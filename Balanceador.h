#include "ThreadConvertirPedido.h"

bool isPedidoCompleto(ListaProducto * , ListaPedido * , Pedido * );

struct ThreadBalanceador{
    std::thread thread; // El objeto thread

    bool running = false, paused  = false;
    ListaPedido * pedidosCompletados, * prioridadAlta, * prioridadMedia,* prioridadBaja;
    ListaProducto * productos;
    ListaProductoDePedido * productosParaFabricar;
    std::mutex mutex; // Mutex para la sincronización de paused/reanudación

    ThreadBalanceador(ListaProductoDePedido * _productosParaFabricar,ListaProducto * _productos, ListaPedido * _pedidosCompletados, ListaPedido * alta, ListaPedido * media,ListaPedido * baja) : thread(&ThreadBalanceador::operator(), this){
        productos = _productos;
        pedidosCompletados = _pedidosCompletados;
        prioridadAlta = alta;
        prioridadMedia = media;
        prioridadBaja = baja;
        productosParaFabricar = _productosParaFabricar;
    }

    void operator()() {
        int i = 0;
        while (!running) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (paused) {
                    // El thread está en pausa, espera
                    lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    lock.lock();
                }
            }
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(2));
           // cout << "TEST:   " << prioridadBaja->isEmpty()<< endl;
            if (!prioridadAlta->isEmpty()){
                prioridadAlta->peek()->pedido->ajustarPedido(productos);
                if(prioridadAlta->peek()->pedido->isPedidoCompleto())
                    pedidosCompletados->encolar(prioridadAlta->desencolar()->pedido);
                else{
                    if(!prioridadAlta->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadAlta->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadAlta->peek()->pedido->atendido = true;
                    prioridadAlta->encolar(prioridadAlta->desencolar()->pedido);
                }
            } 
            if (!prioridadMedia->isEmpty()){
                prioridadMedia->peek()->pedido->ajustarPedido(productos);
                if (prioridadMedia->peek()->pedido->isPedidoCompleto())
                    pedidosCompletados->encolar(prioridadMedia->desencolar()->pedido);
                else{
                    if(!prioridadMedia->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadMedia->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadMedia->peek()->pedido->atendido = true;
                    prioridadMedia->encolar(prioridadMedia->desencolar()->pedido);
                }
            }
            if (!prioridadBaja->isEmpty()){
                
                if (prioridadBaja->peek()->pedido->isPedidoCompleto())
                    pedidosCompletados->encolar(prioridadBaja->desencolar()->pedido);
                else{
                    if(!prioridadBaja->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadBaja->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadBaja->peek()->pedido->atendido = true;
                    prioridadBaja->encolar(prioridadBaja->desencolar()->pedido);
                }
            }
            //cout << "Thread breteando:  " << i++ << endl;
        }
        //std::cout << "Thread ha terminado." << std::endl;
    }

    // Función para pausar el thread
    void Pausar() {
        paused = true;
    }

    // Función para reanudar el thread
    void Reanudar() {
        paused = false;
        running = false;
    }

    // Función para terminar el thread
    void Terminar() {
        running = true;
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~ThreadBalanceador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

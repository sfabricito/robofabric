#include "ThreadConvertirPedido.h"

struct ThreadBalanceador{
    std::thread thread; // El objeto thread

    bool running = true, paused  = false;
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
            std::unique_lock<std::mutex> lock(mutex);
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            lock.lock();
           // cout << "TEST:   " << prioridadBaja->isEmpty()<< endl;
            if (!prioridadAlta->isEmpty()){
                prioridadAlta->peek()->pedido->ajustarPedido(productos);
                if(prioridadAlta->peek()->pedido->isPedidoCompleto()){
                    Pedido * nuevo = prioridadAlta->desencolar()->pedido;
                    pedidosCompletados->encolar(nuevo);
                }else{
                    if(!prioridadAlta->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadAlta->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0,prioridadAlta->peek()->pedido->numeroPedido);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadAlta->peek()->pedido->atendido = true;
                    Pedido * nuevo = prioridadAlta->desencolar()->pedido;
                    prioridadAlta->encolar(nuevo);
                }
            } 
            if (!prioridadMedia->isEmpty()){
                prioridadMedia->peek()->pedido->ajustarPedido(productos);
                if (prioridadMedia->peek()->pedido->isPedidoCompleto()){
                    Pedido * nuevo = prioridadMedia->desencolar()->pedido;
                    pedidosCompletados->encolar(nuevo);
                }else{
                    if(!prioridadMedia->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadMedia->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0,prioridadMedia->peek()->pedido->numeroPedido);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadMedia->peek()->pedido->atendido = true;
                    Pedido * nuevo = prioridadMedia->desencolar()->pedido;
                    prioridadMedia->encolar(nuevo);
                }
            }
            if (!prioridadBaja->isEmpty()){
                prioridadBaja->peek()->pedido->ajustarPedido(productos);
                if (prioridadBaja->peek()->pedido->isPedidoCompleto()){
                    Pedido * nuevo = prioridadBaja->desencolar()->pedido;
                    pedidosCompletados->encolar(nuevo);
                }else{
                    if(!prioridadBaja->peek()->pedido->atendido){
                        ListaProductoDePedido * pendientes = prioridadBaja->peek()->pedido->getProductosFaltantes();
                        NodoProductoDePedido * tmp =  pendientes->primerNodo;
                        while (tmp != NULL){
                            ProductoDePedido * nuevo = new ProductoDePedido(tmp->producto->codigoProducto,tmp->producto->cantidadPedida-tmp->producto->cantidadComprometida,0,prioridadBaja->peek()->pedido->numeroPedido);
                            productosParaFabricar->insertarAlFinal(nuevo);
                            tmp = tmp->siguiente;
                        }
                    }
                    prioridadBaja->peek()->pedido->atendido = true;
                    Pedido * nuevo = prioridadBaja->desencolar()->pedido;
                    prioridadBaja->encolar(nuevo);
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

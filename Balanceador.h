#include "ThreadConvertirPedido.h"

struct ThreadBalanceador{
    std::thread thread; // El objeto thread

    bool running = false, paused  = false;
    ListaPedido * pedidosCompletados, * prioridadAlta, * prioridadMedia,* prioridadBaja;
    ListaProducto * productos;
    std::mutex mutex; // Mutex para la sincronización de paused/reanudación

    ThreadBalanceador(ListaProducto * _productos, ListaPedido * _pedidosCompletados, ListaPedido * alta, ListaPedido * media,ListaPedido * baja) : thread(&ThreadBalanceador::operator(), this){
        productos = _productos;
        pedidosCompletados = _pedidosCompletados;
        prioridadAlta = alta;
        prioridadMedia = media;
        prioridadBaja = baja;
        run();
    }

    void operator()() {
        while (running) {
            cout << running << endl;
            if (paused) {
                if (!prioridadAlta->isEmpty())
                {
                    Pedido * pedido = prioridadAlta->desencolar()->pedido;
                    prepararPedido(productos, pedidosCompletados, pedido);
                }
                if (!prioridadMedia->isEmpty())
                {
                    Pedido * pedido = prioridadMedia->desencolar()->pedido;
                    prepararPedido(productos, pedidosCompletados, pedido);
                }
                if (!prioridadBaja->isEmpty())
                {
                    Pedido * pedido = prioridadBaja->desencolar()->pedido;
                    prepararPedido(productos, pedidosCompletados, pedido);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    // Cambia el estado de paused
    void altenarPausa(){
        paused  = !paused ;
    }

    // Inicia las variables principales
    void run(){
        running = true;
        altenarPausa();
    }

    // Función para terminar el thread
    void Terminar() {
        paused = false;
        running = false;
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~ThreadBalanceador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }

    void prepararPedido(ListaProducto * productos, ListaPedido * pedidosCompletados, Pedido * pedido){
        NodoProductoDePedido * tmp = pedido->productosPedidos->primerNodo;
        while (tmp != NULL){
            Producto * producto = productos->buscarProductoPorCodigo(tmp->producto->codigoProducto)->producto;
            if (producto != NULL){
                if (producto->cantidadAlmacen >= tmp->producto->cantidadPedida){
                    producto->cantidadAlmacen -= tmp->producto->cantidadPedida;
                } else {
                    // Robots producen...
                }
            }
            tmp = tmp->siguiente;
        }
        pedidosCompletados->encolar(pedido);
    }
};

#include "Picking.h"

struct Empacador{
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    //std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * alistados;
    ListaPedido * pedidosParaFacturar;
    ListaString * historial;

    // Constructor
    Empacador(ListaPedido * _pedidosParaFacturar,ListaProducto * _productos, ListaPedido * _alistados) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&Empacador::MiFuncion, this);
        alistados = _alistados;
        productos = _productos;
        pedidosParaFacturar = _pedidosParaFacturar;
        historial = new ListaString ();
        
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {
            {
                //std::unique_lock<std::mutex> lock(mutex);
                while (pausado){
                    // El thread está en pausa, espera
                    //lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    //lock.lock();
                }
            }
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(!alistados->isEmpty()){
                //cout << "QUE PASA AQUI: " << alistados->peek()->pedido->getCantidadDePedidos() << endl;
                std::this_thread::sleep_for(std::chrono::seconds(alistados->peek()->pedido->getCantidadDePedidos()));
                NodoPedido * nuevo = alistados->desencolar();
                historial->insertarAlFinal(nuevo->pedido->toString());
                nuevo->pedido->movimientos->insertarAlFinal("A facturar:\t" + getDateTime() + "\n");

                pedidosParaFacturar->encolar(nuevo->pedido);
            }
        }
    }

    // Función para pausar el thread
    void Pausar() {
        pausado = true;
    }

    // Función para reanudar el thread
    void Reanudar() {
        pausado = false;
    }

    // Función para terminar el thread
    void Terminar() {
        terminar = true;
        pausado = false;
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~Empacador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

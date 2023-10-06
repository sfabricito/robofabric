#include "Picking.h"

struct Empacador{
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * alistados;
    ListaPedido * pedidosParaFacturar;

    // Constructor
    Empacador(ListaPedido * _pedidosParaFacturar,ListaProducto * _productos, ListaPedido * _alistados) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&Empacador::MiFuncion, this);
        alistados = _alistados;
        productos = _productos;
        pedidosParaFacturar = _pedidosParaFacturar;
        
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (pausado){
                    // El thread está en pausa, espera
                    lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    lock.lock();
                }
            }
            std::unique_lock<std::mutex> lock(mutex);
            lock.unlock();
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lock.lock();
            cout << "soy empacador" << endl;
            if(!alistados->isEmpty()){
                std::this_thread::sleep_for(std::chrono::seconds(alistados->peek()->pedido->getCantidadDePedidos()));
                NodoPedido * nuevo = alistados->desencolar();
                pedidosParaFacturar->encolar(nuevo->pedido);
            }
        }
        cout << "soy empacador terminado" << endl;
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
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~Empacador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

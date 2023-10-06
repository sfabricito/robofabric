#include "Fabricador.h"

struct PickingThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * productosParaPicking;
    ListaPedido * alistados;
    int id;


    // Constructor
    PickingThread(int _id,ListaProducto * _productos, ListaPedido * _productosParaPicking, ListaPedido * _alistados) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&PickingThread::MiFuncion, this);
        productosParaPicking = _productosParaPicking;
        alistados = _alistados;
        productos = _productos;
        id = _id;
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {
            {   
                cout << "se mete aqui??????" << endl;
                std::unique_lock<std::mutex> lock(mutex);
                while (pausado) {
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
            cout << "soy picking" << endl;
            if(!productosParaPicking->isEmpty()){
                int duracion = productosParaPicking->peek()->pedido->getDuracionDePicking(productos);
                std::this_thread::sleep_for(std::chrono::seconds(duracion));
                NodoPedido * nuevo = productosParaPicking->desencolar();
                alistados->encolar(nuevo->pedido);
            }
        }
        cout << "soy picking terminado" << endl;
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
    ~PickingThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
    
};

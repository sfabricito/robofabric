#include "Fabricador.h"

struct PickerThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    int id; // Variable con el ID de cada Picker
    ListaProducto * productos;
    ListaPedido * productosParaPicking;
    ListaPedido * alistados;
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación

    // Constructor
    PickerThread(int _id, ListaProducto * _productos, ListaPedido * _productosParaPicking, ListaPedido * _alistados) :  pausado(true), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&RobotThread::MiFuncion, this);
        id = _id;
        productosParaPicking = _productosParaPicking;
        alistados = _alistados;
        productos = _productos;
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {  
            std::unique_lock<std::mutex> lock(mutex);
            while (pausado) {
                // El thread está en pausa, espera
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                lock.lock();
            }
        
            std::unique_lock<std::mutex> lock(mutex);
            lock.unlock();
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            lock.lock();
            if (!productosParaPicking->isEmpty())
            {
                Pedido * alistar = productosParaPicking->desencolar()->pedido;
                std::this_thread::sleep_for(std::chrono::seconds(alistar->getDuracionDePicking(productos)));
                alistados->encolar(alistar);
                Pausar();
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
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~PickerThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

struct PickingThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    PickerThread * pickers[6];
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * productosParaPicking;
    ListaPedido * alistados;


    // Constructor
    PickingThread(ListaProducto * _productos, ListaPedido * _productosParaPicking, ListaPedido * _alistados) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&RobotThread::MiFuncion, this);
        productosParaPicking = _productosParaPicking;
        alistados = _alistados;
        productos = _productos;
        for (int i = 0; i < 6; i++)
            pickers[i] = new PickerThread(i, _productos, _productosParaPicking, _alistados);
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {
            {
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
            cout << "hola como estan" << endl;
            if (!productosParaPicking->isEmpty())
                for (int i = 0; i < 6; i++)
                    if (pickers[i]->pausado == true){
                        pickers[i]->Reanudar();
                        break;
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
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~PickingThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};
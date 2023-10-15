#include "Empacador.h"

struct Facturador{
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    //std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaPedido * pedidosParaFacturar;

    // Constructor
    Facturador(ListaPedido * _pedidosParaFacturar) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&Facturador::MiFuncion, this);
        pedidosParaFacturar = _pedidosParaFacturar;
    }

    Facturador() :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&Facturador::MiFuncion, this);
        
    }

    // Función que será ejecutada por el thread
    void MiFuncion() {
        while (!terminar) {
            {
                //std::unique_lock<std::mutex> lock(mutex);
                while (pausado) {
                    // El thread está en pausa, espera
                    //lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    //cout << "pausado" << endl;
                    //lock.lock();
                }
            }
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (!pedidosParaFacturar->isEmpty()){
                //cout << "HAY ALGO PARA FACTURAR" << endl;
                Pedido * pedidoTmp = pedidosParaFacturar->peek()->pedido;
                string ruta ="",infoPedido="";
                ruta += "Facturados//"+to_string( pedidoTmp->numeroPedido)+"_"+pedidoTmp->codigoCliente+"_";
                ruta += getDateTime()+".txt";
                //cout << ruta << endl;
                infoPedido += pedidoTmp->movimientos->getInfo();
                infoPedido += pedidoTmp->procesosDeRobots->getInfo();
                ofstream archivo(ruta.c_str());
                archivo << infoPedido;
                pedidosParaFacturar->desencolar();
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
        terminar = false;
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
    ~Facturador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

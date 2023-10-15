#include "Fabricador.h"

struct NodoAlistadorThread;
struct ListaAlistadorThread;
struct AlistadorThread;
struct PickingThread;
void encolarAlistador(AlistadorThread * alistador, ListaAlistadorThread * filaAlistadores);

struct AlistadorThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    //std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * productosParaPicking;
    ListaPedido * alistados;
    ListaString * historial;
    ListaAlistadorThread * filaAlistadores;
    int id;


    // Constructor
    AlistadorThread(int _id,ListaProducto * _productos, ListaPedido * _productosParaPicking, ListaPedido * _alistados, ListaAlistadorThread * _filaAlistadores) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&AlistadorThread::MiFuncion, this);
        productosParaPicking = _productosParaPicking;
        alistados = _alistados;
        productos = _productos;
        id = _id;
        filaAlistadores = _filaAlistadores;
        historial = new ListaString();
    }

    // Función que será ejecutada por el thread
    void MiFuncion(){
        while (!terminar) {
            { 
                //std::unique_lock<std::mutex> lock(mutex);
                while (pausado) {
                    // El thread está en pausa, espera
                    //lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    //lock.lock();
                }
            }
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::milliseconds(800));

            if(!productosParaPicking->isEmpty()){
                NodoPedido * nuevo = productosParaPicking->desencolar();
                int duracion = nuevo->pedido->getDuracionDePicking(productos);
                //cout << "DURACION:  " << duracion << endl;
                std::this_thread::sleep_for(std::chrono::seconds(duracion));
                historial->insertarAlFinal(nuevo->pedido->toString());
                nuevo->pedido->movimientos->insertarAlFinal("A empacado:\t" + getDateTime() + "\n");
                string info ="";
                info += "Alisto " + to_string(id) + "\n";
                NodoProductoDePedido * tmp = nuevo->pedido->productosPedidos->primerNodo;
                while (tmp != NULL){
                    info += tmp->producto->codigoProducto + "\t" + "Ubicacion: " + productos->buscarUbicacionDeProducto(tmp->producto->codigoProducto)+"\t";
                    info +=  to_string( getDuracionDelProducto(productos->buscarUbicacionDeProducto(tmp->producto->codigoProducto)))+ "s\n";
                    tmp = tmp->siguiente;
                }
                nuevo->pedido->procesosDeRobots->insertarAlFinal(info);
                alistados->encolar(nuevo->pedido);
                encolarAlistador(this, filaAlistadores);
            }
            Pausar();
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
    ~AlistadorThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

struct NodoAlistadorThread{
    AlistadorThread * alistador;
    NodoAlistadorThread * siguiente;
    NodoAlistadorThread * anterior;

    NodoAlistadorThread(AlistadorThread * _alistador){
        alistador = _alistador;
        siguiente = NULL;
        anterior = NULL;
    }
};

struct ListaAlistadorThread{
    NodoAlistadorThread * primerNodo;
    NodoAlistadorThread * ultimoNodo;

    ListaAlistadorThread(){
        primerNodo = ultimoNodo = NULL;
    }

    bool isEmpty(){
		return primerNodo == NULL;
	}

    NodoAlistadorThread * peek(){
        return primerNodo;
    }

    NodoAlistadorThread * encolar(AlistadorThread * alistador){
		if (isEmpty()){
			primerNodo = ultimoNodo = new NodoAlistadorThread(alistador);
        }
		else{
			NodoAlistadorThread * nuevo = new NodoAlistadorThread(alistador);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
        return ultimoNodo;
    }
        
    NodoAlistadorThread * desencolar(){
        NodoAlistadorThread * borrado = primerNodo;
        if (primerNodo != NULL){
            if (primerNodo == ultimoNodo)
                primerNodo = ultimoNodo = NULL;
            else{
                primerNodo = primerNodo->siguiente;
                borrado ->siguiente = NULL;
                primerNodo->anterior = NULL;
            }
        }
        return borrado;
    }
    void imprimir(){
        NodoAlistadorThread * tmp = primerNodo;
        while (tmp != NULL)
        {
            cout << tmp->alistador->id << endl;
            tmp = tmp->siguiente;
        }
    }
};

struct PickingThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    //std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProducto * productos;
    ListaPedido * productosParaPicking;
    ListaPedido * alistados;
    //ListaString * historial;
    AlistadorThread * alistadores[6];
    ListaAlistadorThread * filaAlistadores;


    // Constructor
    PickingThread(ListaProducto * _productos, ListaPedido * _productosParaPicking, ListaPedido * _alistados) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&PickingThread::MiFuncion, this);
        productosParaPicking = _productosParaPicking;
        alistados = _alistados;
        productos = _productos;
        //historial = new ListaString();
        filaAlistadores = new ListaAlistadorThread();
        for (int i = 0; i < 6; i++){
            alistadores[i] = new AlistadorThread(i+1,productos,productosParaPicking,alistados, filaAlistadores);
            alistadores[i]->Pausar();
            filaAlistadores->encolar(alistadores[i]);
        }
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
                    //lock.lock();
                }
            }
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if(!productosParaPicking->isEmpty() && !filaAlistadores->isEmpty()){
                NodoAlistadorThread * nodo = filaAlistadores->desencolar();
                nodo->alistador->Reanudar();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
        for (int i = 0; i < 6; i++)
            alistadores[i]->Terminar();
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

void encolarAlistador(AlistadorThread * alistador, ListaAlistadorThread * filaAlistadores){
    filaAlistadores->encolar(alistador);
}
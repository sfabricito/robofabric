#include "Balanceador.h"

struct RobotThread {
    std::thread thread; // El objeto thread
    bool pausado; // Variable de control para pausar el thread
    bool terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación
    ListaProductoDePedido * productosAFabricar;
    ListaProducto * productos;
    string categoria;
    bool prioridad;
    int id;


    // Constructor
    RobotThread(int _id,bool _prioridad,string _categoria,ListaProductoDePedido * _productosAFabricar,ListaProducto * _productos) :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&RobotThread::MiFuncion, this);
        prioridad = _prioridad;
        categoria = _categoria;
        productos = _productos;
        productosAFabricar = _productosAFabricar;
        id = _id;
    }

    RobotThread() :  pausado(false), terminar(false) {
        // Iniciar el thread en el constructor
        thread = std::thread(&RobotThread::MiFuncion, this);
        prioridad = false;
        categoria = "";
        productos = NULL;
        productosAFabricar = NULL;
        id = 0;
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
                    cout << "pausado" << endl;
                    lock.lock();
                }
            }
            std::unique_lock<std::mutex> lock(mutex);
            lock.unlock();
            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lock.lock();
            cout << "hola como estan" << endl;
            if (productosAFabricar != NULL){
                if(!productosAFabricar->isEmpty()){
                    if(productos->buscarProductoPorCodigo(productosAFabricar->peek()->producto->codigoProducto)->producto->categoria == categoria){
                        int duracion = productos->getDuracion(productosAFabricar->peek()->producto->codigoProducto);
                        int cantidad = productosAFabricar->peek()->producto->cantidadPedida;
                        std::this_thread::sleep_for(std::chrono::seconds(duracion*cantidad));
                        productos->buscarProductoPorCodigo(productosAFabricar->peek()->producto->codigoProducto)->producto->cantidadAlmacen += cantidad;
                        productosAFabricar->borrarAlInicio();
                        actualizarArchivoProductos(productos);
                    }else{
                        ProductoDePedido * nuevo = productosAFabricar->borrarAlInicio()->producto;
                        productosAFabricar->insertarAlFinal(nuevo);
                    }
                }
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
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~RobotThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

string getLinea(int numero,string _archivo){
    ifstream archivo(_archivo.c_str());
    if (archivo.is_open()){
        string linea;
        while (getline(archivo,linea)){
            numero--;
            if (numero == 0){
                archivo.close();
                return linea;
            }
                
        }
    }else cout << "no se abrio" << endl;
    archivo.close();
    return "";
}

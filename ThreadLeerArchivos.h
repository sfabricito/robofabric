#include "Pedido.h"

struct threadLeerArchivo{//este thread lee los archivos
    std::thread thread; // El thread se encuentra dentro de la estructura
    bool running = false,paused = false;
    ListaProducto * productos;
    ListaCliente * clientes;
    //std::mutex mutex;

    threadLeerArchivo(ListaProducto * l1, ListaCliente * l2) : thread(&threadLeerArchivo::operator(), this) {
        productos = l1;
        clientes = l2;
    }
    
    void operator()() {
        while (!running) {
            {
                //std::unique_lock<std::mutex> lock(mutex);
                while (paused) {
                    // El thread está en pausa, espera
                    //lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    //lock.lock();
                }
            }

            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(2));
            leerArchivosEnCarpeta("Pedidos",clientes,productos);
            //cout << "Thread breteando leer :  " << i++ << endl;
        }
        std::cout << "Thread ha terminado." << std::endl;
    }

    

    // Constructor que inicia el thread en el momento de la creación de la estructura
    

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
    ~threadLeerArchivo() {
        Terminar(); // Asegura que el thread se termine correctamente
    }

};

void leerArchivosEnCarpeta(string rutaCarpeta,ListaCliente * clientes,ListaProducto * productos) {
    for (const auto& archivo : fs::directory_iterator(rutaCarpeta)) {
        if (fs::is_regular_file(archivo)) {
            //cout << archivo.path().filename().string() << endl;
            revisarPedido(archivo.path().filename().string(),clientes,productos);
        }
    }
    
}
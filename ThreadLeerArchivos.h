#include "Pedido.h"

struct threadLeerArchivo{//este thread lee los archivos
    bool running = true,paused = false;
    ListaProducto * productos;
    ListaCliente * clientes;
    

    void operator()() {
        while (running) {
            if (!paused) {
                leerArchivosEnCarpeta("Pedidos",clientes,productos);
            }
            this_thread::sleep_for(chrono::seconds(5));
        }
    }

    std::thread thread; // El thread se encuentra dentro de la estructura

    // Constructor que inicia el thread en el momento de la creación de la estructura
    threadLeerArchivo(ListaProducto * l1, ListaCliente * l2) : thread(&threadLeerArchivo::operator(), this) {
        productos = l1;
        clientes = l2;
    }

    void stop() {
        running = false;
        paused = false; // Asegúrate de que el hilo no esté en pausa
        if (thread.joinable()) {
            thread.join(); // Espera a que el hilo termine
        }
    }

    // Método para pausar el hilo
    void pause() {
        paused = true;
    }

    // Método para reanudar el hilo
    void resume() {
        paused = false;
    }

};

void leerArchivosEnCarpeta(string rutaCarpeta,ListaCliente * clientes,ListaProducto * productos) {
    for (const auto& archivo : fs::directory_iterator(rutaCarpeta)) {
        if (fs::is_regular_file(archivo)) {
            revisarPedido(archivo.path().filename().string(),clientes,productos);
        }
    }
    
}
#include "ThreadLeerArchivos.h"

Pedido * convertirAPedido(string);

struct ThreadConvertirPedido {
    thread thread; // El objeto thread

    bool running = true,paused = false;
    ListaPedido * prioridadAlta, * prioridadMedia,* prioridadBaja;
    ListaCliente * clientes;

    // Constructor
    ThreadConvertirPedido(ListaCliente * _clientes,ListaPedido * alta, ListaPedido * media,ListaPedido * baja) : thread(&ThreadConvertirPedido::operator(), this) {
        prioridadAlta = alta;
        prioridadMedia = media;
        prioridadBaja = baja;
        clientes = _clientes;
    }

    // Función que será ejecutada por el thread
    void operator()() {
        Pedido * pedidoTemporal;
        while (running) {
            if (!paused) {
                // Realiza alguna tarea aquí
                for (const auto& archivo : fs::directory_iterator("Procesados")) {
                    if (fs::is_regular_file(archivo)) {
                        cout << archivo.path().string() << endl;
                        /*pedidoTemporal = convertirAPedido(archivo.path().);
                        //cout << pedidoTemporal->toString() << endl;
                        if (clientes->getPrioridad(pedidoTemporal->codigoCliente) == 11)
                            prioridadAlta->encolar(pedidoTemporal);
                        else if (clientes->getPrioridad(pedidoTemporal->codigoCliente) == 10){
                            prioridadMedia->encolar(pedidoTemporal);
                        }else{
                            prioridadBaja->encolar(pedidoTemporal);
                        }
                        */
                        
                    }
                }
            }
            this_thread::sleep_for(chrono::seconds(5));
        }
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

Pedido * convertirAPedido(string _archivo){
    ifstream archivo(_archivo.c_str());
    if(archivo.is_open()){
        Pedido * pedido = new Pedido();
        string cliente,linea;
        int codigo;
        getline(archivo,linea);
        codigo = stoi(linea);
        getline(archivo,linea);
        cliente = linea;
        pedido->codigoCliente = cliente;
        pedido->numeroPedido = codigo;
        vector<string> producto;
        int cantidad;
        while(getline(archivo,linea)){
            producto = separarProductoDePedido(linea);
            cantidad = stoi(producto[1]);
            //cout << "PRODUCTO:   " << producto[0] << "  CANTIDAD   " << cantidad << endl;
            //cout << "PRODUCTOOOOOOOOOOOOO: " << productoDePedido->codigoProducto << "  " <<productoDePedido->cantidadPedida  << endl;
            pedido->agregarProducto(new ProductoDePedido(producto[0],cantidad,0));
        }
        return pedido;
    }
    cout << "no se abriooooooooooooooooo" << endl;
    archivo.close();
    return NULL;
}

void leerArchivosEnCarpeta2(string rutaCarpeta) {
    for (const auto& archivo : fs::directory_iterator(rutaCarpeta)) {
        if (fs::is_regular_file(archivo)) {
            cout << archivo.path().filename().string() << endl;
            //convertirAPedido(archivo.path().filename().string());
        }
    }
    
}






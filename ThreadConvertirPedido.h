#include "ThreadLeerArchivos.h"

Pedido * convertirAPedido(string);
void convertirPedidosDeCarpeta(string ,ListaPedido * ,ListaPedido * ,ListaPedido * ,ListaCliente *);

struct ThreadConvertirPedido {
    thread thread; // El objeto thread

    bool running = false,paused = false;
    ListaPedido * prioridadAlta, * prioridadMedia,* prioridadBaja;
    ListaCliente * clientes;
    std::mutex mutex; // Mutex para la sincronización de pausa/reanudación

    // Constructor
    ThreadConvertirPedido(ListaCliente * _clientes,ListaPedido * alta, ListaPedido * media,ListaPedido * baja) : thread(&ThreadConvertirPedido::operator(), this) {
        prioridadAlta = alta;
        prioridadMedia = media;
        prioridadBaja = baja;
        clientes = _clientes;
    }

    // Función que será ejecutada por el thread
    void operator()() {
        int i = 0;
        while (!running) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (paused) {
                    // El thread está en pausa, espera
                    lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    lock.lock();
                }
            }

            // Realiza alguna tarea aquí
            std::this_thread::sleep_for(std::chrono::seconds(2));
            convertirPedidosDeCarpeta("Procesados",prioridadAlta,prioridadMedia,prioridadBaja,clientes);
            cout << "Thread breteando:  " << i++ << endl;
        }
        std::cout << "Thread ha terminado." << std::endl;
    }

    // Función para pausar el thread
    void Pausar() {
        paused = true;
    }

    // Función para reanudar el thread
    void Reanudar() {
        paused = false;
    }

    // Función para terminar el thread
    void Terminar() {
        running = true;
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~ThreadConvertirPedido() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

Pedido * convertirAPedido(string _archivo){
    string ruta = "Procesados//";
    ruta += _archivo;
    string desktop = "Convertidos//";
    desktop += _archivo;
    ifstream archivo(ruta.c_str());
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
        archivo.close();
        cout << ruta << "\t" << desktop << endl;
        rename(ruta.c_str(),desktop.c_str());
        return pedido;
    }
    cout << "no se abriooooooooooooooooo " << _archivo << endl;
    return NULL;
}

void convertirPedidosDeCarpeta(string rutaCarpeta,ListaPedido * alta,ListaPedido * media,ListaPedido * baja,ListaCliente * clientes) {
    for (const auto& archivo : fs::directory_iterator(rutaCarpeta)) {
        if (fs::is_regular_file(archivo)) {
            Pedido * pedidoTemporal = new Pedido();
            //cout << archivo.path().filename().string() << endl;
            pedidoTemporal = convertirAPedido(archivo.path().filename().string());
            if (pedidoTemporal != NULL){
                if (clientes->getPrioridad(pedidoTemporal->codigoCliente) == 10){
                    media->encolar(pedidoTemporal);
                }else if (clientes->getPrioridad(pedidoTemporal->codigoCliente) < 10){
                    baja->encolar(pedidoTemporal);
                } 
            }else cout << "no se pudo hacer el pedido" << endl;
        }
    }
    
}






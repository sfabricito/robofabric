
#include "ThreadConvertirPedido.h"

int main(){
    ListaCliente * clientes = new ListaCliente();
    ListaProducto * productos = new ListaProducto(); 
    ListaPedido * alta = new ListaPedido();
    ListaPedido * media = new ListaPedido();
    ListaPedido * baja = new ListaPedido();
    cargarProductos(productos);
    cargarClientes(clientes);
    //clientes->imprimir();
    //threadLeerArchivo myThread(productos,clientes);
    //myThread.thread.join();
    //myThread.stop();
    
    
    //Pedido * p1 = convertirAPedido("Procesados//prueba.txt");
    //convertirPedidosDeCarpeta("Procesados",alta,media,baja,clientes);
    //cout << "baja:   " << endl;
    //baja->imprimir();
    ThreadConvertirPedido thread(clientes,alta,media,baja);
    thread.Reanudar();
    // Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // Terminar el thread
    thread.Terminar();

    cout << "media:   " << endl;
    media->imprimir();
    cout << "baja:   " << endl;
    baja->imprimir();
    

    return 0;
} 

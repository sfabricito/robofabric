
#include "Balanceador.h"

int main(){
    ListaCliente * clientes = new ListaCliente();
    ListaProducto * productos = new ListaProducto(); 
    ListaPedido * pedidosCompletados = new ListaPedido();
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
    ThreadConvertirPedido thread1(clientes,alta,media,baja);
    thread1.Reanudar();
    // Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Terminar el thread
    thread1.Terminar();


    productos->imprimir();
    
    ThreadBalanceador thread(productos, pedidosCompletados , alta, media, baja);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    thread.Terminar();
    pedidosCompletados->imprimir();
    productos->imprimir();
    //cout << "media:   " << endl;
    //media->imprimir();
    //cout << "baja:   " << endl;
    //baja->imprimir();
    

    return 0;
} 

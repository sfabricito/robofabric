
#include "Balanceador.h"

int main(){
    ListaCliente * clientes = new ListaCliente();
    ListaProducto * productos = new ListaProducto(); 
    ListaPedido * pedidosCompletados = new ListaPedido();
    ListaPedido * alta = new ListaPedido();
    ListaPedido * media = new ListaPedido();
    ListaPedido * baja = new ListaPedido();
    ListaProductoDePedido * pendientes = new ListaProductoDePedido();
    cargarProductos(productos);
    cargarClientes(clientes);
    //clientes->imprimir();
    //productos->imprimir();

    //----------------------THREAD LEE ARCHIVOS
    // threadLeerArchivo myThread(productos,clientes);
    // myThread.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    //  Terminar el thread
    // myThread.Terminar();

    //---------------------THREAD CONVERTIR A PEDIDOS
    ThreadConvertirPedido thread1(clientes,alta,media,baja);
    thread1.Reanudar();
    //   Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(4));
    //   Terminar el thread
    thread1.Terminar();


    cout << "media:   " << endl;
    media->imprimir();
    cout << "baja:   " << endl;
    baja->imprimir();

    
    // ---------------------THREAD BALANCEADOR
    ThreadBalanceador thread(pendientes,productos, pedidosCompletados , alta, media, baja);
    thread1.Reanudar();
    //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(4));
    //Terminar el thread
    thread1.Terminar();
    // pedidosCompletados->imprimir();
    //productos->imprimir();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "PENDIENTES:  " << endl;
    pendientes->imprimir();
    
    

    return 0;
} 

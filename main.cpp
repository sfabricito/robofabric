
#include "Empacador.h"

int main(){
    ListaCliente * clientes = new ListaCliente();
    ListaProducto * productos = new ListaProducto(); 
    ListaPedido * pedidosCompletados = new ListaPedido();
    ListaPedido * alta = new ListaPedido();
    ListaPedido * media = new ListaPedido();
    ListaPedido * baja = new ListaPedido();
    ListaPedido * alistados = new ListaPedido();
    ListaProductoDePedido * pendientes = new ListaProductoDePedido();
    cargarProductos(productos);
    cargarClientes(clientes);
    
    //----------------------THREAD LEE ARCHIVOS
    threadLeerArchivo myThread(productos,clientes);
    myThread.Reanudar();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    //Terminar el thread
    myThread.Terminar();
    
    //---------------------THREAD CONVERTIR A PEDIDOS
    // ThreadConvertirPedido thread1(clientes,alta,media,baja);
    // thread1.Reanudar();
    //    //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    // cout << "Funciona el thread" << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // cout << "Termina el thread" << endl;
    //    //Terminar el thread
    // thread1.Terminar();

    // cout << "media:   " << endl;
    // media->imprimir();
    // cout << "baja:   " << endl;
    // baja->imprimir();
    
    //  //---------------------THREAD BALANCEADOR
    //  ThreadBalanceador thread(pendientes,productos, pedidosCompletados , alta, media, baja);
    //  thread.Reanudar();
    //  //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    //  std::this_thread::sleep_for(std::chrono::seconds(6));
    //  //Terminar el thread
    //  thread.Terminar();
    
    //  std::this_thread::sleep_for(std::chrono::seconds(2));

    //  cout << "Pedidos Completados:  " << endl;
    //  //pendientes->imprimir();
    //  if(!pedidosCompletados->isEmpty()){
    //      cout << "si se metio" << endl;
    //      pedidosCompletados->imprimir();
    //  }


    //  //----------------THREAD ROBOTS
    // //RobotThread robots[10];
    
    // //-------------------THREAD PICKING
    // PickingThread picking1(productos,pedidosCompletados,alistados);
    // picking1.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(40));
    // picking1.Terminar();

    // if (!alistados->isEmpty()){
    //     cout << "alistados hay algo" << endl;
    //     alistados->imprimir();
    // }
    return 0;
} 

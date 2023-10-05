
#include "Picking.h"

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
    Pedido * p1 = convertirAPedido("prueba.txt");
    cout << p1->getDuracionDePicking(productos);
    //int ubi
    // RobotThread robot11(true,"A",pendientes,productos);
    // robot11.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // robot11.Terminar();
    //----------------------THREAD LEE ARCHIVOS
    // threadLeerArchivo myThread(productos,clientes);
    // myThread.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // //  Terminar el thread
    // myThread.Terminar();

    // //---------------------THREAD CONVERTIR A PEDIDOS
    // ThreadConvertirPedido thread1(clientes,alta,media,baja);
    // thread1.Reanudar();
    // //   Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    // cout << "Funciona el thread" << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // cout << "Termina el thread" << endl;
    // //   Terminar el thread
    // thread1.Terminar();


    // cout << "media:   " << endl;
    // media->imprimir();
    // cout << "baja:   " << endl;
    // baja->imprimir();

    
    // // ---------------------THREAD BALANCEADOR
    // ThreadBalanceador thread(pendientes,productos, pedidosCompletados , alta, media, baja);
    // thread.Reanudar();
    // // Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    // std::this_thread::sleep_for(std::chrono::seconds(6));
    // // Terminar el thread
    // thread.Terminar();
    
    // std::this_thread::sleep_for(std::chrono::seconds(2));

    // // cout << "Pedidos Completados:  " << endl;
    // pendientes->imprimir();
    // if(!pedidosCompletados->isEmpty()){
    //     cout << "si se metio" << endl;
    //     pedidosCompletados->imprimir();
    // }
        
    
    

    return 0;
} 

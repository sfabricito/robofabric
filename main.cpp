
#include "menu.h"

int main(){
    // Inicializar variables
    ListaCliente * clientes = new ListaCliente();
    ListaProducto * productos = new ListaProducto(); 
    ListaPedido * pedidosCompletados = new ListaPedido();
    ListaPedido * alta = new ListaPedido();
    ListaPedido * media = new ListaPedido();
    ListaPedido * baja = new ListaPedido();
    ListaPedido * alistados = new ListaPedido();
    ListaPedido * pedidosAFacturar = new ListaPedido();
    ListaProductoDePedido * pendientes = new ListaProductoDePedido();
    cargarProductos(productos);
    cargarClientes(clientes);

    // Inicializar Threads
    threadLeerArchivo * threadLeerArchivos = new threadLeerArchivo(productos,clientes);
    threadLeerArchivos->Reanudar();
    ThreadConvertirPedido * threadConvertirPedido = new ThreadConvertirPedido(clientes,alta,media,baja);
    threadConvertirPedido->Reanudar();
    ThreadBalanceador * threadBalanceador = new ThreadBalanceador(pendientes,productos, pedidosCompletados , alta, media, baja);
    threadBalanceador->Reanudar();
    threadBalanceador->Pausar();

    Empacador * empacador = new Empacador(pedidosAFacturar,productos,alistados);
    empacador->Reanudar();
    empacador->Pausar();

    Facturador * facturador = new Facturador(pedidosAFacturar);
    facturador->Reanudar();
    facturador->Pausar();

    // Fabricadores
    RobotThread * robots[10];
    for (int i = 0; i < 10; i++){
        string info = getLinea(i+1,"Robots.txt");
        vector<string> lineaInfo = getCliente(info);
        string categoria = lineaInfo[1];
        bool prioridad;
        if (lineaInfo[2] == "1")
            prioridad = true;
        else
            prioridad = false;
        robots[i] = new RobotThread(i + 1, prioridad, categoria, pendientes, productos);
        if(lineaInfo[0] == "0"){
            robots[i]->Pausar();
        }else if (lineaInfo[0] == "1"){
            robots[i]->Reanudar();
        }
    }

    menu(clientes, productos, alta, media, baja, threadBalanceador, empacador, facturador, robots);
    
    // // //----------------------THREAD LEE ARCHIVOS
    // threadLeerArchivo myThread(productos,clientes);
    // myThread.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(20));
    // //Terminar el thread
    // myThread.Terminar();

    
    // //---------------------THREAD CONVERTIR A PEDIDOS
    // ThreadConvertirPedido thread1(clientes,alta,media,baja);
    // thread1.Reanudar();
    // //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    // cout << "Funciona el thread" << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // cout << "Termina el thread" << endl;
    // //Terminar el thread
    // thread1.Pausar();

    // cout << "alta:   " << endl;
    // alta->imprimir();
    // cout << "media:   " << endl;
    // media->imprimir();
    // cout << "baja:   " << endl;
    // baja->imprimir();

    //  //---------------------THREAD BALANCEADOR
    //  ThreadBalanceador thread(pendientes,productos, pedidosCompletados , alta, media, baja);
    //  thread.Reanudar();
    //  //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos) 
    //  std::this_thread::sleep_for(std::chrono::seconds(4));
    //  //Terminar el thread
    //  thread.Pausar();
    //  pendientes->imprimir();
     


    //  //----------------THREAD ROBOTS
    // // RobotThread robots[10];
    // // for (int i = 0; i < 10; i++){
    // //     string info = getLinea(i+1,"Robots.txt");
    // //     vector<string> lineaInfo = getCliente(info);
    // //     robots[i].categoria = lineaInfo[1];
    // //     robots[i].productosAFabricar = pendientes;
    // //     robots[i].productos = productos;
    // //     robots[i].id = i+1;
    // //     if(lineaInfo[0] == "0"){
    // //         robots[i].Pausar();
    // //     }else if (lineaInfo[0] == "1"){
    // //         robots[i].Reanudar();
    // //     }
    // //     if (lineaInfo[2] == "1"){
    // //         robots[i].prioridad = true;
    // //     }else{
    // //         robots[i].prioridad = false;
    // //     }
    // // }

    // RobotThread robot(1,true,"A",pendientes,productos);
    // robot.Reanudar();
    // //Esperar un tiempo antes de terminar el thread (por ejemplo, después de 5 segundos)
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // //Terminar el thread
    // robot.Terminar();
    // if(!pedidosCompletados->isEmpty()){
    //      cout << "si se metio" << endl;
    //      pedidosCompletados->imprimir();
    //     pedidosCompletados->primerNodo->pedido->movimientos->imprimir();
    // }else cout << "me cago en tencha" << endl;
    
    // // // cout << "Pedidos pedidosCompletados:  " << endl;
    // // //  //pendientes->imprimir();
    // // // if(!pedidosCompletados->isEmpty()){
    // // //     cout << "si se metio" << endl;
    // // //     pedidosCompletados->imprimir();
    // // // }
    // // cout << "que pasa" << endl;
    
    // //-------------------THREAD PICKING
    // PickingThread picking1(1,productos,pedidosCompletados,alistados);
    // picking1.Reanudar();
    // cout << "nada paso" << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // cout << "nada paso 2" << endl;
    // picking1.Terminar();

    // if (!alistados->isEmpty()){
    //     cout << "alistados hay algo" << endl;
    //     alistados->imprimir();
    //     alistados->primerNodo->pedido->movimientos->imprimir();
    // }


    // // ------------------------EMPACADOR
    // Empacador empacador(pedidosAFacturar,productos,alistados);
    // empacador.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // empacador.Terminar();
    // if (!pedidosAFacturar->isEmpty()){
    //     cout << "pedidosAFacturar hay algo" << endl;
    //     pedidosAFacturar->imprimir();
    //     pedidosAFacturar->primerNodo->pedido->movimientos->imprimir();
    //     cout << "PROCESOS DE ROBOTS" << endl;
    //     pedidosAFacturar->primerNodo->pedido->procesosDeRobots->imprimir();
    // }


    // Facturador facturador(pedidosAFacturar);
    // facturador.Reanudar();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // facturador.Terminar();
    // // // cout << getDateTime() << endl;
    // // // ofstream archivo("Facturados//"+getDateTime()+".txt");
    // // // archivo<<"hola";
    return 0;
} 

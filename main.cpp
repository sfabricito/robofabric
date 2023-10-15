
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

    PickingThread * picking = new PickingThread(productos,pedidosCompletados,alistados);
    picking->Reanudar();


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
    
    menu(clientes, productos, alta, media, baja, threadBalanceador, empacador, facturador, robots, picking);

    // Terminar Hilos
    threadLeerArchivos->Terminar();
    threadConvertirPedido->Terminar();
    threadBalanceador->Terminar();
    empacador->Terminar();
    facturador->Terminar();
    for (int i = 0; i < 10; i++)
        robots[i]->Terminar();
    picking->Terminar();
    return 0;
} 

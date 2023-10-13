// Includes
#include "Facturador.h"
#include "iostream"

using namespace std;

// Prototipos
void imprimirBanner();
void imprimirOpciones();
void imprimirClientes(ListaCliente * clientes);
void imprimirAlmacen(ListaProducto * productos);
void menuPedidos(ListaCliente * clientes, ListaProducto * productos, ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja);
void imprimirPedidos(ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja);
void imprimirPedido(ListaPedido * lista, string prioridad);
void agregarPedido(ListaCliente * clientes, ListaProducto * productos, ListaPedido * lista);
void menuBalanceador();
void menuFabricadores();
void imprimirFabricadores();
void imprimirFabricador();
void menuPicking();
void imprimirAlistadores();
void imprimirAlistador();
void menuEmpacador();
void imprimirEmpacador();
void menuFacturador();
void imprimirFacturador();

void continuar();
int pedirNumero(string text);
string pedirString(string text);
int verifyIntPositive(string number);
double verifyDoublePositive(string number);

// Funciones

void linea(){
    cout << "---------------------------------------------------------------" << endl; 
}

void continuar(){
    cout << "Presiona 'Enter' para continuar: ";
    string input;
    getline(cin, input);
    linea();
}

void imprimirBanner(){
    cout << "    ____  ____  ____  ____  _________    ____  ____  __________" << endl;
    cout << "   / __ \\/ __ \\/ __ )/ __ \\/ ____/   |  / __ )/ __ \\/  _/ ____/" << endl;
    cout << "  / /_/ / / / / __  / / / / /_  / /| | / __  / /_/ // // /" << endl;
    cout << " / _, _/ /_/ / /_/ / /_/ / __/ / ___ |/ /_/ / _, _// // /___ " << endl;
    cout << "/_/ |_|\\____/_____/\\____/_/   /_/  |_/_____/_/ |_/___/\\____/" << endl; 
    linea();                                                                                            
}
    
void imprimirOpciones(){
    cout << " (1) Clientes" << endl;
    cout << " (2) Productos" << endl;
    cout << " (3) Pedidos" << endl;
    cout << " (4) Balanceador" << endl;
    cout << " (5) Fabricadores" << endl;
    cout << " (6) Picking" << endl;
    cout << " (7) Empacador" << endl;
    cout << " (8) Facturador" << endl;
    cout << " (9) Salir  " << endl;
}

void menu(ListaCliente * clientes, ListaProducto * productos, ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja){
    imprimirBanner();
    int opcion = 0;
    while (opcion != 9){
        imprimirOpciones();
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Clientes
                imprimirClientes(clientes);
                continuar();
                break;
            case 2: // Almacen (Productos)
                imprimirAlmacen(productos);
                continuar();
                break;
            case 3: // Pedidos
                menuPedidos(clientes, productos, prioridadAlta, prioridadMedia, prioridadBaja);
                break;
            case 4:
                // Balanceador
                menuBalanceador();
                break;
            case 5:
                // Agregar codigo Fabricadores
                menuFabricadores();
                break;
            case 6:
                // Agregar codigo Picking
                menuPicking();
                break;
            case 7:
                // Agregar codigo Empacador
                menuEmpacador();
                break;
            case 8:
                // Agregar codigo facturador
                menuFacturador();
                break;
            case 9:
                return;
        }
    }
}

// Funciones para manejar opciones
void imprimirClientes(ListaCliente * clientes){
    if (clientes->isEmpty()){
        linea();
        cout << "No hay clientes registrados" << endl;
    }
    else {
        NodoCliente * tmp = clientes->primerNodo;
        while (tmp != NULL)
        {
            linea();
            cout << "Código: " << tmp->cliente->codigo << endl;
            cout << "Nombre: " << tmp->cliente->nombre << endl;
            cout << "Prioridad: " << tmp->cliente->prioridad << endl;
            tmp = tmp->sig; 
        }
    }
    linea();
}

void imprimirAlmacen(ListaProducto * productos){
    if (productos->isEmpty()){
        linea();
        cout << "No hay productos en el Almacen" << endl;
    }
    else {
        NodoProducto * tmp = productos->primerNodo;
        while (tmp != NULL)
        {
            linea();
            cout << "Código: " << tmp->producto->codigo << endl;
            cout << "Cantidad Almacen: " << tmp->producto->cantidadAlmacen << endl;
            cout << "Tiempo de Fabricación: " << tmp->producto->tiempoFabricacion << endl;
            cout << "Categoría: " << tmp->producto->categoria << endl;
            cout << "Ubicación Bodega: " << tmp->producto->categoria << endl;
            tmp = tmp->siguiente; 
        }
    }
    linea();
}

void menuPedidos(ListaCliente * clientes, ListaProducto * productos, ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja){
    int opcion = 0;
    while (opcion != 3){
        cout << " (1) Ver pedidos" << endl;
        cout << " (2) Agregar pedido" << endl;
        cout << " (3) Regresar al Menú Principal" << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Imprimir Pedidos
                imprimirPedidos(prioridadAlta, prioridadMedia, prioridadBaja);
                continuar();
                break;
            case 2: // Agregar pedido
                agregarPedido(clientes, productos, prioridadAlta);
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
        }

    }
}

void imprimirPedidos(ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja){
    if (prioridadAlta->isEmpty() && prioridadMedia->isEmpty() && prioridadBaja->isEmpty()){
        linea();
        cout << "No hay pedidos actualmente" << endl;
    }
    else {
        imprimirPedido(prioridadAlta, "Alta");
        imprimirPedido(prioridadMedia, "Media");
        imprimirPedido(prioridadBaja, "Baja");
    }
    linea();
}

void imprimirPedido(ListaPedido * lista, string prioridad){
        NodoPedido * tmp = lista->primerNodo;

        while (tmp != NULL)
        {
            linea();
            cout << "Prioridad: " << prioridad << endl;
            cout << "Número de Pedido: " << tmp->pedido->numeroPedido << endl;
            cout << "Código Cliente:  " << tmp->pedido->codigoCliente << endl;
            cout << "Productos del Pedido:" << endl;
            NodoProductoDePedido * tmpProducto = tmp->pedido->productosPedidos->primerNodo;
            while(tmpProducto != NULL){
                cout << "Código Producto: " << tmpProducto->producto->codigoProducto << endl;
                cout << "Cantidad Pedida: " << tmpProducto->producto->cantidadPedida << endl;
                cout << "Cantidad Comprometida: " << tmpProducto->producto->cantidadComprometida << endl;
                tmpProducto = tmpProducto->siguiente;
            }
            tmp = tmp->siguiente; 
        }
    linea();
}

void agregarPedido(ListaCliente * clientes, ListaProducto * productos, ListaPedido * lista){
    int numeroPedido = -1;
    while (numeroPedido <= 0){
        //TODO validar que el pedido no existe
        numeroPedido = pedirNumero("Número de Pedido: ");
    }
    string codigoCliente = pedirString("Código Cliente: ");
    while(!clientes->buscarCliente(codigoCliente)){
        cout << "Este cliente no existe" << endl;
        codigoCliente = pedirString("Código Cliente: ");
    }
    Pedido * pedido = new Pedido(codigoCliente, numeroPedido);
    bool agregarProducto = true;
    while (agregarProducto){
        string codigoProducto = pedirString("Código Producto: ");
        while(productos->buscarProductoPorCodigo(codigoProducto) == NULL){
            cout << "Este producto no existe" << endl;
            codigoProducto = pedirString("Código Producto: ");
        }
        int cantidadPedida = -1;
        while (cantidadPedida <= 0){
            cantidadPedida = pedirNumero("Cantidad requerida: ");
        }
        pedido->agregarProducto(new ProductoDePedido(codigoProducto, cantidadPedida, 0, numeroPedido));

        string seguirInsertando = pedirString("Agregar otro producto (Si o No): ");
        agregarProducto = false;
        if (seguirInsertando == "SI" || seguirInsertando == "Si" || seguirInsertando == "si"){
            cout << "here" << endl;
            agregarProducto = true;
        }
    }
    lista->encolar(pedido);
}

void menuBalanceador(){
    cout << " (1) Encender Balanceador" << endl;
    cout << " (2) Apagar Balanceador" << endl;
    cout << " (3) Salir  " << endl;
    int opcion = 0;
    while (opcion != 3){
        opcion = pedirNumero("Opción deseada: ");
            switch (opcion){
                case 1:
                    // Encender Balanceador
                    break;
                case 2:
                    // Apagar Balanceador
                    break;
                case 3:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

void menuFabricadores(){
    cout << " (1) Ver Fabricadores" << endl;
    cout << " (2) Ver Fabricador especifico" << endl;
    cout << " (3) Encender un Balanceador" << endl;
    cout << " (4) Apagar un Balanceador" << endl;
    cout << " (5) Salir  " << endl;
    int opcion = 0;
    while (opcion != 5){
        opcion = pedirNumero("Opción deseada: ");
            switch (opcion){
                case 1:
                    // Imprimir Fabricadores
                    imprimirFabricadores();
                    break;
                case 2:
                    // Imprimir Fabricador
                    imprimirFabricador();
                    break;
                case 3:
                    // Encender un fabricador
                    return;
                case 4:
                    // Apagar un fabricador
                    break;
                case 5:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

// TODO
void imprimirFabricadores(){

}

// TODO
void imprimirFabricador(){

}

void menuPicking(){
    cout << " (1) Ver Alistadores" << endl;
    cout << " (2) Ver Alistador especifico" << endl;
    cout << " (3) Encender un Alistador" << endl;
    cout << " (4) Apagar un Alistador" << endl;
    cout << " (5) Salir  " << endl;
    int opcion = 0;
    while (opcion != 5){
        opcion = pedirNumero("Opción deseada: ");
            switch (opcion){
                case 1:
                    // Imprimir Alistadores
                    imprimirAlistadores();
                    break;
                case 2:
                    // Imprimir Alistador
                    imprimirAlistador();
                    break;
                case 3:
                    // Encender un alistador
                    return;
                case 4:
                    // Apagar un alistador
                    break;
                case 5:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

// TODO
void imprimirAlistadores(){

}

// TODO
void imprimirAlistador(){

}

void menuEmpacador(){
    cout << " (1) Ver Empacador" << endl;
    cout << " (2) Encender Empacador" << endl;
    cout << " (3) Apagar Empacador" << endl;
    cout << " (4) Salir  " << endl;
    int opcion = 0;
    while (opcion != 4){
        opcion = pedirNumero("Opción deseada: ");
            switch (opcion){
                case 1:
                    // Imprimir Empacador
                    imprimirEmpacador();
                    break;
                case 2:
                    // Encender Empacador
                    break;
                case 3:
                    // Apagar Empacador
                    break;
                case 4:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

void imprimirEmpacador(){

}

void menuFacturador(){
    cout << " (1) Ver Facturador" << endl;
    cout << " (2) Encender Facturador" << endl;
    cout << " (3) Apagar Facturador" << endl;
    cout << " (4) Salir  " << endl;
    int opcion = 0;
    while (opcion != 4){
        opcion = pedirNumero("Opción deseada: ");
            switch (opcion){
                case 1:
                    // Imprimir Facturador
                    imprimirFacturador();
                    break;
                case 2:
                    // Encender Facturador
                    break;
                case 3:
                    // Apagar Facturador
                    break;
                case 4:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

void imprimirFacturador(){

}

// Funciones secundarias
int pedirNumero(string text){
    cout << text;
    string option;
    getline(cin, option);
    int numberVerified = verifyIntPositive(option); 
    if (numberVerified < 1)
        return pedirNumero(text);
    return numberVerified;
}

string pedirString(string text){
    cout << text;
    string option;
    getline(cin, option);
    return option;
}

int verifyIntPositive(string number){
    try
    {
        return stoi(number);
    }
    catch(const std::exception& e)
    {
        return -1;
    }
}

double verifyDoublePositive(string number){
    try
    {
        return stod(number);
    }
    catch(const std::exception& e)
    {
        return -1;
    }
}
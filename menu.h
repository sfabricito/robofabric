// Includes
#include "Facturador.h"
#include "iostream"

using namespace std;

// Prototipos
void imprimirBanner();
void imprimirOpciones();
void menuClientes(ListaCliente * clientes);
void imprimirClientes(ListaCliente * clientes);
void agregarClientes(ListaCliente * clientes);
void imprimirAlmacen(ListaProducto * productos);
void menuPedidos(ListaCliente * clientes, ListaProducto * productos, ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja);
void imprimirPedidos(ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja);
void imprimirPedido(ListaPedido * lista, string prioridad);
void agregarPedido(ListaCliente * clientes, ListaProducto * productos, ListaPedido * lista);
void menuBalanceador(ThreadBalanceador * balanceador);
void menuFabricadores(RobotThread * robots[]);
void imprimirFabricadores(RobotThread * robots[]);
void menuFabricador(RobotThread * robots[], int id);
void menuPicking();
void imprimirAlistadores();
void imprimirAlistador();
void menuEmpacador(Empacador * empacador);
void imprimirEmpacador();
void menuFacturador(Facturador * facturador);
void imprimirFacturador();

void continuar();
int pedirNumero(string text);
string pedirString(string text);
int verifyIntPositive(string number);
double verifyDoublePositive(string number);
string textoRojo(string texto);
string textoVerde(string texto);
string textoAzul(string texto);
string textoAmarillo(string texto);

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

void limpiarConsola(){
    #ifdef _WIN32
    std::system("cls");
    #elif __linux__
    std::system("clear");
    #endif
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
    //cout << " (5) Fabricadores" << endl;
    //cout << " (6) Picking" << endl;
    cout << " (7) Empacador" << endl;
    cout << " (8) Facturador" << endl;
    cout << " (9) Salir  " << endl;
}

void menu(ListaCliente * clientes, ListaProducto * productos, ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja, ThreadBalanceador * balanceador, Empacador * empacador, Facturador * facturador, RobotThread * robots[]){
    imprimirBanner();
    int opcion = 0;
    while (opcion != 9){
        cout << textoAzul("Menu Principal") << endl;
        imprimirOpciones();
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Clientes
                menuClientes(clientes);
                break;
            case 2: // Almacen (Productos)
                limpiarConsola();
                imprimirAlmacen(productos);
                continuar();
                break;
            case 3: // Pedidos
                limpiarConsola();
                menuPedidos(clientes, productos, prioridadAlta, prioridadMedia, prioridadBaja);
                break;
            case 4: // Balanceador
                menuBalanceador(balanceador);
                break;
            case 5:
                // Agregar codigo Fabricadores
                menuFabricadores(robots);
                break;
            case 6: // Picking
                menuPicking();
                break;
            case 7:
                // Agregar codigo Empacador
                menuEmpacador(empacador);
                break;
            case 8:
                // Agregar codigo facturador
                menuFacturador(facturador);
                break;
            case 9:
                return;
        }
        limpiarConsola();
    }
}

void menuClientes(ListaCliente * clientes){
    int opcion = 0;
    while (opcion != 3){
        limpiarConsola();
        cout << textoAzul("Menu Clientes") << endl;
        cout << " (1) Ver Clientes" << endl;
        cout << " (2) Agregar Cliente" << endl;
        cout << " (3) Regresar al Menú Principal  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Ver clientes
                limpiarConsola();
                cout << textoAzul("Clientes") << endl;
                imprimirClientes(clientes);
                continuar();
                break;
            case 2: // Agregar Clientes
                limpiarConsola();
                cout << textoAzul("Agregar Cliente") << endl;
                agregarClientes(clientes);
                continuar();
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
                continuar();
        }
    }
}

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

void agregarClientes(ListaCliente * clientes){
    string codigo = pedirString("Código del Cliente: ");
    if (clientes->buscarCliente(codigo)){
        cout << "Este cliente ya existe... Ingresa otro código." << endl;
        codigo = pedirString("Código del Cliente: ");
    }
    string nombre = pedirString("Nombre Cliente: ");
    int prioridad = -1;
    while (prioridad < 0){
        prioridad = pedirNumero("Prioridad Cliente: ");
        while (prioridad > 10){
            cout << "La prioridad debe ser de 1 a 10." << endl;
            prioridad = pedirNumero("Prioridad Cliente: ");
        }
    }
    clientes->insertarAlInicio(new Cliente(codigo, nombre, prioridad));
    actualizarClientes(clientes);
    cout << textoVerde("Se ha insertado el cliente exitosamente") << endl;
}

void imprimirAlmacen(ListaProducto * productos){
    cout << textoAzul("Almacen") << endl;
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
        limpiarConsola();
        cout << textoAzul("Menú Pedidos") << endl;
        cout << " (1) Ver pedidos" << endl;
        cout << " (2) Agregar pedido" << endl;
        cout << " (3) Regresar al Menú Principal" << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Imprimir Pedidos
                limpiarConsola();
                cout << textoAzul("Pedidos") << endl;
                imprimirPedidos(prioridadAlta, prioridadMedia, prioridadBaja);
                break;
            case 2: // Agregar pedido
                limpiarConsola();
                cout << textoAzul("Agregar Pedido") << endl;;
                agregarPedido(clientes, productos, prioridadAlta);
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
        }
        continuar();
    }
}

void imprimirPedidos(ListaPedido * prioridadAlta, ListaPedido * prioridadMedia, ListaPedido * prioridadBaja){
    if (prioridadAlta->isEmpty() && prioridadMedia->isEmpty() && prioridadBaja->isEmpty()){
        linea();
        cout << "No hay pedidos actualmente" << endl;
    }
    else {
        imprimirPedido(prioridadAlta, textoRojo("Alta"));
        imprimirPedido(prioridadMedia, textoAmarillo("Media"));
        imprimirPedido(prioridadBaja, textoVerde("Baja"));
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
            cout << "   Código Producto: " << tmpProducto->producto->codigoProducto << endl;
            cout << "   Cantidad Pedida: " << tmpProducto->producto->cantidadPedida << endl;
            cout << "   Cantidad Comprometida: " << tmpProducto->producto->cantidadComprometida << endl;
            if (tmpProducto->siguiente != NULL)
                cout << endl;
            tmpProducto = tmpProducto->siguiente;
        }
        tmp = tmp->siguiente; 
    }
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
        string codigoProducto = pedirString("   Código Producto: ");
        while(productos->buscarProductoPorCodigo(codigoProducto) == NULL){
            cout << "Este producto no existe" << endl;
            codigoProducto = pedirString("   Código Producto: ");
        }
        int cantidadPedida = -1;
        while (cantidadPedida <= 0){
            cantidadPedida = pedirNumero("   Cantidad requerida: ");
        }
        pedido->agregarProducto(new ProductoDePedido(codigoProducto, cantidadPedida, 0, numeroPedido));

        string seguirInsertando = pedirString("Agregar otro producto (Si o No): ");
        agregarProducto = false;
        if (seguirInsertando == "SI" || seguirInsertando == "Si" || seguirInsertando == "si"){
            agregarProducto = true;
        }
    }
    lista->encolar(pedido);
    cout << "Pedido agregado exitosamente" << endl;
}

void menuBalanceador(ThreadBalanceador * balanceador){
    int opcion = 0;
    while (opcion != 3){
        limpiarConsola();
        cout << textoAzul("Menú Balanceador") << endl;
        cout << "Estado: ";
        if (balanceador->paused)
            cout << textoRojo("Apagado") << endl;
        else
            cout << textoVerde("Encendido") << endl;
        cout << " (1) Encender Balanceador" << endl;
        cout << " (2) Apagar Balanceador" << endl;
        cout << " (3) Regresar al Menú Principal  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Encender Balanceador
                balanceador->Reanudar();
                break;
            case 2: // Apagar Balanceador
                balanceador->Pausar();
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
                continuar();
        }
    }
}

void menuFabricadores(RobotThread * robots[]){
    int opcion = 0;
    while (opcion != 3){
        limpiarConsola();
        cout << textoAzul("Menú Fabricadores") << endl;
        cout << " (1) Ver Fabricadores" << endl;
        cout << " (2) Seleccionar Fabricador" << endl;
        cout << " (3) Regresar al Menú Principal  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Imprimir Fabricadores
                limpiarConsola();
                cout << textoAzul("Fabricadores") << endl;
                imprimirFabricadores(robots);
                continuar();
                break;
            case 2:{
                int robotId = pedirNumero("ID Robot: ");
                while (!(robotId > 0 && robotId < 11 )){
                    cout << "ID Inválido" << endl;
                    robotId = pedirNumero("ID Robot: ");
                }
                menuFabricador(robots, robotId-1);
                break;
            }
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
        }
    }
}

void imprimirFabricadores(RobotThread * robots[]){
    for (int i = 0; i < 10; i++){
        linea();
        cout << "ID: " << robots[i]->id << endl;
        if(robots[i]->prioridad)
            cout << "Prioridad: Si" << endl;
        else
            cout << "Prioridad: No" << endl;
        
        if(!robots[i]->pausado)
            cout << "Estado: " << textoVerde("Encendido") << endl;
        else
            cout << "Estado: " << textoRojo("Apagado") << endl;

        if(robots[i]->categoria == "D")
            cout << "Categoría: Todas" << endl;
        else
            cout << "Categoría: " << robots[i]->categoria << endl;
    }
    linea();
}

void menuFabricador(RobotThread * robots[], int id){
    int opcion = 0;
    while (opcion != 5){
        limpiarConsola();
        cout << textoAzul("Fabricador ID " + to_string((id + 1))) << endl;
        if(robots[id]->prioridad)
            cout << "Prioridad: Si" << endl;
        else
            cout << "Prioridad: No" << endl;
        
        if(!robots[id]->pausado)
            cout << "Estado: " << textoVerde("Encendido") << endl;
        else
            cout << "Estado: " << textoRojo("Apagado") << endl;

        if(robots[id]->categoria == "D")
            cout << "Categoría: Todas" << endl;
        else
            cout << "Categoría: " << robots[id]->categoria << endl;
        cout << " (1) Cambiar Tipo" << endl;
        cout << " (2) Cambiar Prioridad" << endl;
        cout << " (3) Encender Fabricador" << endl;
        cout << " (4) Apagar Fabricador" << endl;
        cout << " (5) Regresar al Menú Fabricadores  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1:{
                cout << "  (A)" << endl;
                cout << "  (B)" << endl;
                cout << "  (C)" << endl;
                cout << "  (D): Todos" << endl;
                string tipo = pedirString("Ingrese la categoría: ");
                while(tipo != "A" && tipo != "B" && tipo != "C" && tipo != "D"){
                    tipo = pedirString("Ingrese el Tipo: ");
                }
                robots[id]->categoria = tipo;
                break;
            }
            case 2:
                robots[id]->prioridad = !robots[id]->prioridad;
                break;
            case 3:
                robots[id]->Reanudar();
                break;
            case 4:
                robots[id]->Pausar();
                break;
            case 5:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
        }
    }
}

void menuPicking(){
    cout << " (1) Ver Alistadores" << endl;
    cout << " (2) Ver Alistador especifico" << endl;
    cout << " (3) Encender un Alistador" << endl;
    cout << " (4) Apagar un Alistador" << endl;
    cout << " (5) Regresar al Menú Principal  " << endl;
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

void menuEmpacador(Empacador * empacador){
    int opcion = 0;
    while (opcion != 3){
        limpiarConsola();
        cout << textoAzul("Menú Empacador") << endl;
        cout << "Estado: ";
        if (empacador->pausado)
            cout << textoRojo("Apagado") << endl;
        else
            cout << textoVerde("Encendido") << endl;
        cout << " (1) Encender Empacador" << endl;
        cout << " (2) Apagar Empacador" << endl;
        cout << " (3) Regresar al Menú Principal  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Encender Empacador
                empacador->Reanudar();
                break;
            case 2: // Apagar Empacador
                empacador->Pausar();
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
                continuar();
        }
    }
}

void imprimirEmpacador(){

}

void menuFacturador(Facturador * facturador){
    int opcion = 0;
    while (opcion != 3){
        limpiarConsola();
        cout << textoAzul("Menú Facturador") << endl;
        cout << "Estado: ";
        if (facturador->pausado)
            cout << textoRojo("Apagado") << endl;
        else
            cout << textoVerde("Encendido") << endl;
        cout << " (1) Encender Facturador" << endl;
        cout << " (2) Apagar Facturador" << endl;
        cout << " (3) Regresar al Menú Principal  " << endl;
        opcion = pedirNumero("Opción deseada: ");
        switch (opcion){
            case 1: // Encender Facturador
                facturador->Reanudar();
                break;
            case 2: // Apagar Facturador
                facturador->Pausar();
                break;
            case 3:
                return;
            default:
                cout << "Esa opcion no esta disponible" << endl;
                continuar();
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
    if (option == "" || option == " "){
        cout << "No puede ser vacío." << endl;
        return pedirString(text);
    }
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

string textoRojo(string texto){
    return "\033[31m" + texto + "\033[0m";
}

string textoVerde(string texto){
    return "\033[32m" + texto + "\033[0m";
}

string textoAzul(string texto){
    return "\033[34m" + texto + "\033[0m";
}

string textoAmarillo(string texto){
    return "\033[33m" + texto + "\033[0m";
}
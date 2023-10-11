// Includes
#include "iostream"

using namespace std;

// Prototipos
void imprimirBanner();
void imprimirOpciones();
void resolverOpciones();
int pedirOpcion(string text);
void imprimirClientes();
void imprimirAlmacen();
void menuPedidos();
void imprimirPedidos();
void agregarProducto();
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

int verifyIntPositive(string number);
double verifyDoublePositive(string number);

// Funciones

void menu(){
    imprimirBanner();
    imprimirOpciones();
    resolverOpciones();
}

void imprimirBanner(){
    cout << "    ____  ____  ____  ____  _________    ____  ____  __________" << endl;
    cout << "   / __ \\/ __ \\/ __ )/ __ \\/ ____/   |  / __ )/ __ \\/  _/ ____/" << endl;
    cout << "  / /_/ / / / / __  / / / / /_  / /| | / __  / /_/ // // /" << endl;
    cout << " / _, _/ /_/ / /_/ / /_/ / __/ / ___ |/ /_/ / _, _// // /___ " << endl;
    cout << "/_/ |_|\\____/_____/\\____/_/   /_/  |_/_____/_/ |_/___/\\____/" << endl; 
    cout << "---------------------------------------------------------------" << endl;                                                                                              
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

void resolverOpciones(){
    int opcion = 0;
    while (opcion != 9){
        imprimirOpciones();
        opcion = pedirOpcion("Opcion deseada: ");
            switch (opcion){
                case 1:
                    // Agregar codigo clientes
                    imprimirClientes();
                    break;
                case 2:
                    // Agregar codigo Productos
                    imprimirAlmacen();
                    break;
                case 3:
                    // Agregar codigo Pedidos
                    menuPedidos();
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
void imprimirClientes(){

}

void imprimirAlmacen(){ // Imprimir productos

}

void menuPedidos(){
    cout << " (1) Ver pedidos" << endl;
    cout << " (2) Agregar pedido" << endl;
    cout << " (3) Salir  " << endl;
    int opcion = 0;
    while (opcion != 3){
        opcion = pedirOpcion("Opcion deseada: ");
            switch (opcion){
                case 1:
                    // Ver pedidos
                    imprimirPedidos();
                    break;
                case 2:
                    // Agregar pedido
                    agregarProducto();
                    break;
                case 3:
                    return;
                default:
                    cout << "Esa opcion no esta disponible" << endl;
            }
    }
}

// TODO
void imprimirPedidos(){

}

// TODO
void agregarProducto(){

}

void menuBalanceador(){
    cout << " (1) Encender Balanceador" << endl;
    cout << " (2) Apagar Balanceador" << endl;
    cout << " (3) Salir  " << endl;
    int opcion = 0;
    while (opcion != 3){
        opcion = pedirOpcion("Opcion deseada: ");
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
        opcion = pedirOpcion("Opcion deseada: ");
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
        opcion = pedirOpcion("Opcion deseada: ");
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
        opcion = pedirOpcion("Opcion deseada: ");
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
        opcion = pedirOpcion("Opcion deseada: ");
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
int pedirOpcion(string text){
    cout << endl << text;
    string option;
    getline(cin, option);
    int numberVerified = verifyIntPositive(option); 
    if (numberVerified < 1)
        return pedirOpcion(text);
    return numberVerified;
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
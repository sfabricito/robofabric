// Importaciones
#include "Cliente.h"

using namespace std;

// Prototipos
struct Producto;
struct NodoProducto;
struct ListaProducto;
Producto * separarProductoCadena(string cadena);
ListaProducto * cargarProductos();
void actualizarArchivoProductos(ListaProducto * lista);

// Estructuras
struct Producto{
    // Variables
    string codigo;
    int cantidadAlmacen;
    int tiempoFabricacion;
    string categoria;
    string ubicacionBodega;

    //Constructores
    Producto(){
        codigo = "";
        cantidadAlmacen = 0;
        tiempoFabricacion = 0;
        categoria = "";
        ubicacionBodega = "";
    }

    Producto(string codigoP, int cantidadAlmacenP, int tiempoFabricacionP, string categoriaP, string ubicacionBodegaP){
        codigo = codigoP;
        cantidadAlmacen = cantidadAlmacenP;
        tiempoFabricacion = tiempoFabricacionP;
        categoria = categoriaP;
        ubicacionBodega = ubicacionBodegaP;
    }
};

struct NodoProducto{
    // Variables
    Producto * producto;
    NodoProducto * siguiente;
    NodoProducto * anterior;

    // Constructores
    NodoProducto(){
        producto = NULL;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProducto(Producto * productoP){
        producto = productoP;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProducto(Producto * productoP, NodoProducto * siguienteP, NodoProducto * anteriorP){
        producto = productoP;
        siguiente = siguienteP;
        anterior = anteriorP;
    }

    // Procedimientos
    void imprimir(){
        cout << "Código: " <<  producto->codigo << " Cantidad Almacen: " << producto->cantidadAlmacen
            << " Tiempo Fabricación: " << producto->tiempoFabricacion << " Categoría: " << producto->categoria
            << " Ubicación Bodega: " << producto->ubicacionBodega << endl;
    }
};

struct ListaProducto{
    // Variables
    NodoProducto * primerNodo;
    NodoProducto * ultimoNodo;

    //Constructores
    ListaProducto(){
        primerNodo = ultimoNodo = NULL;
    }

    // Procedimientos
    bool isEmpty(){
		return primerNodo == NULL;
	}

    void insertarInicio(Producto * producto){
        if (isEmpty())
            primerNodo = ultimoNodo = new NodoProducto(producto);
        else{
            NodoProducto * nuevo = new NodoProducto(producto);
            nuevo->siguiente = primerNodo;
            primerNodo->anterior = nuevo;
			primerNodo = nuevo;
        }
    }

    void insertarFinal(Producto * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoProducto(producto);
		else{
			NodoProducto * nuevo = new NodoProducto(producto);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
    }

    NodoProducto * borrarAlInicio(){
        NodoProducto * borrado = primerNodo;
        if (primerNodo != NULL){
            if (primerNodo == ultimoNodo)
                primerNodo = ultimoNodo = NULL;
            else{
                primerNodo = primerNodo->siguiente;
                borrado ->siguiente = NULL;
                primerNodo->anterior = NULL;
            }
        }
        return borrado;
    }

    NodoProducto * borrarAlFinal(){
        NodoProducto * borrado = ultimoNodo;
        if (ultimoNodo != NULL){
            if (primerNodo == ultimoNodo)
                primerNodo = ultimoNodo = NULL;
            else{
                ultimoNodo = ultimoNodo->anterior;
                borrado->anterior = NULL;
                ultimoNodo->siguiente = NULL;
            }
        }
        return borrado;
    }

    void imprimir(){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL)
        {
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
    }

    bool buscarProductoPorCodigo(string _codigo){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL){
            if(tmp->producto->codigo == _codigo)
                return true;
            tmp = tmp->siguiente;
        }
        return false;
    }
};

Producto * separarProductoCadena(string cadena){
    string texto;
    string datos[5] = {"", "", "", "", ""};
    for (int i = 0; i < cadena.length(); i++){
        if (cadena[i] != '\t') 
            texto += cadena[i];
        else {
            for (int i = 0; i < 5; i++){
                if (datos[i] == ""){
                    datos[i] = texto;
                    texto = "";
                }
            }
        }
    }
    datos[4] = texto;
    return new Producto(datos[0], stoi(datos[1]), stoi(datos[2]), datos[3], datos[4]);
}

ListaProducto * cargarProductos(){
    ifstream archivo("Productos.txt");
    if (!archivo.is_open()) {
        cout << "Error archivo" << endl;
        return NULL;
    }
    string linea;
    ListaProducto * lista = new ListaProducto();

    while (getline( archivo, linea)) {
        lista->insertarFinal(separarProductoCadena(linea));
    }
     archivo.close();
     return lista;
}

void actualizarArchivoProductos(ListaProducto * lista){
    ofstream archivo("Productos.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    ListaProducto * tmp = lista;

    bool listaLlena = true;
    while (listaLlena){
        tmp->primerNodo->imprimir();
        archivo << tmp->primerNodo->producto->codigo << '\t';
        archivo << tmp->primerNodo->producto->cantidadAlmacen << '\t';
        archivo << tmp->primerNodo->producto->tiempoFabricacion << '\t';
        archivo << tmp->primerNodo->producto->categoria << '\t';
        archivo << tmp->primerNodo->producto->ubicacionBodega;
        tmp->primerNodo = tmp->primerNodo->siguiente;
        if (tmp->primerNodo != NULL)
            archivo << '\n';
        else 
            listaLlena = false;
    }
    archivo.close();
}
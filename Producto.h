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
bool verificarFormatoProducto(Producto * producto);
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

    NodoProducto * insertarInicio(Producto * producto){
        if (isEmpty())
            primerNodo = ultimoNodo = new NodoProducto(producto);
        else{
            NodoProducto * nuevo = new NodoProducto(producto);
            nuevo->siguiente = primerNodo;
            primerNodo->anterior = nuevo;
			primerNodo = nuevo;
        }
        return primerNodo;
    }

    NodoProducto * insertarFinal(Producto * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoProducto(producto);
		else{
			NodoProducto * nuevo = new NodoProducto(producto);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
        return ultimoNodo;
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

    NodoProducto * buscarProductoPorCodigo(string _codigo){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL){
            if(tmp->producto->codigo == _codigo)
                return tmp;
            tmp = tmp->siguiente;
        }
        return NULL;
    }

    string buscarUbicacionDeProducto(string _codigo){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL){
            if(tmp->producto->codigo == _codigo)
                return tmp->producto->ubicacionBodega;
            tmp = tmp->siguiente;
        }
        return NULL;
    }

    void imprimir(){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL)
        {
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
    }

    int getDuracion(string _codigo){
        NodoProducto * tmp = primerNodo;
        while (tmp != NULL){
            if (tmp->producto->codigo == _codigo){
                return tmp->producto->tiempoFabricacion;
            }
            tmp = tmp->siguiente;
        }
        return -1;
    }

    
};

Producto * separarProductoCadena(string cadena){
    int dato = 0;
    string datos[5];
    for (int i = 0; i < cadena.length(); i++){
        if (cadena[i] != '\t')
            datos[dato] += cadena[i];
        else 
            dato++;
    }
    return new Producto(datos[0], stoi(datos[1]), stoi(datos[2]), datos[3], datos[4]);
}

bool cargarProductos(ListaProducto * lista){
    ifstream archivo("Productos.txt");
    //ListaProducto * lista = new ListaProducto();
    if (!archivo.is_open()) {
        cout << "Error archivo" << endl;
        return false;
    }
    string linea;
    
    while(getline(archivo, linea)) {
        Producto * producto = separarProductoCadena(linea);
        if (!verificarFormatoProducto(producto))
            return false;
        else if (lista->buscarProductoPorCodigo(producto->codigo) != NULL)
            return false;  
        lista->insertarFinal(producto);
    }
    archivo.close();
    return true;
}

void actualizarArchivoProductos(ListaProducto * lista){
    ofstream archivo("Productos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    NodoProducto * tmp = lista->primerNodo;
    while (tmp != NULL){
        archivo << tmp->producto->codigo << '\t';
        archivo << tmp->producto->cantidadAlmacen << '\t';
        archivo << tmp->producto->tiempoFabricacion << '\t';
        archivo << tmp->producto->categoria << '\t';
        archivo << tmp->producto->ubicacionBodega << '\n';
        tmp = tmp->siguiente;
    }
    archivo.close();
}

bool verificarFormatoProducto(Producto * producto){
    if (producto->cantidadAlmacen < 0)
        return false;
    else if (producto->categoria != "A" & producto->categoria != "B" & producto->categoria != "C")
        return false;
    return true;
}
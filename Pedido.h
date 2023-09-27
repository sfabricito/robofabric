#include "Producto.h"

struct productoDePedido{
    // Variables
    string codigoProducto;
    int cantidadPedida;

    // Constructores
    productoDePedido(string _codigoProducto,int _cantidadPedida){
        codigoProducto = _codigoProducto;
        cantidadPedida = _cantidadPedida;
    }  
};

struct NodoProductoDePedido{
    // Variables
    productoDePedido * producto;
    NodoProductoDePedido * siguiente;
    NodoProductoDePedido * anterior;

    // Constructores
    NodoProductoDePedido(){
        producto = NULL;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProductoDePedido(productoDePedido * productoP){
        producto = productoP;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProductoDePedido(productoDePedido * productoP, NodoProductoDePedido * siguienteP, NodoProductoDePedido * anteriorP){
        producto = productoP;
        siguiente = siguienteP;
        anterior = anteriorP;
    }

    // Procedimientos
    void imprimir(){
        cout << "Código: " <<  producto->codigoProducto << " Cantidad Pedida: " << producto->cantidadPedida << endl;
    }
};

struct ListaProductoDePedido{
    // Variables
    NodoProductoDePedido * primerNodo;
    NodoProductoDePedido * ultimoNodo;

    //Constructores
    ListaProductoDePedido(){
        primerNodo = ultimoNodo = NULL;
    }

    // Procedimientos
    bool isEmpty(){
		return primerNodo == NULL;
	}

    void insertarInicio(productoDePedido * producto){
        if (isEmpty())
            primerNodo = ultimoNodo = new NodoProductoDePedido(producto);
        else{
            NodoProductoDePedido * nuevo = new NodoProductoDePedido(producto);
            nuevo->siguiente = primerNodo;
            primerNodo->anterior = nuevo;
			primerNodo = nuevo;
        }
    }

    void insertarFinal(productoDePedido * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoProductoDePedido(producto);
		else{
			NodoProductoDePedido * nuevo = new NodoProductoDePedido(producto);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
    }

    NodoProductoDePedido * borrarAlInicio(){
        NodoProductoDePedido * borrado = primerNodo;
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

    NodoProductoDePedido * borrarAlFinal(){
        NodoProductoDePedido * borrado = ultimoNodo;
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
        NodoProductoDePedido * tmp = primerNodo;
        while (tmp != NULL){
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
    }
};

struct Pedido{
    string codigoCliente;
    int numeroPedido;
    ListaProducto * productos;
};

vector<string> separarProductoDePedido(string cadena){
    vector<string> partes;
    string parte = "";
	bool flag = false;
	for(int i = 0 ; i < cadena.length() ; i++){
		//cout << "probando :           " << cadena[i] << endl;
		if(cadena[i] != '\t'){
			//cout << "se metio if 1"  << endl;
			parte += cadena[i];
			flag = true;
		}else if(cadena[i] == '\t'){
			//cout << "se metio if 2"  << endl;
			if(flag == true){
				partes.push_back(parte);
				flag = false;
			}
			parte = "";
		}
		//cout << "PARTESSSS:     " << parte << endl;
	} 
	partes.push_back(parte);	
    return partes;
}

bool revisarPedido(string _archivo,ListaCliente * listaCliente,ListaProducto * listaProducto){
    string rutaVieja = "Pedidos//";
    rutaVieja += _archivo;
    cout << "ruta vieja :  " << rutaVieja << endl;
    string rutaNueva = "Errores//";
    rutaNueva += _archivo;
    ifstream archivo(rutaVieja.c_str());
    if(archivo.is_open()){
        string linea;
        getline(archivo,linea);
        cout << "linea 1 :  " << rutaVieja << endl;
        getline(archivo,linea);
        string codigoCliente = linea;
        cout << "ruta nueva:  " << rutaNueva.c_str() << endl;
        if (!listaCliente->buscarCliente(codigoCliente))
            return false;
        
        vector<string> producto;
        int cantidad;
        while (getline(archivo,linea)){
            cout << "esta en while" << endl;
            producto = separarProductoDePedido(linea);
            cantidad = stoi(producto[1]);
            if(!listaProducto->buscarProductoPorCodigo(producto[0]) || cantidad < 1)
                return false;
        }
    } else return false;
    return true;
}

Pedido * convertirAPedido(string _archivo){
    ifstream archivo(_archivo.c_str());
    if(archivo.is_open()){

    }

}

struct threadLeerArchivo{
    
};

void leerArchivosEnCarpeta(string rutaCarpeta) {
    for (const auto& archivo : fs::directory_iterator(rutaCarpeta)) {
        if (fs::is_regular_file(archivo)) {
            cout << archivo.path().filename() << endl;
        }
    }
    
}
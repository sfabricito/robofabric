#include "Producto.h"
void leerArchivosEnCarpeta(string);
void revisarPedido(string ,ListaCliente *,ListaProducto *);
vector<string> separarProductoDePedido(string );
void leerArchivosEnCarpeta(string ,ListaCliente * ,ListaProducto * );


struct ProductoDePedido{
    // Variables
    string codigoProducto;
    int cantidadPedida, cantidadComprometida;
    // Constructores
    ProductoDePedido(string _codigoProducto,int _cantidadPedida, int _cantidadComprometida){
        codigoProducto = _codigoProducto;
        cantidadPedida = _cantidadPedida;
        cantidadComprometida = _cantidadComprometida;
    }  

    ProductoDePedido(){
        codigoProducto = "";
        cantidadPedida = 0;
        cantidadComprometida = 0;
    }  

    string toString(){
        return "Codigo producto: " + codigoProducto + " Cantidad: " + to_string(cantidadPedida);
    }
};

struct NodoProductoDePedido{
    // Variables
    ProductoDePedido * producto;
    NodoProductoDePedido * siguiente;
    NodoProductoDePedido * anterior;

    // Constructores
    NodoProductoDePedido(){
        producto = NULL;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProductoDePedido(ProductoDePedido * productoP){
        producto = productoP;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoProductoDePedido(ProductoDePedido * productoP, NodoProductoDePedido * siguienteP, NodoProductoDePedido * anteriorP){
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

    void insertarAlInicio (ProductoDePedido * productoPedido){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoProductoDePedido (productoPedido);
		else{
			NodoProductoDePedido * nuevo = new NodoProductoDePedido(productoPedido);
			nuevo->siguiente = primerNodo;
			primerNodo->anterior = nuevo;
			primerNodo = nuevo;
		}
	}

	void insertarAlFinal (ProductoDePedido * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoProductoDePedido (producto);
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
    // Variables
    string codigoCliente;
    int numeroPedido;
    ListaProductoDePedido * productosPedidos;

    // Constructores
    Pedido(){
        codigoCliente = "";
        numeroPedido = 0;
        productosPedidos = new ListaProductoDePedido();
    }

    Pedido(string _codigoCliente,int _numeroPedido){
        codigoCliente = _codigoCliente;
        numeroPedido = _numeroPedido;
        productosPedidos = new ListaProductoDePedido();
    }

    //Metodos
    string toString(){
        string pedidos;
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        while(tmp != NULL){
            pedidos += tmp->producto->codigoProducto + "\t" + to_string(tmp->producto->cantidadPedida) + "\n";
            tmp = tmp->siguiente;
        }
        return "Numero pedido: " + to_string(numeroPedido) + "\tCodigo Cliente: " + codigoCliente + "\nPedidos:\n" + pedidos;
    }

    void agregarProducto(ProductoDePedido * producto){
        productosPedidos->insertarAlFinal(producto);
    }
    
};

struct NodoPedido{
    // Variables
    Pedido * pedido;
    NodoPedido * siguiente;
    NodoPedido * anterior;

    // Constructores
    NodoPedido(){
        pedido = NULL;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoPedido(Pedido * productoP){
        pedido = productoP;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoPedido(Pedido * productoP, NodoPedido * siguienteP, NodoPedido * anteriorP){
        pedido = productoP;
        siguiente = siguienteP;
        anterior = anteriorP;
    }

    // Procedimientos
    void imprimir(){
        cout << pedido->toString() << endl;
    }
};

struct ListaPedido{//esto va a servir como las colas de nuestros pedidos
    // Variables
    NodoPedido * primerNodo;
    NodoPedido * ultimoNodo;

    //Constructores
    ListaPedido(){
        primerNodo = ultimoNodo = NULL;
    }

    // Procedimientos
    bool isEmpty(){
		return primerNodo == NULL;
	}

    void insertarFinal(Pedido * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoPedido(producto);
		else{
			NodoPedido * nuevo = new NodoPedido(producto);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
    }

    NodoPedido * borrarAlInicio(){
        NodoPedido * borrado = primerNodo;
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

    void imprimir(){
        NodoPedido * tmp = primerNodo;
        while (tmp != NULL){
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
    }
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
	} 
	partes.push_back(parte);	
    return partes;
}

void revisarPedido(string _archivo,ListaCliente * listaCliente,ListaProducto * listaProducto){
    string rutaVieja = "Pedidos//";
    rutaVieja += _archivo;
    string rutaNueva = "Errores//";
    rutaNueva += _archivo;
    string rutaBuena = "Procesados//";
    rutaBuena += _archivo;
    ifstream archivo(rutaVieja.c_str());
    if(archivo.is_open()){
        string linea;
        getline(archivo,linea);
        getline(archivo,linea);
        string codigoCliente = linea;
        if (!listaCliente->buscarCliente(codigoCliente)){
            archivo.close();
            rename(rutaVieja.c_str(),rutaNueva.c_str());
            return;
        }
        vector<string> producto;
        int cantidad;
        while (getline(archivo,linea)){
            producto = separarProductoDePedido(linea);
            cantidad = stoi(producto[1]);
            if(!listaProducto->buscarProductoPorCodigo(producto[0]) || cantidad < 1){
                archivo.close();
                rename(rutaVieja.c_str(),rutaNueva.c_str());
                return;
            }
        }
        archivo.close();
        rename(rutaVieja.c_str(),rutaBuena.c_str());
    } else {
        cout << "no se abrio" << endl;
        return;
    }
}

Pedido * convertirAPedido(string _archivo){
    ifstream archivo(_archivo.c_str());
    if(archivo.is_open()){
        Pedido * pedido = new Pedido();
        string cliente,linea;
        int codigo;
        getline(archivo,linea);
        codigo = stoi(linea);
        getline(archivo,linea);
        cliente = linea;
        pedido->codigoCliente = cliente;
        pedido->numeroPedido = codigo;
        vector<string> producto;
        int cantidad;
        while(getline(archivo,linea)){
            producto = separarProductoDePedido(linea);
            cantidad = stoi(producto[1]);
            //cout << "PRODUCTO:   " << producto[0] << "  CANTIDAD   " << cantidad << endl;
            //cout << "PRODUCTOOOOOOOOOOOOO: " << productoDePedido->codigoProducto << "  " <<productoDePedido->cantidadPedida  << endl;
            pedido->agregarProducto(new ProductoDePedido(producto[0],cantidad,0));
        }
        return pedido;
    }
    cout << "no se abrio" << endl;
    archivo.close();
    return NULL;
}


#include "Producto.h"
void leerArchivosEnCarpeta(string);
void revisarPedido(string ,ListaCliente *,ListaProducto *);
vector<string> separarProductoDePedido(string );
void leerArchivosEnCarpeta(string ,ListaCliente * ,ListaProducto * );
int obtenerValorPosicional(char);
struct ProductoDePedido{
    // Variables
    string codigoProducto;
    int cantidadPedida, cantidadComprometida, numeroDePedido;
    // Constructores
    ProductoDePedido(string _codigoProducto,int _cantidadPedida, int _cantidadComprometida,int _numeroDePedido){
        codigoProducto = _codigoProducto;
        cantidadPedida = _cantidadPedida;
        cantidadComprometida = _cantidadComprometida;
        numeroDePedido = _numeroDePedido;
    }  

    ProductoDePedido(){
        codigoProducto = "";
        cantidadPedida = 0;
        cantidadComprometida = 0;
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
        cout << "Código:\t" <<  producto->codigoProducto << "\tCantidad Pedida:\t" << producto->cantidadPedida << "\tCantidad Comprometida:\t" << producto->cantidadComprometida<< 
        "\tNumero De Pedido: " << producto->numeroDePedido << endl;
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

    NodoProductoDePedido * peek(){
        return primerNodo;
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
    bool atendido;
    ListaProductoDePedido * productosPedidos;

    // Constructores
    Pedido(){
        codigoCliente = "";
        numeroPedido = 0;
        productosPedidos = new ListaProductoDePedido();
        atendido = false;
    }

    Pedido(string _codigoCliente,int _numeroPedido){
        codigoCliente = _codigoCliente;
        numeroPedido = _numeroPedido;
        productosPedidos = new ListaProductoDePedido();
        atendido = false;
    }

    //Metodos
    string toString(){
        string pedidos;
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        while(tmp != NULL){
            pedidos += tmp->producto->codigoProducto + "\t" + to_string(tmp->producto->cantidadPedida) + "\t" + to_string(tmp->producto->cantidadComprometida)+"\n";
            tmp = tmp->siguiente;
        }
        return "Numero pedido: " + to_string(numeroPedido) + "\tCodigo Cliente: " + codigoCliente + "\nPedidos:\n" + pedidos;
    }

    void agregarProducto(ProductoDePedido * producto){
        productosPedidos->insertarAlFinal(producto);
    }


    bool isPedidoCompleto(){
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        while (tmp != NULL){
            if (tmp->producto->cantidadComprometida != tmp->producto->cantidadPedida)
                return false;
            tmp = tmp->siguiente;
            }
        return true;
    }

    ListaProductoDePedido * getProductosFaltantes(){
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        ListaProductoDePedido * nueva = new ListaProductoDePedido();
        while (tmp != NULL){
            if (tmp->producto->cantidadComprometida != tmp->producto->cantidadPedida)
                nueva->insertarAlFinal(tmp->producto);
            tmp = tmp ->siguiente;
        }
        return nueva;
    }

    void ajustarPedido(ListaProducto * productos){
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        while (tmp != NULL){
            NodoProducto * producto = productos->buscarProductoPorCodigo(tmp->producto->codigoProducto);
            if(producto != NULL){
                if (tmp->producto->cantidadPedida == tmp->producto->cantidadComprometida){
                    tmp = tmp->siguiente;
                    continue;
                }
                if (tmp->producto->cantidadPedida <= producto->producto->cantidadAlmacen){
                    tmp->producto->cantidadComprometida += tmp->producto->cantidadPedida;
                    producto->producto->cantidadAlmacen -= tmp->producto->cantidadComprometida;
                } else if (tmp->producto->cantidadPedida > producto->producto->cantidadAlmacen){
                    tmp->producto->cantidadComprometida += producto->producto->cantidadAlmacen;
                    producto->producto->cantidadAlmacen = 0;
                }
            }
            tmp = tmp->siguiente;
        }
        actualizarArchivoProductos(productos);   
    }

    int getDuracionDePicking(ListaProducto * productos){
        int res = 0;
        NodoProductoDePedido * tmp = productosPedidos->primerNodo;
        while (tmp != NULL){
            string ubicacion = productos->buscarUbicacionDeProducto(tmp->producto->codigoProducto);
            char columna = ubicacion[0];
            char fila1 = ubicacion[1];
            char fila2 = ubicacion[2];
            string fila = "";
            fila += fila1;
            fila += fila2;
            res += (obtenerValorPosicional(columna)-1  + stoi(fila)-1)*2;
            tmp = tmp->siguiente;
        }
        return res;
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

    void encolar(Pedido * producto){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoPedido(producto);
		else{
			NodoPedido * nuevo = new NodoPedido(producto);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
    }

    NodoPedido * peek(){
        return primerNodo;
    }

    NodoPedido * desencolar(){
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
		if(cadena[i] != '\t'){
			parte += cadena[i];
			flag = true;
		}else if(cadena[i] == '\t'){
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

int obtenerValorPosicional(char letra) {
    // Verifica si la letra es una letra minúscula o mayúscula
    if (letra >= 'a' && letra <= 'z') {
        // Si es minúscula, resta 'a' y suma 1 para obtener el valor posicional
        return letra - 'a' + 1;
    } else if (letra >= 'A' && letra <= 'Z') {
        // Si es mayúscula, resta 'A' y suma 1 para obtener el valor posicional
        return letra - 'A' + 1;
    } else {
        // Si no es una letra del alfabeto, devuelve -1 o maneja el error según tus necesidades
        return -1;
    }
}
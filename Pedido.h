#include "Producto.h"

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

void revisarPedido(string _archivo,ListaCliente * listaCliente,ListaProducto * listaProducto){
    string rutaVieja = "Pedidos/";
    rutaVieja += _archivo;
    cout << "ruta vieja :  " << rutaVieja << endl;
    ifstream archivo(rutaVieja.c_str());
    if(archivo.is_open()){
        string rutaNueva = "Errores/";
        rutaNueva += _archivo;
        string linea;
        getline(archivo,linea);
        cout << "linea 1 :  " << rutaVieja << endl;
        getline(archivo,linea);
        string codigoCliente = linea;
        cout << "Codigo:  " << codigoCliente << endl;
        cout << "ruta nueva:  " << rutaNueva.c_str() << endl;
        if (!listaCliente->buscarCliente(codigoCliente)){
            cout << "se metio al if" << endl;
            rename(rutaVieja.c_str(),rutaNueva.c_str());
        }
        vector<string> producto;
        int cantidad;
        while (getline(archivo,linea)){
            cout << "esta en while" << endl;
            producto = separarProductoDePedido(linea);
            cantidad = stoi(producto[1]);
            if(!listaProducto->buscarProductoPorCodigo(producto[0]) || cantidad < 1){
                rename(rutaVieja.c_str(),rutaNueva.c_str());
            }   
        }
    }
    //return true;   
}
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <filesystem>

using namespace std;

struct Cliente{
    string codigo;
    string nombre;
    int prioridad;

    Cliente(string cod, string nom, int prior){
        codigo = cod;
        nombre = nom;
        if(prior >= 10)
            prioridad = 10;
        else
            prioridad = prior;
    }

    string toString(){
        return "Codigo: " + codigo + "  Nombre: " + nombre + "  Prioridad: "  + to_string(prioridad);
    }
};
//-------------------------------------------------------------------------------------------------------------------
struct NodoCliente{
	Cliente * cliente;
	NodoCliente * sig;
	
	NodoCliente(Cliente * _cliente){
		cliente = _cliente;
		sig = NULL;
	}
 
    void imprimir(){
        cout << cliente->toString() << endl;
    }
};
//-------------------------------------------------------------------------------------------------------------------
struct ListaCliente{
	NodoCliente * primerNodo;
	
	ListaCliente(){ 
		primerNodo  = NULL;
	}	
	
	bool isEmpty(){
		return primerNodo == NULL;
	}
	
	void insertarAlInicio (Cliente * cliente){
		if (isEmpty())
			primerNodo = new NodoCliente (cliente);
		else{
			NodoCliente * nuevo = new NodoCliente (cliente);
			nuevo->sig = primerNodo;
			primerNodo = nuevo;
		}
	}
	
	// IMPRIMIR LISTA
	void imprimir(){
		NodoCliente * tmp = primerNodo;
		while (tmp != NULL){
			tmp->imprimir();
			tmp = tmp->sig; 		
		}
		cout << endl;
	}
	
	NodoCliente * borrarAlInicio(){
		NodoCliente * borrado = primerNodo;
		if (primerNodo != NULL){
			primerNodo = primerNodo->sig;
			borrado->sig = NULL;
		}
		return borrado;
	}

	bool buscarCliente(string _codigo){
		NodoCliente * tmp = primerNodo;
		while (tmp != NULL){
			if(tmp->cliente->codigo == _codigo)
				return true; 
			tmp = tmp->sig; 		
		}
		return false;
	}
	
};

vector<string> getCliente(string cadena){
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

void cargarClientes(ListaCliente * l){
    ifstream archivo("Clientes.txt");
    string linea;
    int prior;
    vector<string> cliente;
    while (getline(archivo,linea)){
        cliente = getCliente(linea);
        prior = stoi(cliente[2]);
        l->insertarAlInicio(new Cliente(cliente[0],cliente[1],prior));
    }
	archivo.close();
}

string getTexto(string nomArchivo){
	string linea, texto;
	ifstream archivo(nomArchivo);
	while (getline(archivo,linea)){
		texto += linea + "\n";
	}
	archivo.close();
	return texto;
}

void actualizarClientes(ListaCliente * l){
	ofstream archivo("Clientes.txt");
	string clientes;
	NodoCliente * tmp = l->primerNodo;
	while (tmp != NULL){
		clientes += tmp->cliente->codigo + "\t" + tmp->cliente->nombre + "\t" + to_string(tmp->cliente->prioridad) + "\n";
		tmp = tmp->sig;
	}	
	archivo << clientes;
	archivo.close();
}
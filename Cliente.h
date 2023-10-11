#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <filesystem>
#include <thread>
#include <string>
#include <atomic>
#include <mutex>
#include <ctime>
#include <iomanip>
#include <chrono>

namespace fs = std::filesystem;
using namespace std;

string getDateTime(){
	chrono::system_clock::time_point now = chrono::system_clock::now();
    // Convertir el tiempo en un objeto de tiempo local
    time_t currentTime = chrono::system_clock::to_time_t(now);
    // Utilizar la función localtime para obtener la estructura de tiempo local
    struct tm* localTime = localtime(&currentTime);
    // Formatear la estructura de tiempo en un string
    stringstream ss;
    ss << std::put_time(localTime, "%d-%m-%Y_%I-%M-%S");
    string dateTimeString = ss.str();
    // retorna el string con la fecha y hora
    return dateTimeString;
}

struct NodoString{
	string dato;
	NodoString* siguiente;
	NodoString * anterior;
	
	NodoString(string _dato){
		dato=_dato;
		siguiente = NULL;
	}

	void imprimir(){
		cout << dato << endl;
	}
};

struct ListaString{
	NodoString * primerNodo;
	NodoString * ultimoNodo;
	
	ListaString(){ 
		primerNodo = ultimoNodo = NULL;
	}	
	
	bool isEmpty(){
		return primerNodo == NULL;
	}
	
	void insertarAlInicio (string _dato){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoString (_dato);
		else{
			NodoString * nuevo = new NodoString(_dato);
			nuevo->siguiente = primerNodo;
			primerNodo->anterior = nuevo;
			primerNodo = nuevo;
		}
	}

	void insertarAlFinal (string _dato){
		if (isEmpty())
			primerNodo = ultimoNodo = new NodoString (_dato);
		else{
			NodoString * nuevo = new NodoString(_dato);
			nuevo->anterior = ultimoNodo;
			ultimoNodo->siguiente = nuevo;
			ultimoNodo = nuevo;
		}
	}

	// IMPRIMIR LISTA
	void imprimir(){
		NodoString * tmp = primerNodo;
		while (tmp != NULL){
			tmp->imprimir();
			tmp = tmp->siguiente; 		
		}
		cout <<endl;
	}

	NodoString * borrarAlInicio(){
		NodoString * borrado = primerNodo;
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
	
	NodoString * borrarAlFinal(){
		NodoString * borrado = ultimoNodo;
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

	string getInfo(){
		NodoString * tmp = primerNodo;
		string res = "";
		while (tmp != NULL){
			res += tmp->dato + "\n";
			tmp = tmp->siguiente;
		}		
		return res;
	}

};



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

	int getPrioridad(string _nombre){
		NodoCliente * tmp = primerNodo;
		while (tmp != NULL){
			if(tmp->cliente->codigo == _nombre)
				return tmp->cliente->prioridad; 
			tmp = tmp->sig; 		
		}
		return 0;
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
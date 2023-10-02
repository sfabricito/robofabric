#include "ThreadLeerArchivos.h"

int main(){
    ListaCliente * l1 = new ListaCliente();
    ListaProducto * l2 = cargarProductos(); 
    cargarClientes(l1);
    //l2->imprimir();
    //cout << endl;
    //l1->imprimir();
    return 0;
} 


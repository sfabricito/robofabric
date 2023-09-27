#include "Pedido.h"

int main(){
    ListaCliente * l1 = new ListaCliente();
    ListaProducto * l2 = new ListaProducto();
    cargarClientes(l1);
    l1->imprimir();
    //vector<string> cliente = getCliente("0	hola	7");
    //Cliente * c = new Cliente(cliente[0],cliente[1],12893);
    //cout <<cliente[0]  << endl;
    //cout <<cliente[1]  << endl;
    //cout <<cliente[2]  << endl;
    
    revisarPedido("prueba.txt",l1,l2);
    return 0;
} 


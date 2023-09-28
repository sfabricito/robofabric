#include "Pedido.h"

int main(){
    ListaProducto * lista = new ListaProducto();
    if(cargarProductos(lista))
        cout << "Cargados" << endl;
    else   
        cout << "Error cargando" << endl;

    lista->imprimir();

    return 0;
}
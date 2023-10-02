
#include "ThreadConvertirPedido.h"

int main(){
    ListaCliente * l1 = new ListaCliente();
    ListaProducto * l2 = new ListaProducto(); 
    //ListaPedido * alta, * media,* baja;
    cargarProductos(l2);
    cargarClientes(l1);
    //threadLeerArchivo myThread(l2, l1);
    //myThread.thread.join();
    Pedido * p1 = convertirAPedido("Procesados//prueba.txt");
    cout << p1->toString() << endl;
    leerArchivosEnCarpeta2("Procesados");
    //ThreadConvertirPedido thread(l1,alta,media,baja);
    
    //thread.thread.join();
    
    return 0;
} 

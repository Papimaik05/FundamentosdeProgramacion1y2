#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Descuentos.h"
#include "Clientes.h"

using namespace std;
int main() {
	tDescuento descuento;
	string nombre;
	ifstream archivo;
	tListaClientes lista;
	/*cout << "introduce el nombre del archivo a cargar" << endl;
	cin >> nombre;
	cargardescuento(nombre, descuento);*/
	lista = cargar(archivo);
	mostrar(lista);



	return 0;
}

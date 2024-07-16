#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Descuentos.h"

using namespace std;
bool cargardescuento(string nombre, tDescuento& descuento) {

	bool salida = true;
	ifstream archivo;

	archivo.open(nombre, ios::in);
	if (archivo.fail()) {
		salida = false;
		cout << "no se puede bro" << endl;
	}
	else if (salida) {

		for (int i = 0; i < MAX_DIAS; i++)
		{
			for (int j = 0; j < MAX_SECC; j++) {

				archivo >> descuento[i][j];
			}
		}
	}
	archivo.close();
	/*for (int k = 0; k < MAX_DIAS; k++)
	{
		for (int z = 0; z < MAX_SECC; z++) {

			cout << descuento[k][z];
			cout << "   ";
		}
		cout << endl;
	}
	cout << endl;*/


	return salida;
}
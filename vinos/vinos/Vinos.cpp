#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Vinos.h"

using namespace std;
void ordenar(tMaridaje mari) {
	string aux;
	for (int i = 0; i < mari.contador; i++)
	{
		for (int j = 0; j < mari.contador - 1; j++) {

			if (mari.puntero[j] < mari.puntero[j + 1]) {
				aux = mari.puntero[j + 1];
				mari.puntero[j + 1] = mari.puntero[j];
				mari.puntero[j] = aux;
			}
		}
	}
}
void mostrarvino(tVino vino) {
	cout << " Nombre del vino:  " << vino.nombre << endl;
	cout << "Numero de maridajes :  " << vino.arraymaridaje.contador << "  ";
	for (int i = 0; i < vino.arraymaridaje.contador; i++)
	{
		cout << vino.arraymaridaje.puntero[i] << "  ";
	}
	cout << endl;
	cout << "UVA tempranillo" << endl;
	cout << "origen nacional  " << vino.composicion[0][0] << "  origen importaciones  " << vino.composicion[0][1] << endl;
	cout << "UVA merlot" << endl;
	cout << "origen nacional  " << vino.composicion[1][0] << "  origen importaciones  " << vino.composicion[1][1] << endl;
	cout << "UVA syrah" << endl;
	cout << "origen nacional  " << vino.composicion[2][0] << "  origen importaciones  " << vino.composicion[2][1] << endl;
	cout << "UVA chardonai" << endl;
	cout << "origen nacional  " << vino.composicion[3][0] << "  origen importaciones  " << vino.composicion[3][1] << endl;
	cout << "UVA malvasia" << endl;
	cout << "origen nacional  " << vino.composicion[4][0] << "  origen importaciones  " << vino.composicion[4][1] << endl;
	cout << "------------------------------------------------------------------" << endl;


}
bool alimentolocalizado(tMaridaje& maridaje, string alimento,int i) {
	bool salida = false;
	
	if ((i < maridaje.contador)&&(salida==false)) {
		if (maridaje.puntero[i]==alimento)
		{
			salida = true;
		}
		else {
			i++;
			alimentolocalizado(maridaje, alimento, i);
		}
	}
	return salida;
}
void destruir(tMaridaje& maridaje) {
	delete maridaje.puntero;
}
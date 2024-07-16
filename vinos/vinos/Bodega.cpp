#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Vinos.h"
#include "Bodega.h"

using namespace std;

void inicializar(tListaVinos& lista) {
	for (int i = 0; i < TAM_MAX; i++)
	{

		lista.array[i] = new tVino;
	}
	lista.contador = 0;
}
void cargar(ifstream& archivo, tListaVinos& bodega) {
	inicializar(bodega);
	bool salida = true;
	string nvinos;
	string nombre;
	int nalimentos;
	string alimentos;
	int xd;
	string basura;
	archivo.open("vinos.txt", ios::in);
	if (archivo.fail())
	{
		salida = false;
		cout << "no se abre bro" << endl;
	}
	else if (salida) {
		getline(archivo, nvinos);
		bodega.contador = stoi(nvinos);
		for (int i = 0; i < bodega.contador; i++)
		{
			bodega.array[i]->arraymaridaje.contador = 0;
			bodega.array[i]->arraymaridaje.puntero = new string[10];
			getline(archivo, nombre);
			bodega.array[i]->nombre = nombre;
			archivo >> nalimentos;
			bodega.array[i]->arraymaridaje.contador = nalimentos;
			for (int j = 0; j < nalimentos; j++)
			{
				archivo >> alimentos;
				bodega.array[i]->arraymaridaje.puntero[j] = alimentos;
			}
			for (int k = 0; k < variedad; k++)
			{
				for (int w = 0; w < origen; w++) {

					archivo >> xd;
					bodega.array[i]->composicion[k][w] = xd;
				}
			}
			getline(archivo, basura);

		}
	}
	archivo.close();


	/*for (int p = 0; p < bodega.contador; p++)
	{
		cout << bodega.array[p]->nombre << endl;
		cout << bodega.array[p]->arraymaridaje.contador << endl;
		for (int b = 0; b < bodega.array[p]->arraymaridaje.contador; b++)
		{
			cout << bodega.array[p]->arraymaridaje.puntero[b] << endl;
		}
		cout << endl;
		for (int r = 0; r < variedad; r++)
		{
			for (int h = 0; h < origen; h++)
			{
				cout << bodega.array[p]->composicion[r][h] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/
	
}
void mostrar(tListaVinos& vinos) {
	for (int i = 0; i < vinos.contador; i++)
	{
		mostrarvino(*vinos.array[i]);
	}
}
void ordenarmarid(tListaVinos& bodega) {
	tVino *aux;
	for (int i = 0; i <bodega.contador; i++)
	{
		for (int j= 0; j < bodega.contador-1; j++)
		{
			if (bodega.array[j]->nombre < bodega.array[j+1]->nombre) {
				aux = bodega.array[j + 1];
				bodega.array[j + 1] = bodega.array[j];
				bodega.array[j] = aux;

			}
		}
	}
}
void destruir(tListaVinos& bodega) {
	for (int i = 0; i < bodega.contador; i++)
	{
		delete[]bodega.array[i];
	}
}
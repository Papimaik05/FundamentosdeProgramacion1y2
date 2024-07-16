#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Descuentos.h"
#include "Clientes.h"

using namespace std;

tListaClientes cargar(ifstream &archivo) {
	bool salida = true;
	tListaClientes lista;
	
	lista.contador = 0;
	string diasemana;
	string tarjeta;
	string nclientes;
	string nombre;
	string basura;
	archivo.open("clientess.txt", ios::in);
	if (archivo.fail())
	{
		salida = false;
		cout << "no se puede bro" << endl;
	}
	else if (salida) {
		getline(archivo, nclientes);
		lista.contador = stoi(nclientes);
		for (int i = 0; i < lista.contador; i++)
		{
			lista.array[i] = new tCliente;
			getline(archivo, nombre);
			lista.array[i]->nombre = nombre;
			getline(archivo, tarjeta);
			if (stoi(tarjeta)==1)
			{
				lista.array[i]->tarjeta = true;
			}
			else if (stoi(tarjeta) == 0) {
				lista.array[i]->tarjeta = false;
			}

			getline(archivo, diasemana);
			lista.array[i]->diasemana = stoi(diasemana);
			for (int j = 0; j < MAX_SECC; j++)
			{
				archivo >> lista.array[i]->listacompra.arrayestatico[j];
			}
			getline(archivo, basura);
		}


	}
	archivo.close();
	

	return lista;
}
void mostrar(tListaClientes lista) {
	for (int i = 0; i < lista.contador; i++)
	{
		cout << "NOMBRE DEL CLIENTE:    " << lista.array[i]->nombre << endl;
		cout << endl;
		if (lista.array[i]->tarjeta==true)
		{
			cout << "TARJETA: " << "SI" << endl;
			cout << endl;
		}
		else if (lista.array[i]->tarjeta == false) {
			cout << "TARJETA:  " << "NO" << endl;
			cout << endl;
		}
		cout << " COMPRA REALIZADA EL DIA " << lista.array[i]->diasemana << "  DE LA SEMANA" << endl;
		cout << endl;

		for (int j = 0; j < MAX_SECC; j++)
		{
			cout << "Gasto Seccion  " << j + 1 << " " << lista.array[i]->listacompra.arrayestatico[j] << "  " << endl;
		}
		cout << endl;
		
		
	}
}
void ordenar(tListaClientes& listac) {
	tCliente *aux;
	for (int i = 1; i < listac.contador; i++)
	{
		for (int j = 0; j < listac.contador-1; j++)
		{
			if (listac.array[j]->importe < listac.array[j + 1]->importe) {
				aux = listac.array[j + 1];
				listac.array[j + 1] = listac.array[j];
				listac.array[j] = aux;
			}
			else if (listac.array[j]->importe == listac.array[j + 1]->importe) {
				if (listac.array[j]->nombre < listac.array[j + 1]->nombre)
				{
					aux = listac.array[j + 1];
					listac.array[j + 1] = listac.array[j];
					listac.array[j] = aux;
				}
			}
		}
	}
}
void importe(tListaClientes& listac) {
	double importe;
	for (int i = 0; i < listac.contador; i++)
	{
		importe = 0;
		if(listac.array[i]->tarjeta==false){
			for (int j = 0; j < MAX_SECC; j++)
			{
				importe += listac.array[i]->listacompra.arrayestatico[j];
			}
			
		}
		else if (listac.array[i]->tarjeta == true) {
			

		}
		listac.array[i]->importe = importe;
	}
}
void seleccionar(tListaClientes listac, int nclientes, string nombre) {
	ofstream archivo;
	bool salida = true;
	int j = 0;
	archivo.open(nombre, ios::out);
	if (archivo.fail())
	{
		salida = false;
		cout << "no se puede crear" << endl;
	}
	else if (salida) {
		while (j < nclientes) {
			for (int i = 0; i < listac.contador; i++)
			{
				if (listac.array[i]->tarjeta == true) {
  					archivo << listac.array[i]->nombre << "   " << listac.array[i]->importe << endl;
					j++;
				}
			}
		}
		
	}
}
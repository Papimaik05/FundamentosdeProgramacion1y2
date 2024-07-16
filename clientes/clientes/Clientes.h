#pragma once
#ifndef CLIENTES_H
#define CLIENTES_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Descuentos.h"
#include "Clientes.h"
using namespace std;

const int  MAX_TAMANO = 50;

typedef double tArrayestatico[MAX_SECC];

typedef struct {
	tArrayestatico arrayestatico;
	int contador;
}tListacompra;

typedef struct {
	string nombre;
	bool tarjeta;
	int diasemana;
	tListacompra listacompra;
	double importe;
}tCliente;

typedef tCliente *arrayestatico[MAX_TAMANO];

typedef struct {

	arrayestatico array;
	int contador;
}tListaClientes;

tListaClientes cargar(ifstream &archivo);
void mostrar(tListaClientes lista);
void ordenar(tListaClientes& listac);
void importe(tListaClientes& listac);
void seleccionar(tListaClientes listac, int nclientes, string nombre)


#endif // !CLIENTES_H


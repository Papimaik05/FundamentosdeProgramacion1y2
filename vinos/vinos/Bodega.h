#pragma once
#ifndef BODEGA_H
#define BODEGA_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Vinos.h"

using namespace std;

const int TAM_MAX = 50;

typedef tVino *arrayvino[TAM_MAX];

typedef struct {
	arrayvino array;
	int contador;
}tListaVinos;

void inicializar(tListaVinos& lista);
void cargar(ifstream& archivo, tListaVinos& bodega);
void mostrar(tListaVinos& vinos);
void ordenarmarid(tListaVinos& bodega);
void destruir(tListaVinos& bodega);
#endif

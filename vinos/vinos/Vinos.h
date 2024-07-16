#pragma once
#ifndef VINOS_H
#define VINOS_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

const int variedad = 5;
const int origen = 2;

typedef string* arraydinamico;

typedef struct {
	arraydinamico puntero;
	int contador;
	int tamano;
}tMaridaje;

typedef double tComposicion[variedad][origen];

typedef struct {
	tComposicion composicion;
	string nombre;
	tMaridaje arraymaridaje;
}tVino;

void ordenar(tMaridaje mari);
void mostrarvino(tVino vino);
bool alimentolocalizado(tMaridaje& maridaje, string alimento);
void destruir(tMaridaje& maridaje);

#endif
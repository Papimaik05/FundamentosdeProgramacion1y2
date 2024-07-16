#pragma once
#ifndef LISTAASIGNATURAS_H
#define LISTAASIGNATURAS_H


using namespace std;

const int MAX_ASIGNATURAS = 30;

typedef struct {

    string codigo;
    string nombre;
    int creditos;

}tAsignaturas;

typedef tAsignaturas tArray[MAX_ASIGNATURAS];

typedef struct {

    tArray listaAM;
    int contador;

}tListaAsiganturas;


void cargarAsignaturas(tListaAsiganturas& lista, int numasignaturas, ifstream& archivo, double& coste);

void insertarAsignatura(tListaAsiganturas& lista, tAsignaturas asignatura);





#endif





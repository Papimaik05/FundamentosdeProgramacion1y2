#include<iostream>
#include<string>
#include<fstream>
#include"listaasignaturas.h"
#include"listamatriculas.h"


using namespace std;


void cargarAsignaturas(tListaAsiganturas& lista, int numasignaturas, ifstream& archivo, double& coste) {
    string aux;
    int creditos = 0;
    for (int i = 0; i < numasignaturas; i++) {

        getline(archivo, lista.listaAM[i].codigo);
        getline(archivo, lista.listaAM[i].nombre);
        getline(archivo, aux);
        lista.listaAM[i].creditos = stoi(aux);
        creditos += lista.listaAM[i].creditos;
    }
    coste += (creditos * 26.50);
    lista.contador = numasignaturas;
}
void insertarAsignatura(tListaAsiganturas& lista, tAsignaturas asignatura) {


    lista.listaAM[lista.contador] = asignatura;
    lista.contador++;

}
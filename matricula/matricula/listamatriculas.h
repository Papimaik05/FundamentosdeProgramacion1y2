#ifndef LISTAMATRICULAS_H
#define LISTAMATRICULAS_H


using namespace std;

const int MAX_MATRICULAS = 50;



typedef struct {

    string apellidos;
    string nombre;
    string NIF;
    string tipoestudios;
    tListaAsiganturas lista;
    double coste;

}tMatricula;

typedef tMatricula* tArray2[MAX_MATRICULAS];

typedef struct {

    tArray2 listaM;
    int contador;

}tListaMatriculas;

void cargarMatriculas(tListaMatriculas& listaMa);
void insertarMatriculas(tListaMatriculas& listaMa, tMatricula matricula);
void ordenatLista(tListaMatriculas& listaMa);
void mostrarMatriculas(tListaMatriculas listaMA);
#endif
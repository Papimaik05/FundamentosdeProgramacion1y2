#include<iostream>
#include<string>
#include<fstream>
#include"listaasignaturas.h"
#include"listamatriculas.h"

using namespace std;

void cargarMatriculas(tListaMatriculas& listaMa) {

    ifstream archivo;
    string aux;
    char aux2;

    archivo.open("matriculas.txt", ios::in);

    archivo >> listaMa.contador;
    archivo.get(aux2);

    for (int i = 0; i < listaMa.contador; i++) {
        double coste = 0;

        listaMa.listaM[i] = new tMatricula;

        getline(archivo, listaMa.listaM[i]->apellidos);
        getline(archivo, listaMa.listaM[i]->nombre);
        getline(archivo, listaMa.listaM[i]->NIF);
        getline(archivo, listaMa.listaM[i]->tipoestudios);
        getline(archivo, aux);
        int numasignaturas = stoi(aux);
        cargarAsignaturas(listaMa.listaM[i]->lista, numasignaturas, archivo, coste);
        listaMa.listaM[i]->coste = coste;
    }
    ordenatLista(listaMa);


}
void ordenatLista(tListaMatriculas& listaMa)
{
    tMatricula* aux3;
    for (int i = 1; i < listaMa.contador; i++) {
        for (int j = 0; j < listaMa.contador - 1; j++) {
            if (listaMa.listaM[j]->apellidos > listaMa.listaM[j + 1]->apellidos) {
                aux3 = listaMa.listaM[j];
                listaMa.listaM[j] = listaMa.listaM[j + 1];
                listaMa.listaM[j + 1] = aux3;
            }
        }
    }
}
void mostrarMatriculas(tListaMatriculas listaMA) { 
    cout << "La lista de matriculas cargadas es ..." << endl;
    for (int i = 0; i < listaMA.contador; i++) {
        cout << i + 1 << ". " << listaMA.listaM[i]->apellidos << "    " << listaMA.listaM[i]->NIF << "    (" << listaMA.listaM[i]->lista.contador << ")   " << listaMA.listaM[i]->coste << endl;
    }
}
void insertarMatriculas(tListaMatriculas& listaMa, tMatricula matricula) {

   
      listaMa.listaM[listaMa.contador] = &matricula;
      listaMa.contador++;
      ordenatLista(listaMa);
}
int seleccionarMatricula(tListaMatriculas listaMa) {
    int seleccion;
    mostrarMatriculas(listaMa);
    cout << "Elige una matricula" << endl;
    cin >>seleccion;
    seleccion = seleccion - 1;
    return seleccion;
}
void liberar(tListaMatriculas listaMa) {

    for (int i = 0; i < listaMa.contador; i++)
    {
        delete[]listaMa.listaM[i];
    }
}
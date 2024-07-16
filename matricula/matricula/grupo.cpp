
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "listaasignaturas.h"
#include "listamatriculas.h"
#include "grupo.h"
using namespace std;

tGrupo nuevo(int aula, string identificador) {
	tGrupo grupo;

	grupo.aula = aula;
	grupo.identificador = identificador;
	grupo.contador = 0;
	grupo.tamano = MAX_ALUM;
	grupo.arraydinamico = new tAlumno[grupo.tamano];
	

	return grupo;
}
void mostrarAlumno(tAlumno alumno) {
	cout << alumno.puntero->apellidos << "   " << alumno.correo << endl;
}
void insertaralumno(tGrupo& grupo,tAlumno alumno) {
	
	bool salida = false;
	for (int i = 0; (salida==false)&&(i < grupo.contador); i++)
	{
		if (grupo.arraydinamico[i].puntero->NIF==alumno.puntero->NIF) {
			cout << "ya esta introducido" << endl;
			salida = true;
		}
		else  {
			grupo.arraydinamico[grupo.contador] = alumno;
			grupo.contador++;
		}
	}
}
int buscaralumno(tGrupo grupo,tAlumno alumno ) {
	bool salida = false;
	int indice = -1;

	for (int i = 0;(salida==false) && (i < grupo.contador); i++)
	{
		if (grupo.arraydinamico[i].puntero->NIF == alumno.puntero->NIF) {
			salida = true;
			indice = i;
		}
	}
	return indice;
}
void eliminaralumno(tGrupo& grupo, tAlumno alumno) {
	int indice = buscaralumno(grupo,alumno);
	if (indice=-1)
	{
		cout << "Este alumno no esta en el grupo" << endl;
	}
	else
	{
		for (int i = indice; i < grupo.contador-1; i++)
		{
			grupo.arraydinamico[i] = grupo.arraydinamico[i + 1];
		}
		grupo.contador--;
	}
}
void mostrargrupo() {

}
void liberar(tGrupo& grupo) {
	delete grupo.arraydinamico;
}
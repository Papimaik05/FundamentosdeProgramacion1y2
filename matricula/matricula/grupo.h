#pragma once
#ifndef GRUPO_H
#define GRUPO_H



using namespace std;

const int MAX_ALUM = 10;

typedef tMatricula *tpuntero;
typedef struct {
	string correo;
	tpuntero puntero;
}tAlumno;

typedef tAlumno* tarraydinamico;
typedef struct {
	tarraydinamico arraydinamico;
	int contador;
	int aula;
	string identificador;
	int tamano;
}tGrupo;

tGrupo nuevo(int aula, string identificador);
void mostrarAlumno(tAlumno alumno);

#endif 


//#pragma once
//Proyecto realizado por Miguel Mateos Matías y Carlos Moreno Pérez
#ifndef TAD_H
#define TAD_H

#include "stdlib.h"
//Declaramos las librerias y las structs
typedef struct {
	int contador;
	int tamano;
	int* puntero;
} tConjunto;

void crearConjuntoVacio(tConjunto& c); //Creamos un conjunto vacio
bool pertenece(tConjunto c, int e); //Determina si el elemento pertenece a c o no
bool conjuntoVacio(tConjunto c); //Determina si el conjunto es vacio o no.
void insertar(tConjunto& c, int e);//Insertamos un elemento en un conjunto.Solo se mete una vez el elemento,si está ya incluido,lo ignoramos
void mostrar(tConjunto c);// Muestra por pantalla el conjunto
void eliminar(tConjunto& c, int e); //Elimina un elemento de un conjunto,si el elemento no esta incluido en el conjunto,no hace nada
bool operator==(tConjunto a, tConjunto b);// determina si dos conjuntos son iguales o no.
tConjunto operator*(tConjunto a, tConjunto b); //devuelve la interseccion de a y b.
tConjunto operator+(tConjunto a, tConjunto b);// devuelve la union de a y b.
tConjunto operator-(tConjunto a, tConjunto b);// devuelve la diferencia de a y b.
bool operator<<(tConjunto a, tConjunto b);// determina si a esta contenido en b o no.
#endif 


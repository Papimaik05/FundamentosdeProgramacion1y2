//#pragma once
#ifndef COORDENADA_H
#define COORDENADA_H
//Definimos la estructura de la coordenada.En esta estructura vamos a tener la posicion de la fila y la columna,además del color
typedef struct {
	int posfila;
	int poscolumna;
	int color;
}tCoor;


bool operator == (tCoor c1, tCoor c2); //Compara si dos coordenadas son iguales.
bool operator != (tCoor c1, tCoor c2); //Compara si dos coordenadas son distintas.
tCoor operator + (tCoor c1, tCoor c2); //Devuelve la coordenada resultante de sumar las dos coordenadas dadas por parámetros.


#endif

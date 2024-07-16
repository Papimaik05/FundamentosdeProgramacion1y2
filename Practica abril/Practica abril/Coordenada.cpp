#include "Coordenada.h"
#include "UtilidadesSYS.h"
#include <iostream>
#include <Windows.h>
using namespace std;

bool operator == (tCoor c1, tCoor c2) { //compara si dos coordenadas son iguales.
	return (c1.color == c2.color);
}
bool operator != (tCoor c1, tCoor c2) { //compara si dos coordenadas son distintas.
	return !(c1.color == c2.color);
}

tCoor operator + (tCoor c1, tCoor c2) { //devuelve la coordenada resultante de sumar las dos coordenadas dadas por parámetros.
	tCoor coordenada;
	coordenada.poscolumna =(c1.poscolumna + c2.poscolumna);
	coordenada.posfila = (c1.posfila + c2.posfila);
	return coordenada ;
}

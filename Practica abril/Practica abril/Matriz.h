#pragma once
#ifndef MATRIZ_H
#define MATRIZ_H

#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"
#include <fstream>
#include <sstream>
//Declaramos las librerias que vamos a utilizar y llamamos a los módulos que vamos a necesitar
using namespace std;

const int DIM_MAX = 64; //Definimos la dimension maxima de nuestra matriz
//Declaramos la estructura de nuestra matriz.En esta estructura vamos a encontrar el numero de filas,el numero de columnas y las coordenadas de nuestra  matriz
typedef struct {
	int nfilas;
	int ncolumnas;
	tCoor matriz[DIM_MAX][DIM_MAX];
}tMatrizChar;


bool cargar(tMatrizChar& mat, ifstream& ent);//Carga en la matriz los datos dados mediante el flujo de entrada.Devuelve falso si se produce un error en la lectura de los datos.
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2); //Compara si las dos matrices son iguales.
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2);//Intercambia las coordenadas pos1 y pos2 de la matriz.Devuelve falso si las posiciones no pertenecen al rango de la matriz.
bool swapF(tMatrizChar& mat, int f1, int f2);//Intercambia las filas f1 y f2 de la matriz.Devuelve falso si las filas no pertenecen al rango de la matriz.
bool swapC(tMatrizChar& mat, int c1, int c2);//Intercambia las columnas c1 y c2.Devuelve falso si las columnas no pertenecen al rango de la matriz.
bool swapD(tMatrizChar& mat, int d);//Intercambia las diagonales d y - d.Devuelve falso si las diagonales no pertenecen al rango de la matriz, o si la matriz no escuadrada.
bool voltearF(tMatrizChar& mat, int f);//Dar la vuelta a la fila f con respecto al eje vertical central de la imagen.Devuelve falso si la fila no pertenece al rango de lamatriz.
bool voltearC(tMatrizChar& mat, int c);//Dar la vuelta a la columna c con respecto al eje horizontal central de la imagen.Devuelve falso si la columna no pertenece al rango de la matriz.
bool voltearD(tMatrizChar& mat, int d);//Dar la vuelta a la diagonal d con respecto al centro de eje perpendicular de dicha diagonal.Devuelve falso si la diagonal no pertenece al rango de la matriz o si la matriz no es cuadrada.
void voltearV(tMatrizChar& mat);//Dar la vuelta a la imagen completa con respecto a su eje vertical central.
void voltearH(tMatrizChar& mat);//Dar la vuelta a la imagen completa con respecto a su eje horizontal central.
void rotarD(tMatrizChar& mat);//Rotar una imagen 90 grados en el sentido de las agujas del reloj.
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);//Intercambiar las celdas vecinas o adyacentes de las posiciones pos1 y pos2.
bool VoltearID(tMatrizChar& mat);//Voltear la imagen completa respecto a la diagonal principal.Devuelve falso si la matriz no es cuadrada.

#endif


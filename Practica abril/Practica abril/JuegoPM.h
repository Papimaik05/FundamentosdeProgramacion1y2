#pragma once
#ifndef JUEGOPM_H
#define JUEGOPM_H
#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"
#include "JuegoPM.h"
#include <fstream>
#include <string>
//Declaramos las librerias que vamos a utilizar y llamamos a los m�dulos que vamos a necesitar
//Declaramos nuestra estructura del juego.En esta estructura vamos a tener el modo elegido,el numero de acciones, la matriz reto y la matriz solucion.
typedef struct {
	int modo; 
	int accionesrestantes; 
	tMatrizChar matriz1;
	tMatrizChar matrizsolucion;
}tJuegoPM;
void mainJuegoPM();//Funci�n principal del juego.
int menu();//Men� para seleccionar el tipo de juego(1 o 2) o salir(0).
bool iniciar(tJuegoPM& jpm,int opcion);//Inicia los par�metros del juego que correspondan y llama a la funci�n cargar definida a continuaci�n.
bool cargar(tJuegoPM& jpm);//Abre el fichero que corresponda y llama a la funci�n cargar del m�dulo Matriz,ademas nos carga el numero de acciones.
void mostrar(tJuegoPM const& jpm);//Muestra el estado del reto utilizando las facilidades del m�dulo utilidadesSYS.Debe mostrar primero la imagen que se est�modificando y a continuaci�n la imagen objetivo.Debe mostrar tambi�n el n�mero deintentos que quedan.
bool jugar(tJuegoPM& jpm);//Permite realizar las acciones necesarias para jugar y controla si se ha llegado al l�mite de acciones permitidas;
bool accion(tJuegoPM& jpm);//Seg�n el comando de acci�n tecleado por el usuario,llama a la acci�n correspondiente definida en el m�dulo Matriz;
void modo1D();//Nos muestra las acciones disponibles en el modo 1D
void modo2D();//Nos muestra las acciones disponibles en el modo 2D
#endif


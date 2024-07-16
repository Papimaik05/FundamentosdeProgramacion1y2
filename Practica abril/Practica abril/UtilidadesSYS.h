//#pragma once
#ifndef UTILIDADESYS_H
#define UTILIDADESYS_H

typedef unsigned char uint8;  // Byte
//typedef unsigned short int usint; // entero pequeño sin signo

void chcp1252();// Funcion estética
void borrar(); // Borra todo lo que haya en la pantalla
void pausa(); // Anade una pausa cuando se llame a la funcion
void colorCTA(uint8 color, uint8 fondo); //Muestra colores

#endif

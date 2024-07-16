#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//LLamamos a las bibliotecas que vamos a necesitar,y a los modulos que vamos a utilizar
using namespace std;

bool cargar(tMatrizChar& mat, ifstream& ent) { 
	bool salida = true; //Creamos una variable bool que utilizaremos para salir del programa
	if (salida==true)
	{
		ent >> mat.nfilas; //Leemos el numero de filas
		ent >> mat.ncolumnas; //Leemos el numero de columnas
		for (int fila = 0; fila < mat.nfilas; fila++) //Bucle for para las filas y columnas
		{
			for (int columna = 0; columna < mat.ncolumnas; columna++)
			{
				ent >> mat.matriz[fila][columna].color; //Leemos la matriz
			}
		}
	
	}
	
	return salida;
}
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2) { 
	bool salida = true; //Creamos una variable bool que utilizaremos para salir del programa
	
	for (int fila = 0; (salida==true)&&(fila < mat1.nfilas) ; fila++) //Mientras la matriz sea igual
	{
		for (int columna = 0; (salida == true) && (columna < mat1.ncolumnas); columna++)
		{
			if (mat1.matriz[fila][columna]!=mat2.matriz[fila][columna]) //Si las dos matrices no son iguales, nos salimos
			{
				salida = false; 
			}
		}
	}
	return salida;
}
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
	bool permitido = false;
	tCoor aux;//creamos una auxiliar
	if (((pos1.poscolumna>mat.ncolumnas)||(pos1.posfila >mat.nfilas))||((pos2.poscolumna > mat.ncolumnas) || (pos2.posfila > mat.nfilas)))
	{
		permitido = true; 
	}
	else
	{	
	  aux.color = pos1.color; //Introducimos la posicion 1 al auxiliar
	  pos1.color = pos2.color; //Introducimos el valor 2 en el valor 1
	  pos2.color = aux.color; //Introducimos el valor 1 en el valor 2,a traves del auxiliar
	}


	return permitido;
}
bool swapF(tMatrizChar& mat, int f1, int f2)
{
	bool permitido = false; //creamos una variable bool para salir del programa
	tCoor aux; //creamos una auxiliar
	if ((f1>mat.nfilas)||(f2>mat.nfilas))
	{
		permitido = true; //En caso de que las filas seleccionadas sean mayor que el numero de filas maximo,nos da error
	}
	else
	{
			for (int columna = 0; columna < mat.ncolumnas; columna++)
			{
				aux.color= mat.matriz[f1][columna].color; //Introducimos el valor de la fila 1 en la auxiliar
				mat.matriz[f1][columna].color = mat.matriz[f2][columna].color; //Introducimos el valor de la fila 2 ,en el valor de la fila 1
				mat.matriz[f2][columna].color = aux.color; //Introducimos el valor de la fila 1 ,en el valor de la fila 2 a traves de la auxiliar
			}
	}

	return permitido;
}
bool swapC(tMatrizChar& mat, int c1, int c2) 
{
		bool permitido = false; //creamos una variable bool para salir del programa
		tCoor aux; //creamos una auxiliar
		if ((c1 > mat.ncolumnas) || (c2 > mat.ncolumnas))
		{
			permitido = true; //En caso de que las columnas seleccionadas sean mayor que el numero de columnas maximo,nos da error
		}
		else
		{
			for (int fila = 0; fila < mat.nfilas; fila++)
			{
					aux.color = mat.matriz[fila][c1].color; //Introducimos el valor de la columnna 1 en la auxiliar
					mat.matriz[fila][c1].color = mat.matriz[fila][c2].color;//Introducimos el valor de la columna 2 ,en el valor de la columna 1
					mat.matriz[fila][c2].color = aux.color;//Introducimos el valor de la columna 1 ,en el valor de la columna 2 a traves de la auxiliar
			}
		}

		return permitido;
}
bool swapD(tMatrizChar & mat, int d)

	{
	bool permitido = false;  //creamos una variable bool para salir del programa
	tCoor aux;//creamos una auxiliar
	if ((mat.ncolumnas!=mat.nfilas)||(d>mat.ncolumnas)&&(d>mat.nfilas))
	{
		permitido = true;  //Si las diagonales no pertenecen al rango de la matriz, o si la matriz no escuadrada,da error
	}
	else
	{
		for (int fila = 0; fila < mat.nfilas; fila++)
		{
			aux.color = mat.matriz[fila][d].color; //Introducimos el valor de la columna(que es nuestra d) en la auxiliar
			mat.matriz[fila][d].color = mat.matriz[d][fila].color; 
			mat.matriz[d][fila].color = aux.color;
			d++; //aumenta la d elegida
		}
		
	}

	return permitido;
    }
bool voltearF(tMatrizChar& mat, int f)
{
	bool permitido = false; //creamos una variable bool para salir del programa
	tCoor aux;
	if ((f > mat.nfilas) || (f > mat.nfilas)) //En caso de que la fila elegida sea mayor que el numero de filas maximo
	{
		permitido = true;
	}
	else
	{
		for (int columna = 0; columna < mat.ncolumnas/2; columna++) //Lo dividimos entre 2 para que no se haga dos veces
		{
			aux.color = mat.matriz[f][columna].color; //Aqui encontramos un sistema para que se cumpla nuestra funcion
			mat.matriz[f][columna].color = mat.matriz[f][mat.ncolumnas- columna-1].color;
			mat.matriz[f][mat.ncolumnas - columna - 1].color = aux.color;
		}
	}
	return permitido;
}
bool voltearC(tMatrizChar& mat, int c)
{
	bool permitido = false; //creamos una variable bool para salir del programa
	tCoor aux;
	if ((c > mat.ncolumnas) || (c > mat.ncolumnas))  //en caso de que la columna no pertenezca al rango de la matriz
	{
		permitido = true;
	}
	else
	{
		for (int fila = 0; fila < mat.nfilas / 2; fila++) //Lo dividimos entre dos para que no se haga dos veces
		{
			//Aqui encontramos un sistema para que se cumpla nuestra funcion
			aux.color = mat.matriz[fila][c].color;
			mat.matriz[fila][c].color = mat.matriz[mat.nfilas-fila-1][c].color;
			mat.matriz[mat.nfilas - fila - 1][c].color = aux.color;
		}
	}
	return permitido;
}
bool voltearD(tMatrizChar& mat,int d)
{
	bool permitido = false; //creamos una variable bool para salir del programa
	tCoor aux;
	if ((d > mat.nfilas) || (d > mat.ncolumnas)||(mat.ncolumnas!=mat.nfilas))
	{
		permitido = true; //Devuelve falso si la diagonal no pertenece al rango de la matriz o si la matriz no es cuadrada.
	}
	else
	{
		//Aqui encontramos un sistema para que se cumpla  nuestra funcion
		for (int fila = 0; fila < (mat.ncolumnas - d )/ 2; fila++)
		{
			aux.color = mat.matriz[fila][d+fila].color;
			mat.matriz[fila][d+fila].color = mat.matriz[mat.ncolumnas - 1 - (d + fila)][mat.ncolumnas-1-fila].color;
			mat.matriz[mat.ncolumnas-1-(d+fila)][mat.ncolumnas - 1 - fila].color = aux.color;
		}
	}
	return permitido;
}
void voltearV(tMatrizChar& mat)
{
	tCoor aux;
	for (int f = 0; f < mat.nfilas; f++)
	{
		for (int columna = 0; columna < mat.ncolumnas / 2; columna++) //Lo dividimos entre dos para que no se haga dos veces
		{
			//Aqui encontramos un sistema para que se cumpla  nuestra funcion
			aux.color = mat.matriz[f][columna].color;
			mat.matriz[f][columna].color = mat.matriz[f][mat.ncolumnas - columna - 1].color;
			mat.matriz[f][mat.ncolumnas - columna - 1].color = aux.color;
		}
	}

}
void voltearH(tMatrizChar& mat) // : dar la vuelta a la imagen completa conrespecto a su eje horizontal central.
{	
 tCoor aux;
 for (int c = 0; c < mat.ncolumnas; c++)
 {
	 for (int fila = 0; fila < mat.nfilas / 2; fila++) //Lo dividimos entre dos para que no se haga dos veces
	 {
		 //Aqui encontramos un sistema para que se cumpla  nuestra funcion
		 aux.color = mat.matriz[fila][c].color;
		 mat.matriz[fila][c].color = mat.matriz[mat.nfilas - fila - 1][c].color;
		 mat.matriz[mat.nfilas - fila - 1][c].color = aux.color;
	 }
 }
}
void rotarD(tMatrizChar& mat) /* : rotar una imagen 90 grados en el sentido de lasagujas del reloj.*/
{
	tMatrizChar aux;

	for (int fila = 0 ; fila < mat.nfilas ; fila++)
	{
		//Aqui encontramos un sistema para que se cumpla  nuestra funcion

		for (int columna = 0; columna < mat.ncolumnas; columna++)
		{
			aux.matriz[fila][columna].color = mat.matriz[fila][columna].color;
		}
	}
	for (int fila = 0; fila < mat.ncolumnas; fila++)
	{
		for (int columna = 0; columna < mat.nfilas; columna++)
		{
			mat.matriz[fila][columna].color = aux.matriz[mat.nfilas - 1 - columna][ fila].color;
		}
	}
	int aux2;
	aux2 = mat.ncolumnas;
	mat.ncolumnas = mat.nfilas;
	mat.nfilas = aux2;
	//Se intercambia el numero de filas por el de columnas y viceversa,a la hora de girarlo
}
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2)
{
	{
		bool permitido = false; //creamos una variable bool para salir del programa
		if (((mat.ncolumnas<6)&&(mat.nfilas<6)) || (pos1.posfila<1) || (pos2.posfila<1)|| (pos1.poscolumna < 1) || (pos2.poscolumna < 1)) 
		{
			permitido = true;
		}
		else
		{
			for (int fila = -1; fila < 2; fila++)
			{
				for (int columna = -1; columna < 2; columna++)
				{
					if (fila!=0||columna!=0)
					{
						//Aqui encontramos un sistema para que se cumpla  nuestra funcion
						tCoor aux;
						aux.color = mat.matriz[pos1.posfila + fila][pos1.poscolumna + columna].color;
						mat.matriz[pos1.posfila + fila][pos1.poscolumna + columna].color = mat.matriz[pos2.posfila + fila][pos2.poscolumna + columna].color;
						mat.matriz[pos2.posfila + fila][pos2.poscolumna + columna].color = aux.color;
					}
					
				}
			}

		}

		return permitido;
	}
}
bool VoltearID(tMatrizChar& mat) 
{
	bool permitido = false; //creamos una variable bool para salir del programa
	tMatrizChar aux;
	if (mat.ncolumnas != mat.nfilas) //Si la matriz no es cuadrada
	{
		permitido = true;
	}
	else
	{
		//Aqui encontramos un sistema para que se cumpla  nuestra funcion
		for (int fila = 0; fila < mat.nfilas; fila++)
		{

			for (int columna = 0; columna < mat.ncolumnas; columna++)
			{
				aux.matriz[fila][columna].color = mat.matriz[fila][columna].color;

			}
		}
		for (int fila = 0; fila < mat.nfilas; fila++)
		{

			for (int columna = 0; columna < mat.ncolumnas; columna++)
			{

				mat.matriz[fila][columna].color = aux.matriz[columna][fila].color;
			}
		}

	}

	return permitido;
}
//Proyecto realizado por Miguel Mateos Matías y Carlos Moreno Pérez
#include "TAD.h"
#include <iostream>

//Declaramos las variables
using namespace std;

void crearConjuntoVacio(tConjunto& c) {
	c.tamano = 10; //Inicializamos el tamano en 10
	c.contador = 0; // Inicializamos el contador en 0
	c.puntero = new int[c.tamano]; //Creamos el array dinamico
	for (int i = 0; i < c.tamano; i++) //Recordamos al programa que cada elemento esta vacio.
	{
		c.puntero[i] = NULL;
	}
}
bool pertenece(tConjunto c, int e) {
	bool salida = false; 
	for (int i = 0;i < c.contador; i++) //Recorremos todos los elementos 
	{
		if (e==c.puntero[i]) //SI e es igual al elemento
		{
			//cout <<  c.puntero[i]<<" SI pertenece a c " << endl; ??Esto lo usamos para comprobar si nuestra funcion,funciona correctamente
			salida = true;
		}
	}
	return salida;
}
bool conjuntoVacio(tConjunto c) {
	bool salida = false;
	if (c.contador==0) //Si el numero de elementos es 0
	{
		salida = true; 
	}
	
	return salida;
}
void insertar(tConjunto& c, int e) {
	int* aux; //declaramos un auxiliar
	bool repetir = true; //declaramos una variable por si se repite
	for (int i = 0; i < c.contador; i++) //Recorremos nuestro conjunto
	{
		if (e == c.puntero[i]) //Lo utilizamos para saber si el elemento ya esta introducido
		{
			cout << c.puntero[i]<<" ya esta introducido" << endl;
			repetir = false;
		}
	}
	if (repetir) //Si no esta repetido
	{

		if (c.contador >= c.tamano) { //Si pasamos de 10 posiciones
			c.tamano += 10;//Aumentamos el tamano (+10)
			aux = new int[c.tamano]; //declaramos el puntero aux
			for (int i = 0; i < c.contador; i++)
			{
				aux[i] = c.puntero[i]; //copiamos el conjunto en nuestro auxiliar
			}
			aux[c.contador] = e; //Introducimos e
			delete[] c.puntero; //Borramos nuestro puntero
			c.puntero = new int[c.tamano];  //Volvemos a declarar el c.puntero
			c.contador++; //aumentamos el contador al introducir el elemento
			for (int i = 0; i < c.contador; i++)
			{
				c.puntero[i] = aux[i];   //Volvemos a copiar lo que tenemos en aux en nuestro puntero original(Ahora con mas tamaño)
			}
			delete[] aux; //borramos el puntero auxiliar
		}
		else
		{

			c.puntero[c.contador] = e; //Introducimos el elemento en nuestro conjunto
			c.contador++; //aumentamos el numero de elementos

		}
	 }
	}
void mostrar(tConjunto c) {
	for (int i = 0; i < c.contador; i++)
	{
		cout << c.puntero[i] << endl; //mostramos todos los elementos de nuestro conjunto
	}
}
void eliminar(tConjunto& c, int e) {
	int* aux; //declaramos auxiliar
	bool encontrado = false; //declaramos variable para comprobar que el elemento está en nues
	for (int i = 0; (i < c.contador)&&(encontrado==false); i++) //Recorremos todos los elementos
	{
		if (e == c.puntero[i]) //SI e es igual al elemento
		{
			cout << "E si pertenece a c " << endl;
			for (int j = i; j < c.contador; j++)
			{
				c.puntero[j] = c.puntero[j + 1]; //Funcion para eliminar el elemento
				encontrado = true;

				if (c.contador <= c.tamano / 4) { //Si al eliminar un elemento el numero de posiciones con informacion es menor del 25 %,restamos 10 al tamano
					c.tamano -= 10; //Se resta 10 
				    aux = new int[c.tamano];
					for (int k = 0; k < c.contador; k++)
					{
						aux[k] = c.puntero[k]; //copiamos el conjunto a nuestro auxiliar
					}
					delete[] c.puntero; //borramos el puntero
					c.puntero = new int[c.tamano]; //Creamos el puntero con nuestro nuevo tamano
					for (int l = 0; l < c.contador; l++)
					{
						c.puntero[l] = aux[l]; //copiamos los valores del auxiliar al nuevo conjunto,con su nuevo tamano
					}
					delete[] aux; //borramos el puntero auxiliar
				}
			}
			
			
		}
	}
	c.contador--; //disminuimos un elemento al contador
}
bool operator==(tConjunto a, tConjunto b) {
	bool salida = true;
	for (int i = 0; (i < a.contador)&&(salida==true); i++) //recorremos a,mientras los elementos sean iguales
	{
		for (int j = 0; j < (b.contador)&&(salida == true); j++) { //recorremos b,mientras los elementos sean iguales
			if (a.puntero[i]==b.puntero[j]) //Si A es igual a B
			{
				salida = true;
			}
			else //si no lo es
			{
				salida = false;
			}
		}
	}
	return salida;
	
}
tConjunto operator * (tConjunto a, tConjunto b) {
	tConjunto inter;//declaramos nuevo conjunto
	if (a.tamano < b.tamano) //Como mucho la interseccion va a tener el tamano del mas pequeno
	{
		inter.tamano = a.tamano;
	}
	else
	{
		inter.tamano = b.tamano;
	}
	inter.puntero = new int[inter.tamano]; //declaramos el puntero
	inter.contador = 0; //declaramos el numero de elementos
	for (int i = 0; i < a.contador; i++) //recorremos a
	{
		for (int j = 0; j < b.contador; j++)//recorremos b
		{
			if (a.puntero[i] == b.puntero[j]) //si el elemento es igual
			{
				inter.puntero[inter.contador] = a.puntero[i]; //lo anadimos a nuestro conjunto
				inter.contador++;//aumentamos el numero de elementos,cada vez 
			}
		}
	}
	return inter;
}
tConjunto operator+(tConjunto a, tConjunto b) {

	tConjunto unio; //declaramos el conjunto
	unio.tamano = a.tamano + b.tamano; //el tamano como mucho va a tener la suma de los 2 conjuntos
	unio.puntero = new int[unio.tamano];
    unio.contador = 0;
	for (int i = 0; i < a.contador; i++)
	{
		unio.puntero[i] = a.puntero[i]; //copiamos a en nuestro nuevo conjunto
		unio.contador++; //actualizamos el numero de elementos
	}
	for (int j = 0; j < b.contador; j++)
	{
		insertar(unio, b.puntero[j]); //llamamos  a la funcion insertar para meter los elementos de b,(sin incluir los repetidos)
	}
	
	return unio;
	
}
tConjunto operator-(tConjunto a, tConjunto b) {
	tConjunto diferencia; //declaramos el conjunto
	diferencia.tamano = a.tamano;
	diferencia.puntero = new int[10];
	diferencia.contador = 0;
	bool salida = true;

	for (int i = 0; i < a.contador; i++)//recorremos el array
	{
		salida = pertenece(b, a.puntero[i]); //Usamos la funcion pertenece para saber los elementos que se repiten
		if (salida==false)
		{
			diferencia.puntero[diferencia.contador] = a.puntero[i]; //introducimos todos los elementos menos los que se repiten
			diferencia.contador++;
			
		}
		
	}
	return diferencia;
}
bool operator<<(tConjunto a, tConjunto b) {
	bool salida = true;
	for (int i = 0;salida && i < a.contador; i++)
	{
		salida = pertenece(b, a.puntero[i]); //usamos la funcion pertenece para ver si los elementos de a estan en b
	}
	return salida;
}
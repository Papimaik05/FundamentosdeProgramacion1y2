//Realizado por Miguel Mateos Matias y Carlos Moreno Perez, GRUPO B
#include <iostream>
#include <string>
#include <fstream>
#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"
#include "JuegoPM.h"
//LLamamos a las bibliotecas que vamos a necesitar,y a los modulos que vamos a utilizar
using namespace std;
void mainJuegoPM() { 
	tJuegoPM juegopartida;
	jugar(juegopartida); 
	//llamamos a las funciones mostrar y jugar,que van a ser la base de nuestro programa
}
int menu() {
	int opcion;
	do
	{
		//Pedimos al usuario que elija modo
		cout << "1-Modo 1D" << endl;
		cout << "2-Modo 2D" << endl;
		cout << "3- Salir" << endl;
		cin >> opcion;
		cout << "Has elegido el modo " << opcion <<"D"<< endl; //Mostramos el modo elegido
	} while ((opcion != 1) && (opcion != 2) && (opcion != 3)); //Se repite infinitamente hasta que hayamos seleccionado una accion disponible

	return opcion;
} 
bool iniciar(tJuegoPM& jpm,int opcion) { 
	bool salida = true; //Creamos una variable bool que utilizaremos para salir del programa
	salida = cargar(jpm); //Llamamos a la funcion cargar
	if (salida==false)
	{
		cout << "No se han podido coger los parámetros" << endl; //En caso de error
	}
	return salida;
}
bool cargar(tJuegoPM& jpm) {
	ifstream archivo; // Variable para el archivo de lectura
	string nombrereto; // Variable string para el nombre del archivo
	bool salida = true;
	cout << "Escribe el nombre del reto" << endl; //Pedimos el nombre del archivo
	cin >> nombrereto; //Introducimos el nombre
	string nombrecompleto = (nombrereto + "_") + to_string(jpm.modo) + "D.txt"; //Lo utilizamos para no tener que poner _ el modo y .txt
	archivo.open(nombrecompleto, ios::in); //abrimos el archivo de lectura
	if (archivo.fail()) //En caso de error
	{
		salida = false;
		cout << "No se ha podido abrir el archivo" << endl;
	}
	else
	{
		cargar(jpm.matriz1,archivo); //Cargamos la matriz reto
		cargar(jpm.matrizsolucion, archivo); //Cargamos la matriz solucion
		archivo >> jpm.accionesrestantes; // Cargamos el numero de acciones
	}
	return salida;
}
void mostrar(tJuegoPM const& jpm) {
	//Pintamos la matriz reto
	cout << "Matriz reto" << endl;
	cout << " ";
	for (int i = 0; i < jpm.matriz1.ncolumnas; i++)
	{
		
		cout << i%10 << " "; //Lo utilizamos para que aparezcan los numeros encima de las columnas(desde el 0 hasta el 9)

	}
	cout << endl;
	for (int fila = 0; fila < jpm.matriz1.nfilas; fila++)
	{
		cout << fila %10; //Lo utilizamos para que aparezcan los numeros a la izquierda de las filas(desde el 0 hasta el 9)
		for (int columna = 0; columna < jpm.matriz1.ncolumnas; columna++)
		{
			colorCTA(15, jpm.matriz1.matriz[fila][columna].color); //Utilizamos la función colorCTA que nos proporciona el profesor para pintar los colores
			cout << "  ";
			colorCTA(15, 0); // Vuelve al color original(negro)
		}
		cout << endl;
	}
	cout << endl;
	//Pintamos la matriz solucion
	cout << "Matriz solucion" << endl;
	cout << " ";
	for (int i = 0; i < jpm.matrizsolucion.ncolumnas; i++)
	{
		cout << i %10 << " "; // Lo utilizamos para que aparezcan los numeros encima de las columnas(desde el 0 hasta el 9)
	}
	cout << endl;
	for (int fila = 0; fila < jpm.matrizsolucion.nfilas; fila++)
	{
		cout << fila % 10; // Lo utilizamos para que aparezcan los numeros a la izquierda de las filas(desde el 0 hasta el 9)
		for (int columna = 0; columna < jpm.matrizsolucion.ncolumnas; columna++)
		{
			colorCTA(15, jpm.matrizsolucion.matriz[fila][columna].color); //Utilizamos la función colorCTA que nos proporciona el profesor para pintar los colores
			cout << "  ";
			colorCTA(15, 0);//Vuelve al color base(negro)
		}
		cout << endl;
	}
	cout << "Numero de intentos restantes" << endl;
	cout << jpm.accionesrestantes << endl; //Nos muestra los intentos restantes
	

}
bool jugar(tJuegoPM& jpm) {
	int opcion = menu(); //llamamos a la funcion menu
	jpm.modo = opcion;  //Cargamos el modo elegido en la funcion menu
	bool salida = true;//Creamos una variable bool que utilizaremos para salir del programa
	if ((opcion==1) ||(opcion==2)) //Si el modo elegido es 1D o 2D
	{
		iniciar(jpm, opcion);//llamamos a la funcion iniciar
		if (salida == true)
		{
			borrar(); //Borramos la pantalla
			while (jpm.accionesrestantes!=0) //Bucle que funciona mientras las acciones restantes son distintas de 0
			{
				cout << "Te quedan " << jpm.accionesrestantes << "intentos" << endl; //mostramos el  numero de intentos
				mostrar(jpm); //mostramos las matrices
				salida = accion(jpm);
				if (jpm.matriz1==jpm.matrizsolucion)
				{
					jpm.accionesrestantes = 0;
				}
				else 
				{
					jpm.accionesrestantes--;
				}
				borrar(); //Borramos la pantalla
				
			}
		}
		if (jpm.accionesrestantes == 0)
		{
			cout << "No tienes mas acciones" << endl; //En caso de no tener mas acciones
			salida = false;
		}
	}
	
	mostrar(jpm); //Mostramos la matriz reto y la matriz solucion
	return salida;
}
bool accion(tJuegoPM& jpm){
	bool salida = true;

	if (jpm.modo==1) //Si el modo es 1D
	{
		int tipoaccion; //Pedimos al usuario que decida una accion
		modo1D(); //LLamamos a la funcion modo para que nos muestre las opciones disponibles
		cin >> tipoaccion;
		if (tipoaccion==1)
		{
			int f1, f2;
			cout << "Elige 2 filas" << endl;//Pedimos lo necesario para nuestra funcion
			cin >> f1;
			cin >> f2;
			swapF(jpm.matriz1, f1, f2); //Llamamos a la funcion SwapF

		}
		if (tipoaccion == 2)
		{
			int c1, c2;
			cout << "Elige 2 columnas" << endl; //Pedimos lo necesario para nuestra funcion
			cin >> c1;
			cin >> c2;

			swapC(jpm.matriz1, c1, c2); //Llamamos a la funcion SwapC
		}
		if (tipoaccion == 3)
		{
			int d;
			cout << "Elige 1 diagonal" << endl;//Pedimos lo necesario para nuestra funcion
			cin >> d;
			swapD(jpm.matriz1, d); //Llamamos a la funcion SwapD
		}
		if (tipoaccion == 4)
		{
			int f;
			cout << "Elige 1 filas" << endl; //Pedimos lo necesario para nuestra funcion
			cin >> f;
			voltearF(jpm.matriz1, f); //Llamamos a la funcion VoltearF
		}
		if (tipoaccion == 5)
		{
			int c;
			cout << "Elige 1 columna" << endl; //Pedimos lo necesario para nuestra funcion
			cin >> c;
			voltearC(jpm.matriz1, c); //Llamamos a la funcion VoltearC
		}
		if (tipoaccion == 6)
		{
			int d;
			cout << "Elige 1 diagonal" << endl; //Pedimos lo necesario para nuestra funcion
			cin >> d;
			voltearD(jpm.matriz1, d); //Llamamos a la funcion VoltearD
		}
	}
	if (jpm.modo==2) //Si el modo es 2D
	{
		int tipoaccion;
		modo2D();//LLamamos a la funcion modo para que nos muestre las opciones disponibles
		cin >> tipoaccion;
		if (tipoaccion == 1)
		{
			voltearV(jpm.matriz1);//Llamamos a la funcion VoltearV
		}
		if (tipoaccion==2)
		{
			voltearH(jpm.matriz1); //Llamamos a la funcion VoltearH
		}
		if (tipoaccion == 3)
		{
			rotarD(jpm.matriz1); //Llamamos a la funcion rotarD
		}
		if (tipoaccion == 4)
		{
			tCoor pos1;
			tCoor pos2;
			cout << "Cual es tu fila(1coordenada)" << endl; //Pedimos lo necesario para nuestra funcion
			cin >> pos1.posfila;
			cout << "Cual es tu columna(1coordenada)" << endl;
			cin >> pos1.poscolumna;
			cout << "Cual es tu fila(2coordenada)" << endl;
			cin >> pos2.posfila;
			cout << "Cual es tu columna(2coordenada)" << endl;
			cin >> pos2.poscolumna;
			swapAdy(jpm.matriz1, pos1, pos2); //Llamamos a la funcion swapAdy
		}
		if (tipoaccion == 5)
		{
			VoltearID(jpm.matriz1); //Llamamos a la funcion VoltearID
		}
	}
	return salida;
}
void modo1D()
{
	//Mostramos las acciones disponibles del modo 1D
	cout << "Que acción quieres realizar?" << endl;
	cout << "[*]" << " 1-SF(Intercambia las filas f1 y f2 de la matriz)" << endl;
	cout << "[*]" << " 2-SC(Intercambia las columnas c1 y c2)" << endl;
	cout << "[*]" << " 3-SD(Intercambia las diagonales)" << endl;
	cout << "[*]" << " 4-VF(Dar la vuelta a la fila f con respecto al eje vertical central de la imagen)" << endl;
	cout << "[*]" << " 5-VC(Dar la vuelta a la columna c con respecto al eje horizontal central de la imagen)" << endl;
	cout << "[*]" << " 6-VD(Dar la vuelta a la diagonal d con respecto al centro de eje perpendicular de dicha diagonal)" << endl;
}
void modo2D()
{
	//Mostramos las acciones disponibles del modo 2D
	cout << "Que acción quieres realizar?" << endl;
	cout << "[*]" << " 1-VV(Dar la vuelta a la imagen completa con respecto a su eje vertical central)" << endl;
	cout << "[*]" << " 2-VH(Dar la vuelta a la imagen completa con respecto a su eje horizontal central)" << endl;
	cout << "[*]" << " 3-RD(Rotar una imagen 90 grados en el sentido de las agujas del reloj)" << endl;
	cout << "[*]" << " 4-SA(Intercambiar las celdas vecinas o adyacentes de las posiciones pos1 y pos2)" << endl;
	cout << "[*]" << " 5-VD(Voltear la imagen completa respecto a la diagonal principal)" << endl;
}



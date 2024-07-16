/*Parchis V1 Realizado por Carlos Moreno Perez y Miguel Mateos Matias*/
/*El código utiliza un dado manual,aunque viene también incluido un dado aleatorio en forma de comentario,ambos funcionan correctamente ,pero usamos el manual para la corrección*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime>

/*Librerias*/
using namespace std;

typedef enum { amarillo = 1, azul, rojo, verde } tColor; // Creamos tipo enumerado TColor
tColor Jugador(int numero_jugador); //Asigna el color a cada jugador
string colorACadena(tColor color); // Muestra el color elegido por el jugador
char colorALetra(tColor color); //Genera la ficha del jugador correspondiendo con su color previamente elegido
int CasillaInicio(tColor color); //Asigna la casilla de inicio del jugador en funcion del color elegido
int dado(); //Dado que determina el movimiento de las fichas
bool esSeguro(int pos); //Determina las casillas en las que no se pueden comer las fichas (seguros)
void mostrar(int jugador1, int jugador2, int casilla1, int casilla2); //Genera el tablero
int zanataJugador(tColor color); //Determina la zanata de cada jugador
int extra_zanata(int casilla, tColor color, int movimiento_fichas); //Sistema que impide que un jugador se pase de la zanata, de esta forma tiene que llegar a la zanata con el numero exacto
bool ganador(int casilla, int jugador); //Determina cuando hay un ganador, es decir, que un jugador a llegado a su zanata; mientras que no haya un jugador el juego continua
int extra_tablero(int casilla); //Mecanismo por el que el jugador pasa de la casilla 67 a la 0



int main() {
	tColor color1, color2;
	string cadena1, cadena2;
	int casilla1, casilla2;

	color1 = Jugador(1);
	color2 = Jugador(2);
	cadena1 = colorACadena(color1);
	cadena2 = colorACadena(color2);
	casilla1 = -1;
	casilla2 = -1;

	cout << "Jugador 1 elige :::::> " << cadena1 << endl;
	cout << "Jugador 2 elige :::::> " << cadena2 << endl;
	/*Pedimos a los jugadores,que elijan color y establecemos todo lo corespondiente a los colores*/
	/* Creamos las variables que vamos a utilizar*/
	int movimiento_fichas = 0;
	
	while (ganador(casilla1, color1) == false && ganador(casilla2, color2) == false) { /*Creamos bucle hasta que gane un jugador*/
		system("cls");/*Lo utilizamos para "limpiar" nuestro programa*/

		cout << "Turno del jugador  " << colorACadena(color1) << endl; /* Comienza el turno del primer jugador*/
		movimiento_fichas = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
		if (casilla1 == -1) { /*Si la ficha está en casa*/
			if (movimiento_fichas == 5) { /*Si obtenemos un 5,nuestra ficha sale de casa*/
				casilla1 = CasillaInicio(color1);
			}
			else if (movimiento_fichas == 6) { /*Si en el dado obtenemos un 6*/
				cout << "Vuelves a tirar (2vez)" << endl;
				system("pause");
				int tirada4 = 0;
				tirada4 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
				if (tirada4 == 5) {  /*Si obtenemos un 5,nuestra ficha sale de casa*/
					casilla1 = CasillaInicio(color1);
				}
				else if (tirada4 == 6) { /*Si obtenemos un segundo 6*/
					cout << "Vuelves a tirar (3vez)" << endl;
					system("pause");
					int tirada5 = 0; 
					tirada5 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
					if (tirada5 == 5) { /*Si obtenemos un 5,nuestra ficha sale de casa*/
						casilla1 = CasillaInicio(color1);
					}
					else if (tirada5 == 6) { /*Si obtenemos un tercer 6,se acaba el turno */
						cout << "Has sacado 3 veces 6, le toca a tu rival" << endl;
					}
					else {
						cout << "Lastima,sigues en casa" << endl;  /* Si no obtienes un 5 en la posición casa*/
					}
				}
				else {
					cout << "Lastima,sigues en casa" << endl;  /* Si no obtienes un 5 en la posición casa*/
				}
			}
			else {
				cout << "Lastima,sigues en casa" << endl;  /* Si no obtienes un 5 en la posición casa*/
			}
		}
		else { /*Si la ficha está en el carril*/
			casilla1 = casilla1 + movimiento_fichas; /* A la posición,le sumamos el valor del dado*/
			casilla1 = extra_tablero(casilla1); /*Aplicamos esta función,para cuando sobrepase la casilla 67*/
			casilla1 = extra_zanata(casilla1, color1, movimiento_fichas); /*Evita errores al comer cerca de la zanata*/
			mostrar(color1, color2, casilla1, casilla2); /*Se muestra el tablero*/
			if (movimiento_fichas == 6) /*Si en el dado obtenemos un 6*/
			{
				cout << "Vuelves a tirar(2vez)" << endl;
				system("pause");
				int tirada2 = 0;
				tirada2 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
				casilla1 = casilla1 + tirada2; /* A la posición,le sumamos el valor del dado*/
				casilla1 = extra_tablero(casilla1); /*Aplicamos esta función,para cuando sobrepase la casilla 67*/
				casilla1 = extra_zanata(casilla1, color1, movimiento_fichas);/*Evita errores al comer cerca de la zanata*/
				mostrar(color1, color2, casilla1, casilla2);/*Se muestra el tablero*/
				if (tirada2 == 6) /*Si en el dado obtenemos un segundo 6*/
				{
					cout << "Vuelves a tirar(3vez)" << endl;
					system("pause"); /*Esto lo usamos de forma estética*/
					int tirada3 = 0;
					tirada3 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
					if (tirada3 == 6) /*Si en el dado obtenemos un tercer 6 seguido*/
					{
						cout << "Has sacado tres seises seguidos,lo siento!" << endl;
						casilla1 = CasillaInicio(color1); /* La ficha vuelve a la casilla inicial*/
						casilla1 = -1; /*Mete la ficha en casa*/
					}
					else {
						casilla1 = casilla1 + tirada3;  /* A la posición,le sumamos el valor del dado*/
						casilla1 = extra_tablero(casilla1);/*Aplicamos esta función,para cuando sobrepase la casilla 67*/
						casilla1 = extra_zanata(casilla1, color1, movimiento_fichas);/*Evita errores al comer cerca de la zanata*/
						mostrar(color1, color2, casilla1, casilla2);/*Se muestra el tablero*/
					}
				}
			}
		}
		if ((casilla1 == casilla2) && (esSeguro(casilla1)==false)) { /*Cuando comes al jugador 2*/

			
			casilla2 = CasillaInicio(color2); /* El jugador 2 vuelve a la casilla inicial*/
			casilla2 = -1; /* Mete la ficha en casa */
			if (casilla1 != -1 && casilla1 < zanataJugador(color1) && casilla1 + 20 > zanataJugador(color1) || (casilla1 > 48) &&  (color1 == 1 ))/*Cuando comes cerca de la zanata*/
			{
				cout << "No puedes avanzar porque te excedes de la zanata" << endl;
			}
			else
			{
				casilla1 = casilla1 + 20; /* Se suman 20 posiciones a la ficha*/
			}
		}

		cout << "Turno del jugador " << colorACadena(color2) << endl; /*Turno del jugador 2*/
		movimiento_fichas = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
		if (casilla2 == -1) { /*Si la ficha está en casa*/
			if (movimiento_fichas == 5) { /*Si obtenemos un 5,salimos de casa*/
				casilla2 = CasillaInicio(color2);
			}
			else if (movimiento_fichas == 6) { /*Si obtenemos un 6*/
				cout << "Vuelves a tirar (2vez)" << endl;
				system("pause");
				int tirada6 = 0; 
				tirada6 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
				if (tirada6 == 5) { /*Si obtenemos un 5,salimos de casa*/
					casilla2 = CasillaInicio(color2);
				}
				else if (tirada6 == 6) { /*Si obtenemos un segundo 6*/
					cout << "Vuelves a tirar (3vez)" << endl;
					system("pause");
					int tirada7 = 0;
					tirada7 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
					if (tirada7 == 5) { /*Si obtenemos un 5,salimos de casa*/
						casilla2 = CasillaInicio(color2);
					}
					else if (tirada7 == 6) { /*Si obtenemos un tercer 6 seguido,perdemos el turno*/
						cout << "Has sacado 3 veces 6, le toca a tu rival" << endl;
					}
					else {
						cout << "Lastima,sigues en casa" << endl;
					}
				}
				else {
					cout << "Lastima,sigues en casa" << endl;
				}
			}
			else {
				cout << "Lastima,sigues en casa" << endl;
			}
		}
		else { /*Si la ficha esta en el carril*/
			casilla2 = casilla2 + movimiento_fichas;/* A la posición,le sumamos el valor del dado*/
			casilla2 = extra_tablero(casilla2);/*Aplicamos esta función,para cuando sobrepase la casilla 67*/
			casilla2 = extra_zanata(casilla2, color2, movimiento_fichas);/*Evita errores al comer cerca de la zanata*/
			mostrar(color1, color2, casilla1, casilla2);/*Mostramos el tablero*/
			if (movimiento_fichas == 6) /*Si obtenemos un 6*/
			{
				cout << "Vuelves a tirar(2vez)" << endl;
				system("pause");
				int tirada8 = 0;
				tirada8 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
				casilla2 = casilla2 + tirada8;/* A la posición,le sumamos el valor del dado*/
				casilla2 = extra_tablero(casilla2);/*Aplicamos esta función,para cuando sobrepase la casilla 67*/
				casilla2 = extra_zanata(casilla2, color2, movimiento_fichas);/*Evita errores al comer cerca de la zanata*/
				mostrar(color1, color2, casilla1, casilla2);/*Mostramos el tablero*/
				if (tirada8 == 6) /* Si obtenemos un segundo 6*/
				{
					cout << "Vuelves a tirar(3vez)" << endl;
					system("pause");
					int tirada9 = 0;
					tirada9 = dado(); /*El movimiento de las fichas viene determinado por la función dado*/
					if (tirada9 == 6) /*Si obtenemos un gtercer 6 seguido*/
					{
						cout << "Has sacado tres seises seguidos,lo siento!" << endl;
						casilla2 = CasillaInicio(color1); /*Nuestra ficha vuelve a la posición inicial*/
						casilla2 = -1;/*Mete la ficha en casa*/
					}
					else {
						casilla2 = casilla2 + tirada9; /* A la posición,le sumamos el valor del dado*/
						casilla2 = extra_tablero(casilla2);/*Aplicamos esta función,para cuando sobrepase la casilla 67*/
						casilla2 = extra_zanata(casilla2, color2, movimiento_fichas);/*Evita errores al comer cerca de la zanata*/
						mostrar(color1, color2, casilla1, casilla2);/*Mostramos el tablero*/
					}
				}
			}
		}
		if ((casilla2 == casilla1) && (esSeguro(casilla2) == false)) { /*Cuando comemos al jugador 1*/


			casilla1 = CasillaInicio(color2); /*El jugador 1 vuelve a la posición inicial*/
			casilla1 = -1;/*Mete la ficha en casa*/
			if (casilla2 != -1 && casilla2 < zanataJugador(color2) && casilla2 + 20 > zanataJugador(color2) || (casilla2 > 48) && (color2 == 1)) /*Cuando come cerca de la zanata*/
			{
				cout << "No puedes avanzar porque te excedes de la zanata" << endl;
			}
			else
			{
				casilla2 = casilla2 + 20;/*Se suma 20 posiciones a la ficha 2*/
			}
		}
		mostrar(color1, color2, casilla1, casilla2); /*Se muestra el tablero*/
	}
	if (ganador(casilla1, color1) == true) /*Cuando uno de los dos jugadores ganan el juego*/
	{
		cout << "Enhorabuena " << colorACadena(color1) << ",has alcanzado la victoria!" << endl; /*Cuando gana el jugador 1*/
	}
	else if (ganador(casilla2, color2) == true) {
		cout << "Enhorabuena " << colorACadena(color2) << ",has alcanzado la victoria!" << endl; /*Cuando gana el jugador 1*/
	}
	return 0;
}

tColor Jugador(int numero_jugador) //Funcion que asigna jugador
{
	int elegir = 0;
	tColor  seleccion;
	while (elegir == 0) /*Creamos un menu, y en función de lo que elijas ,te asigna un color*/
	{
		do
		{
			cout << "\nJugador " << numero_jugador << ", elige tu color:\n[1] Amarillo\n[2] Azul\n[3] Rojo\n[4] Verde\n";
			cin >> elegir;
		} while ((elegir < 1) || (elegir > 4));

		if (elegir == 1)
		{
			seleccion = amarillo;
		}
		else if (elegir == 2)
		{
			seleccion = azul;
		}
		else if (elegir == 3)
		{
			seleccion = rojo;
		}
		else if (elegir == 4)
		{
			seleccion = verde;
		}
		else
		{
			cout << "valor no valido" << endl;
		}
		return seleccion;
	}
}
string colorACadena(tColor color) // Muestra el color elegido por el jugador
{
	string eleccion_color; 
	if (color == rojo)
		eleccion_color = "Rojo";
	else if (color == amarillo)
		eleccion_color = "Amarillo";
	else if (color == azul)
		eleccion_color = "Azul";
	else if (color == verde)
		eleccion_color = "Verde";
	return eleccion_color;
}
char colorALetra(tColor color) //Genera la ficha del jugador correspondiendo con su color previamente elegido
{
	char seleccion_ficha; /*Esto se verá en el tablero*/
	if (color == rojo)
		seleccion_ficha = 'R';
	else if (color == amarillo)
		seleccion_ficha = 'M';
	else if (color == azul)
		seleccion_ficha = 'A';
	else if (color == verde)
		seleccion_ficha = 'V';
	return seleccion_ficha;
}
int CasillaInicio(tColor color) //Asigna la casilla de inicio del jugador en funcion del color elegido
{
	int seleccion_casilla_inicio; 
	if (color == rojo)
	{
		seleccion_casilla_inicio = 39;
	}
	else if (color == amarillo)
	{
		seleccion_casilla_inicio = 5;
	}
	else if (color == azul)
	{
		seleccion_casilla_inicio = 22;
	}
	else if (color == verde)
	{
		seleccion_casilla_inicio = 56;
	}
	return seleccion_casilla_inicio;
}
int dado() //Dado que determina el movimiento de las fichas
{
	/*srand(time(NULL));
	int tirada = 1 + (rand() % 6);*/
	/*DADO ALEATORIO*/
	int tirada;/*DADO MANUAL*/
	cout << "Introduzca el numero del dado" << endl;
	cin >> tirada;
	cout << "Has sacado un :" << tirada << endl;
	return tirada;
}
bool esSeguro(int pos) //Determina las casillas en las que no se pueden comer las fichas (seguros)
{
	bool seguro;
	if (pos == 0 || pos == 5 || pos == 12 || pos == 17 || pos == 22 || pos == 29 || pos == 34 || pos == 39 || pos == 46 || pos == 51 || pos == 56 || pos == 63) {
		seguro = true;
	}

	else {
		seguro = false;
	}
	return seguro;
}
void mostrar(int jugador1, int jugador2, int casilla1, int casilla2)  //Genera el tablero
{
	int NUM_CASILLAS = 68;
	char c;
	//Muestra posiciones del tablero
	cout << endl << "      ";
	for (int pos = 0; pos < NUM_CASILLAS; pos++)
		cout << pos / 10;
	cout << endl << "      ";
	for (int pos = 0; pos < NUM_CASILLAS; pos++)
		cout << pos % 10;
	//Muestra posiciones seguras del tablero
	cout << endl << "      ";
	for (int pos = 0; pos <= 67; pos++)
		if (esSeguro(pos))
			cout << "o";
		else
			cout << "-";
	//Muestra las fichas en su posición correspondiente en el tablero
	cout << endl << "CALLE ";
	for (int pos = 0; pos < NUM_CASILLAS; pos++)
		if (pos == casilla1)
			cout << colorALetra(tColor(jugador1));
		else if (pos == casilla2)
			cout << colorALetra(tColor(jugador2));
		else
			cout << " ";
	//Muestra las posiciones seguras del tablero
	cout << endl << "      ";
	for (int pos = 0; pos <= 67; pos++)
		if (esSeguro(pos))
			cout << "o";
		else
			cout << "-";
	//Muestra las fichas que estan en casa
	cout << endl << "CASA  ";
	for (int pos = 0; pos < NUM_CASILLAS; pos++) {
		char c = ' ';
		if (pos == CasillaInicio(tColor(jugador1))) {
			if (casilla1 == -1)
				c = colorALetra(tColor(jugador1));
		}
		else if (pos == CasillaInicio(tColor(jugador2)))
			if (casilla2 == -1)
				c = colorALetra(tColor(jugador2));
		cout << c;
	}
	cout << endl;

	system("pause");
}
int zanataJugador(tColor color) {  //Determina la zanata de cada jugador
	int seleccion_zanataJugador;
	if (color == 1) {
		seleccion_zanataJugador = 0;
	}
	else if (color == 2) {
		seleccion_zanataJugador = 17;
	}
	else if (color == 3) {
		seleccion_zanataJugador = 34;
	}
	else if (color == 4) {
		seleccion_zanataJugador = 51;
	}
	return seleccion_zanataJugador;
}
int extra_zanata(int casilla, tColor color, int movimiento_fichas) { //Sistema que impide que un jugador se pase de la zanata, de esta forma tiene que llegar a la zanata con el numero exacto

	if ((zanataJugador(color)) < casilla && casilla <= CasillaInicio(color)) {
		cout << "Te has pasado, vuelves a tu posicion " << endl;
		casilla = casilla - movimiento_fichas;
	}
	return casilla;
}
bool ganador(int casilla, int jugador) { //Determina cuando hay un ganador, es decir, que un jugador a llegado a su zanata; mientras que no haya un jugador el juego continua
	bool verdadero_zanatajugador;
	if (casilla == zanataJugador(tColor(jugador))) {
		verdadero_zanatajugador = true;
	}
	else {
		verdadero_zanatajugador = false;
	}
	return verdadero_zanatajugador;
}
int extra_tablero(int casilla) {  //Mecanismo por el que el jugador pasa de la casilla 67 a la 0
	if (casilla > 67) {
		casilla = casilla - 67;
	}
	return casilla;
}


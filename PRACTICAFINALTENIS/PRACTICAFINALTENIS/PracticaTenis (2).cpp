//Trabajo realizado por Miguel Mateos y David Vega
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <stdlib.h>//Librerias

using namespace std;

const int LIM_INF_HAB = 1;//Declaramos las constantes
const int LIM_SUP_HAB = 2;
const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 3;
const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const bool MODO_DEBUG = false;//Explica mejor los detalles
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2; //Arrays de Golpes
const int JUEGOS_SET = 3;//Juegos necesarios para ganar

//Definicion de enumerados 
typedef enum tTenista { NADIE, TENISTA1, TENISTA2 };
typedef enum tPuntosJuego { NADA, QUINCE, TREINTA, CUARENTA, VENTAJA, VICTORIA };
typedef int tConteoGolpes[DIM_ARRAY_GOLPES];

typedef struct {
	int posicion;
	tPuntosJuego puntos;
	int juegos;
	int golpes_ganadores;
	tConteoGolpes golpes;
}tDatosPartido;

typedef struct {
	string iniciales;
	int habilidad;
	int velocidad;
	int partidos_ganados;
	int partidos_perdidos;
	tDatosPartido datos;
}tDatosTenista;

typedef tDatosTenista arraydatostenista[10];

typedef struct {
	arraydatostenista array;
	int contador;
}tListaTenistas;

string pedir_nombre();//Pide las siglas del jugador
int pedir_velocidad();//Pide la velocidad del jugador
int pedir_habilidad();//Pide la habilidad del jugador
int quien_comienza();//Elige quien empieza sacando
string puntoAstring(tPuntosJuego puntuacion);//Convierte en string la puntuacion
int correTenista(int posicion_tenista_recibe, int velocidad, int posicion_bola, bool& llega);//Se encarga de ver si el tenista llega a la posicion de la  bola
void aleatorio(bool& aleatorio);//Elige si el modo de juego es aleatorio o no
int golpeoBola(int posicion_tenista, int habilidad, tConteoGolpes& golpes, bool juego_aleatorio);//Funcion encargada de realizar el golpeo de la bola
void turnox(tTenista& tenista_golpea);//Cambia el turno
int victoria(tPuntosJuego& puntuacion1, tPuntosJuego& puntuacion2);
void regularpunto(tPuntosJuego& puntuacion1, tPuntosJuego& puntuacion2);//Funcion que aparece cuando los marcadores estan en ventaja empatados
tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2);//Devuelve el ganador, y actualiza los puntos en el marcador.
void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para);// Muestra el resulktado(juegos, puntos) y quien saca.
tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& pos_bola, bool juego_aleatorio);//Realiza una jugada devuelve el ganador.
tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para, bool juego);// Devuelve el ganador del punto con la iformación que le devuelve lance.
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola);// Llama a diferentes funciones para pintar el campo, la bola y los jugadores.
tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para, bool juego);// Te marca quien ha ganado el juego.
tTenista hayGanadorSet(tDatosTenista& tenista1, tDatosTenista& tenista2, tListaTenistas& listaT);//Te indica quien gana el set.
void inicializargolpes(tDatosPartido& datospartido1, tDatosPartido& datospartido2);// Registra los golpes, y los golpes ganados.
//Funciones para el "pintarPeloteo"
void mostrarNombre(int pos, string nombre);
void mostrarCampo1(int pos_bola, tTenista bola_jugador);
void mostrarBorde();
void mostrarCampo2(int pos_bola, tTenista bola_jugador);
void sumarpunto(tPuntosJuego& punt);
void mostrarEstadisticas(string nombre, int golpesganados, tConteoGolpes golpes);//Muestra las estadisticas de los jugadores, al finalizar cada punto.
void mostrarNumeros();

//nuevo
bool cargar(tListaTenistas& listaT);//La función recibe un archivo de texto y lo carga en la lista de tenistas 
void mostrar(const tListaTenistas& listaT);//Recibe la lista de la funcion cargar, y la muestra en pantalla
void mostrarIniciales(const tListaTenistas& listaT);//Recibe la lista y muestra las iniciales de los tenistas
int buscarIniciales(const tListaTenistas& listaT, string ini);//Recibe una lista de tenista y unas iniciales y devuelve la posicion
void eliminarTenista(tListaTenistas& listaT, string iniciales);//Busca en la lista las iniciales, y si las encuentra la elimina
void introducirTenista(tListaTenistas& listaT);//Se añade un tenista a la lista, si hay hueco
void guardar(tListaTenistas& listaT);//Recibe una lista de tenistas, y las guarda en el archivo de texto
void mostrarOpciones();//El menu para ver que accion se desea ejucutar la funcion correspondiente
tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2, tListaTenistas& listaT);//Se jugara el partido con dos tenistas, y devolvera el ganador, además se actualizaran los partidos ganados y perdidos para cada uno.
tDatosTenista seleccionartenista(string iniciales, tListaTenistas& listaT);//Coge al tenista de la posicion especificada
void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4);//Recibe los 4 jugadores de la lista de tenistas, y realiza un partido con cada pareja, y luego una final
int postenista(tListaTenistas& listaT, string iniciales);//Coge la posicion del tenista en la lista
void ordenarlista(tListaTenistas& listaT);//Ordena la lista de tenistas por partidos ganados


int main() {
	srand(time(NULL));
	//definicion de las variables que vamos a necesitar
	tListaTenistas listaT;
	cargar(listaT);
	string inicialeseliminar;
	int opcion;
	cout << "Bienvenido al simulador de partidos de tenis v3" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	mostrarOpciones();
	cout << endl;
	cout << "Introduce una opcion" << endl;
	cin >> opcion;
	while (opcion != 0) {
		if (opcion == 1) {
			mostrar(listaT);
		}
		else if (opcion == 2) {
			introducirTenista(listaT);

		}
		else if (opcion == 3) {
			mostrarIniciales(listaT);
			cout << "Introduce el tenista que desea eliminar" << endl;
			cin >> inicialeseliminar;
			eliminarTenista(listaT, inicialeseliminar);
		}
		else if (opcion == 4) {
			string iniciales1;
			string iniciales2;
			mostrarIniciales(listaT);
			cout << "Elige el primer tenista" << endl;
			cin >> iniciales1;
			tDatosTenista tenista1 = seleccionartenista(iniciales1, listaT);
			mostrarIniciales(listaT);
			cout << "Elige el segundo tenista" << endl;
			cin >> iniciales2;
			while (iniciales2 == iniciales1) {
				cout << "Has seleccionado al mismo tenista,seleccione otro " << endl;
				mostrarIniciales(listaT);
				cin >> iniciales2;
			}
			tDatosTenista tenista2 = seleccionartenista(iniciales2, listaT);
			jugarPartido(tenista1, tenista2, listaT);

		}
		else if (opcion == 5) {
			int indT1, indT2, indT3, indT4;
			string iniciales1, iniciales2, iniciales3, iniciales4;
			mostrarIniciales(listaT);
			cout << "Elige el primer participante" << endl;
			cin >> iniciales1;
			indT1 = postenista(listaT, iniciales1);
			mostrarIniciales(listaT);
			cout << "Elige el segundo participante" << endl;
			cin >> iniciales2;
			while (iniciales2 == iniciales1) {
				cout << "Has seleccionado a un tenista seleccionado anteriormente ,seleccione otro " << endl;
				mostrarIniciales(listaT);
				cin >> iniciales2;
			}
			indT2 = postenista(listaT, iniciales2);
			mostrarIniciales(listaT);
			cout << "Elige el tercer participante" << endl;
			cin >> iniciales3;
			while (iniciales3 == iniciales2 || iniciales3 == iniciales1) {
				cout << "Has seleccionado a un tenista seleccionado anteriormente ,seleccione otro " << endl;
				mostrarIniciales(listaT);
				cin >> iniciales3;
			}
			indT3 = postenista(listaT, iniciales3);
			mostrarIniciales(listaT);
			cout << "Elige el cuarto participante" << endl;
			cin >> iniciales4;
			while (iniciales4 == iniciales3 || iniciales4 == iniciales2 || iniciales4 == iniciales1) {
				cout << "Has seleccionado a un tenista seleccionado anteriormente ,seleccione otro " << endl;
				mostrarIniciales(listaT);
				cin >> iniciales4;
			}
			indT4 = postenista(listaT, iniciales4);
			jugarTorneo(listaT, indT1, indT2, indT3, indT4);
		}
		else if (opcion == 6) {

			ordenarlista(listaT);
			jugarTorneo(listaT, 0, 3, 1, 2);
		}
		else {
			cout << "Opcion no valida,seleccione otra posible" << endl;
		}
		cout << endl;
		system("pause");
		mostrarOpciones();
		cout << endl;
		cout << "Introduce una opcion" << endl;
		cin >> opcion;
	}
	return 0;
}
void aleatorio(bool& aleatorio) {
	int alt;
	cout << "Elige si desea el modo aleatorio o no" << endl;
	cout << "1-Aleatorio" << endl;
	cout << "0-Manual" << endl;
	cin >> alt;
	while ((alt < 0) || (alt > 1)) {//Si elige opcion no incluida
		cout << "Valor introducido no valido" << endl;
		cin >> alt;
	}
	if (alt == 1) { //Modo aleatorio
		cout << "Se ha elegido el modo aleatorio" << endl;
		aleatorio = true;
	}
	else if (alt == 0) {//Modo manual
		cout << "Se ha elegido el modo manual" << endl;
		aleatorio = false;
	}

}
string pedir_nombre() {
	string nombre;
	cout << "-Introduce sus iniciales " << endl;
	cin >> nombre;
	while ((nombre.length() > 3) || (nombre.length() != 3))//EN caso de que no sean 3 siglas
	{
		cout << "Solo se admiten 3 siglas" << endl;
		cin >> nombre;
	}

	return nombre;
}
int pedir_velocidad() {
	int velocidad;
	cout << "-Introduce la velocidad del Jugador (valor entre 1 y 3) " << endl;
	cin >> velocidad;
	while ((velocidad < LIM_INF_VEL) || (velocidad > LIM_SUP_VEL)) {//En caso de que no este en las opciones
		cout << "Velocidad no incluida entre los parametros,vuelve a intentarlo!" << endl;
		cin >> velocidad;
	}
	return velocidad;
}
int pedir_habilidad() {
	int habilidad;
	cout << "-Introduce la habilidad del Jugador (valor entre 1 y 2) " << endl;
	cin >> habilidad;
	while ((habilidad < LIM_INF_HAB) || (habilidad > LIM_SUP_HAB)) {//En caso de que no este en las opciones
		cout << "Habilidad no incluida entre los parametros,vuelve a intentarlo!" << endl;
		cin >> habilidad;
	}
	return habilidad;
}
int quien_comienza() {
	int numero;
	numero = rand();
	numero = numero % 2;//Numero aleatorio cuyo modulo sea 0 o 1
	return numero;
}
string puntoAstring(tPuntosJuego puntuacion) { //Pasa de tipo PuntosJuego a string
	string marcador;
	switch (puntuacion)
	{
	case 0: marcador = "00";;
		break;
	case 1:marcador = "15";;
		break;
	case 2:marcador = "30";;
		break;
	case 3:marcador = "40";;
		break;
	case 4:marcador = "Ad";;
		break;

	}
	return marcador;
}
int correTenista(int posicion_tenista_recibe, int velocidad, int posicion_bola, bool& llega) {
	int posfinal;
	int distancia;
	//Calculamos distancia entre tenista y bola
	if (posicion_bola > posicion_tenista_recibe) {
		distancia = posicion_bola - posicion_tenista_recibe;
	}
	else {
		distancia = posicion_tenista_recibe - posicion_bola;
	}

	if (distancia <= velocidad) {//Si distancia <=velocidad
		posfinal = posicion_bola;//Posiciontenista=Posbola
		llega = true;//lega a la bola
		if (MODO_DEBUG == true) {
			cout << "Su rival  llega a la bola" << endl;
		}

	}
	else {//si distancia no es <=velocidad
		if (posicion_bola > posicion_tenista_recibe) {
			posfinal = posicion_tenista_recibe + velocidad;//Una posición o otra
		}
		else
		{
			posfinal = posicion_tenista_recibe - velocidad;
		}
		llega = false;//No llega
		if (MODO_DEBUG == true) {
			cout << "Su rival no llega a la bola" << endl;
		}
	}
	return posfinal;
}
int golpeoBola(int posicion_tenista, int habilidad, tConteoGolpes& golpes, bool juego_aleatorio) {
	int destinodeseado;
	double distancia;
	int numaleatorio = 0;
	int num2 = 0;
	int destinofinal;
	int probabilidad;
	float prob1;
	if (juego_aleatorio == true) {//Numero entre 1 y 7 forma aleatoria
		destinodeseado = 1 + rand() % (ANCHO_PISTA);
	}
	else {//Forma manual
		cout << "Introduce la calle deseada(1 y 7)" << endl;
		cin >> destinodeseado;
		while ((destinodeseado < 1) || (destinodeseado > 7)) {
			cout << "Calle no incluida entre los parametros,vuelve a intentarlo!" << endl;
			cin >> destinodeseado;
		}

	}
	if (MODO_DEBUG == true)//Indica donde quiere disparar
	{
		cout << "El jugador dispara hacia la casilla " << destinodeseado << endl;
	}
	distancia = abs(destinodeseado - posicion_tenista);//calcula distancia entre la calle y el tenista
	if (distancia <= habilidad) {
		if (MODO_DEBUG == true)
		{
			cout << "Ese ha sido un tiro sencillo " << endl;
		}
		destinofinal = destinodeseado;//Dispara a donde quiere
	}
	else {//El disparo no va  al destino
		numaleatorio = rand() % 100;//Se calcula una probabilidad y un num aleatorio entre 0 y 99
		prob1 = (distancia - habilidad) / ((ANCHO_PISTA - 1) - LIM_INF_HAB);
		probabilidad = 100 - prob1 * 100;
		if (MODO_DEBUG == true)
		{
			cout << "Tiro complicado que .. (Probabilidad exito : " << probabilidad << " y resultado = " << numaleatorio << " )" << endl;
		}
		if (numaleatorio < probabilidad) {
			if (MODO_DEBUG == true)
			{
				cout << "LLega a su destino!" << endl;
			}
			destinofinal = destinodeseado;//LLega al destino a pesar de todo
		}
		else {//No llega y se decide a que destino va
			if (MODO_DEBUG == true)
			{
				cout << "No ha sido preciso!" << endl;
			}
			num2 = rand() % 2;
			if (num2 == 0) {
				destinofinal = destinodeseado + 1;
			}
			else {
				destinofinal = destinodeseado - 1;
			}
		}
	}
	switch (destinofinal) //Aumentar los golpes para las estadisticas
	{
	case 0: golpes[0] = golpes[0] + 1;
		break;
	case 1:golpes[1] = golpes[1] + 1;
		break;
	case 2:golpes[2] = golpes[2] + 1;
		break;
	case 3:golpes[3] = golpes[3] + 1;
		break;
	case 4:golpes[4] = golpes[4] + 1;
		break;
	case 5:golpes[5] = golpes[5] + 1;
		break;
	case 6:golpes[6] = golpes[6] + 1;
		break;
	case 7:golpes[7] = golpes[7] + 1;
		break;
	case 8:golpes[8] = golpes[8] + 1;
		break;

	}

	return destinofinal;
}
void turnox(tTenista& tenista_golpea) {
	if (tenista_golpea == TENISTA1) {//Cambia los turnos
		tenista_golpea = TENISTA2;
	}
	else if (tenista_golpea == TENISTA2) {
		tenista_golpea = TENISTA1;
	}
}
void regularpunto(tPuntosJuego& puntuacion1, tPuntosJuego& puntuacion2) {
	if ((puntuacion1 == VENTAJA) && (puntuacion2 == VENTAJA)) { //en caso de ir los dos empate con ventaja
		puntuacion1 = CUARENTA;
		puntuacion2 = CUARENTA;
	}
}
int victoria(tPuntosJuego& puntuacion1, tPuntosJuego& puntuacion2) {
	int final = 0;
	if ((puntuacion1 == VENTAJA) && (puntuacion2 < CUARENTA)) {//Mira todos los casos de victoria
		final = 1;
	}
	else if ((puntuacion2 == VENTAJA) && (puntuacion1 < CUARENTA)) {
		final = 2;
	}
	else if ((puntuacion1 == VICTORIA) && (puntuacion2 == CUARENTA)) {
		final = 1;
	}
	else if ((puntuacion2 == VICTORIA) && (puntuacion1 == CUARENTA)) {
		final = 2;
	}
	return final;
}
tTenista actualizarMarcador(tTenista ganador_punto, tDatosPartido& datos_t1, tDatosPartido& datos_t2) {
	tTenista Ganador;
	Ganador = NADIE;
	if (ganador_punto == TENISTA1) {// If para saber quien gana el punto
		sumarpunto(datos_t1.puntos);//Le suma el punto
		regularpunto(datos_t1.puntos, datos_t2.puntos);//Por si estan empatados en ventaja. 
		if (victoria(datos_t1.puntos, datos_t2.puntos) == TENISTA1) {//Y llama a la funcion victoria para sumar un juego en caso de ganar.
			Ganador = TENISTA1;
			datos_t1.juegos += 1;
		}
	}
	else if (ganador_punto == TENISTA2) {
		sumarpunto(datos_t2.puntos);
		regularpunto(datos_t1.puntos, datos_t2.puntos);
		if (victoria(datos_t1.puntos, datos_t2.puntos) == TENISTA2) {
			Ganador = TENISTA2;
			datos_t2.juegos += 1;
		}
	}
	return Ganador;
}
void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para) {//Pinta el marcador
	if (servicio_para == 1) {
		cout << iniciales1 << " " << datos_t1.juegos << " : " << puntoAstring(datos_t1.puntos) << " * " << endl;
		cout << iniciales2 << " " << datos_t2.juegos << " : " << puntoAstring(datos_t2.puntos) << endl;
	}
	else if (servicio_para == 2) {
		cout << iniciales1 << " " << datos_t1.juegos << " : " << puntoAstring(datos_t1.puntos) << endl;
		cout << iniciales2 << " " << datos_t2.juegos << " : " << puntoAstring(datos_t2.puntos) << " * " << endl;
	}
	else {
		cout << iniciales1 << " " << datos_t1.juegos << " : " << puntoAstring(datos_t1.puntos) << endl;
		cout << iniciales2 << " " << datos_t2.juegos << " : " << puntoAstring(datos_t2.puntos) << endl;
	}
}
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola) {

	cout << '\n';

	mostrarNombre(pos_t1, nombre1);// Muestra los nombres de los tenistas.

	mostrarBorde();//Muestra los bordes del campo

	mostrarCampo1(pos_bola, bola_jugador);//Muestra el primer campo, y donde se encuentra la bola en él.

	mostrarNumeros();//Muestra los numeros que marcan el ancho de pista.

	mostrarCampo2(pos_bola, bola_jugador);//Muestra el segundo campo, y donde se encuentra la bola en él.

	mostrarBorde();

	mostrarNombre(pos_t2, nombre2);

	cout << '\n';


}
void mostrarNombre(int pos, string nombre) {

	for (int i = 1; i < ANCHO_PISTA + 2; i++) {
		if (pos == i - 1)
			cout << nombre;
		else
			cout << "  ";
	}

	cout << '\n';

}
void mostrarBorde() {

	cout << "   ";
	for (int i = 1; i < ANCHO_PISTA + 2; i++)
		cout << "- ";
	cout << '\n';

}
void mostrarNumeros() {

	cout << " -";
	for (int i = 1; i < ANCHO_PISTA + 1; i++)
		cout << "-" << i;
	cout << "--" << '\n';

}
void mostrarCampo1(int pos_bola, tTenista bola_jugador) {

	cout << "  ";
	for (int i = 1; i < ANCHO_PISTA + 2; i++) {

		if (pos_bola == i && bola_jugador == TENISTA2)
			cout << "|o";
		else
			cout << "| ";

	}
	cout << '\n';

	int i = 0;
	while (i < 2) {

		cout << "  ";
		for (int i = 1; i < ANCHO_PISTA + 2; i++)
			cout << "| ";
		cout << '\n';
		i++;
	}


}
void mostrarCampo2(int pos_bola, tTenista bola_jugador) {

	int i = 0;
	while (i < 2) {

		cout << "  ";
		for (int i = 1; i < ANCHO_PISTA + 2; i++)
			cout << "| ";
		cout << '\n';
		i++;
	}

	cout << "  ";
	for (int i = 1; i < ANCHO_PISTA + 2; i++) {

		if (pos_bola == i && bola_jugador == TENISTA1)
			cout << "|o";
		else
			cout << "| ";

	}
	cout << '\n';

}
tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& pos_bola, bool juego_aleatorio) {
	tTenista ganador;
	bool llega = false; //Variable para saber cuando llega y hacer if.
	ganador = NADIE;
	cout << "Golpea " << tenista_golpea.iniciales << endl;
	pos_bola = golpeoBola(pos_bola, tenista_golpea.habilidad, tenista_golpea.datos.golpes, juego_aleatorio); //LLama la funcion que golpea la bola
	if ((pos_bola < 1) || (pos_bola > ANCHO_PISTA)) { //Manda fuera
		if (bola_para == TENISTA1) { //Si el que golpea es el tenista1
			cout << "El disparo ha ido fuera de la pista" << endl;
			ganador = TENISTA2;
		}
		else if (bola_para == TENISTA2) { //Si el que golpea es el tenista2
			cout << "El disparo ha ido fuera de la pista" << endl;
			ganador = TENISTA1;
		}
	}
	else {//Manda dentro

		tenista_recibe.datos.posicion = correTenista(tenista_recibe.datos.posicion, tenista_recibe.velocidad, pos_bola, llega); //funcion que llama a corrertenista
		if (llega == false) {
			ganador = bola_para;
			tenista_golpea.datos.golpes_ganadores++;
		}
		else {
			ganador = NADIE;
		}

	}
	return ganador;
}
tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para, bool juego) {
	int posbola = 4; //establecen la sposiciones de la bola y los tenistas
	tenista1.datos.posicion = 4;
	tenista2.datos.posicion = 4;
	tTenista Lance;
	Lance = NADIE;// Para saber quien a ganado la jugada.
	tTenista ganadorpunto;
	ganadorpunto = NADIE;
	turnox(servicio_para);
	pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datos.posicion, tenista2.datos.posicion, servicio_para, posbola); //pinta pista
	turnox(servicio_para);// Llama a turno para decidir  a quien le toca después del punto.
	while (ganadorpunto == NADIE) {// Bucle hasta que alguien gane.
		if (servicio_para == TENISTA1) {//If para decidir quien es el ganador segun el lance.
			system("pause");
			Lance = lance(servicio_para, tenista1, tenista2, posbola, juego);
			pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datos.posicion, tenista2.datos.posicion, servicio_para, posbola);
			if (Lance == 0) { //si no ha ganado nadie
				servicio_para = TENISTA2;
			}
			else if (Lance == 1) {//si gana 1
				ganadorpunto = TENISTA1;
				cout << "El ganador del punto es  " << tenista1.iniciales << endl;
			}
			else if (Lance == 2) { //si gana 2
				cout << "El ganador del punto es  " << tenista2.iniciales << endl;
				ganadorpunto = TENISTA2;

			}
		}
		else if (servicio_para == TENISTA2) {
			system("pause");
			Lance = lance(servicio_para, tenista2, tenista1, posbola, juego);
			pintarPeloteo(tenista1.iniciales, tenista2.iniciales, tenista1.datos.posicion, tenista2.datos.posicion, servicio_para, posbola);
			if (Lance == 0) {
				servicio_para = TENISTA1;
			}
			else if (Lance == 1) {
				cout << "El ganador del punto es  " << tenista1.iniciales << endl;
				ganadorpunto = TENISTA1;

			}
			else if (Lance == 2) {
				cout << "El ganador del punto es  " << tenista2.iniciales << endl;
				ganadorpunto = TENISTA2;
			}
		}
	}
	return ganadorpunto;

}
tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para, bool juego) {
	tTenista ganadorpunto;
	tTenista ganadorjuego;
	tenista1.datos.puntos = NADA;
	tenista2.datos.puntos = NADA;
	ganadorpunto = NADIE;
	ganadorjuego = NADIE;
	while (ganadorjuego == 0) {// Bucle hasta que alguien gane.
		pintarMarcador(tenista1.iniciales, tenista2.iniciales, tenista1.datos, tenista2.datos, servicio_para);//Dibuja el marcador con el nuevo resultado
		ganadorpunto = jugarPunto(tenista1, tenista2, servicio_para, juego);
		ganadorjuego = actualizarMarcador(ganadorpunto, tenista1.datos, tenista2.datos);// Va cambiando el marcador según cambia el resultado.
	}
	if (ganadorjuego == 1) {
		cout << "Ha ganado " << tenista1.iniciales << endl;
	}
	else
	{
		cout << "Ha ganado " << tenista2.iniciales << endl;
	}
	return ganadorjuego;

}
tTenista hayGanadorSet(tDatosTenista& tenista1, tDatosTenista& tenista2, tListaTenistas& listaT) {
	tTenista Ganador;
	Ganador = NADIE;
	int pos1 = buscarIniciales(listaT, tenista1.iniciales);
	int pos2 = buscarIniciales(listaT, tenista2.iniciales);
	int diferencia1 = 0, diferencia2 = 0;
	diferencia1 = tenista1.datos.juegos - tenista2.datos.juegos;
	diferencia2 = tenista2.datos.juegos - tenista1.datos.juegos;
	if ((tenista1.datos.juegos == 3) && (tenista2.datos.juegos <= 1)) {// If para saber si se cumple la condición para ganar el set.
		listaT.array[pos1].partidos_ganados += 1;
		listaT.array[pos2].partidos_perdidos += 1;
		Ganador = TENISTA1;
	}
	else if ((tenista2.datos.juegos == 3) && (tenista1.datos.juegos <= 1)) {
		listaT.array[pos2].partidos_ganados += 1;
		listaT.array[pos1].partidos_perdidos += 1;
		Ganador = TENISTA2;
	}
	else if ((tenista2.datos.juegos >= 2) && (diferencia1 == 2)) {
		listaT.array[pos1].partidos_ganados += 1;
		listaT.array[pos2].partidos_perdidos += 1;
		Ganador = TENISTA1;
	}
	else if ((tenista1.datos.juegos >= 2) && (diferencia2 == 2)) {
		listaT.array[pos2].partidos_ganados += 1;
		listaT.array[pos1].partidos_perdidos += 1;
		Ganador = TENISTA2;
	}
	return Ganador;
}
void inicializargolpes(tDatosPartido& datospartido1, tDatosPartido& datospartido2) {
	for (int i = 0; i < DIM_ARRAY_GOLPES; i++)//Bucle para inicializar los bordes
	{
		datospartido1.golpes[i] = 0;
		datospartido2.golpes[i] = 0;
	}
	datospartido1.golpes_ganadores = 0;
	datospartido2.golpes_ganadores = 0;
}
void sumarpunto(tPuntosJuego& punt) {
	switch (punt)//Va sumando los puntos.
	{
	case 0: punt = QUINCE;
		break;
	case 1:punt = TREINTA;
		break;
	case 2:punt = CUARENTA;
		break;
	case 3:punt = VENTAJA;
		break;
	case 4:punt = VICTORIA;
		break;

	}
}
void mostrarEstadisticas(string nombre, int golpesganados, tConteoGolpes golpes) {
	float sumagolpes;
	sumagolpes = golpes[0] + golpes[1] + golpes[2] + golpes[3] + golpes[4] + golpes[5] + golpes[6] + golpes[7] + golpes[8];//Suma el total de golpes, golpes ganados y errores no forzados y los muestra con porcentajes.
	cout << "Estadisticas de  " << nombre << endl;
	cout << "     " << "Golpes totales:  " << sumagolpes << endl;
	cout << "     " << "Golpes ganadores:  " << golpesganados << endl;
	cout << "     " << "Errores no forzados :  " << golpes[0] + golpes[8] << endl;
	cout << "     " << "Distribucion de los golpes en la pista :  " << endl;
	cout << "        " << "Calle  " << "    0     " << "  1     " << "   2   " << "    3   " << "    4   " << "     5   " << "     6   " << "   7   " << "    8   " << endl;
	cout << "        " << "%  " << "      " << fixed << setprecision(2) << float((golpes[0] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[1] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[2] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[3] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[4] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[5] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[6] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[7] * 100) / sumagolpes) << "    " << fixed << setprecision(2) << float((golpes[8] * 100) / sumagolpes) << endl;
}
bool cargar(tListaTenistas& listaT) {
	ifstream archivo;//Variable para leer el archivo
	listaT.contador = 0;//contador
	int eliminar;
	bool salida = true;
	string nombre;
	int hab;
	int vel;
	int pg;
	int pp;


	archivo.open("tenistas.txt", ios::in);//Abrir el archivo
	if (archivo.fail()) {//Si falla envia un mensaje
		salida = false;
		cout << "No se ha podido abrir el archivo" << endl;
	}
	else {
		while (archivo.eof() == false) {//Entra en bucle hasta que se acaba el archivo
			archivo >> nombre;
			listaT.array[listaT.contador].iniciales = nombre;
			archivo >> hab;
			listaT.array[listaT.contador].habilidad = hab;
			archivo >> vel;
			listaT.array[listaT.contador].velocidad = vel;
			archivo >> pg;
			listaT.array[listaT.contador].partidos_ganados = pg;
			archivo >> pp;
			listaT.array[listaT.contador].partidos_perdidos = pp;
			listaT.contador++;
		}

		for (int i = listaT.contador - 1; i < listaT.contador; i++)//Va recorriendo el array con el contador para añadir los datos
		{
			listaT.array[i] = listaT.array[i + 1];
		}
		listaT.contador--;
	}
	archivo.close();//Se cierrra el archivo
	return salida;
}
void mostrar(const tListaTenistas& listaT) {

	for (int i = 0; i < listaT.contador; i++) {//Bucle para mostrar cada tenista del array
		cout << listaT.array[i].iniciales << "  " << listaT.array[i].habilidad << "  " << listaT.array[i].velocidad << "  " << listaT.array[i].partidos_ganados << "  " << listaT.array[i].partidos_perdidos << endl;
	}
}
void mostrarIniciales(const tListaTenistas& listaT) {
	for (int i = 0; i < listaT.contador; i++) {//Bucle que muestra cada inicial
		cout << listaT.array[i].iniciales << "  ";
	}
	cout << endl;
}
int buscarIniciales(const tListaTenistas& listaT, string ini) {
	int posicion = -1;
	bool fin = false;
	int i = 0;
	while (fin == false && i < listaT.contador) {//Compaara la variable con todas las iniciales del array hasta encontrar la que busca
		if (ini == listaT.array[i].iniciales) {
			posicion = i;
			fin = true;
		}
		i++;
	}
	return posicion;
}
void eliminarTenista(tListaTenistas& listaT, string iniciales) {
	int indice;
	indice = buscarIniciales(listaT, iniciales);//Busca si el tenista existe
	if (indice == -1) {//Si no existe manda mensaje
		cout << "No existe ese tenista" << endl;
	}
	else {
		for (int i = indice; i < listaT.contador - 1; i++)//Si existe se mete en un for para encontrarlo y eliminarlo
		{
			listaT.array[i] = listaT.array[i + 1];
		}
		listaT.contador--;
	}
	guardar(listaT);//Y cuando lo elimina guarda la lista

}
void introducirTenista(tListaTenistas& listaT) {
	tDatosTenista nuevo;//Pide los datos del tenista
	nuevo.iniciales = pedir_nombre();
	nuevo.habilidad = pedir_habilidad();
	nuevo.velocidad = pedir_velocidad();
	nuevo.partidos_ganados = 0;
	nuevo.partidos_perdidos = 0;
	if (listaT.contador < 10) {//Recorre el array para ver si hay espacio y los añade en la ultima posicion
		listaT.array[listaT.contador] = nuevo;
		listaT.contador++;
	}
	guardar(listaT);//Guarda la lista
}
void guardar(tListaTenistas& listaT) {
	ofstream archivo;//Variable de archivo de salida
	archivo.open("tenistas.txt", ios::out);
	if (archivo.fail()) {
		cout << "No existe ese archivo" << endl;
	}
	else {
		for (int i = 0; i < listaT.contador; i++)//Bucle para ir devolviendo los nuevos valores que iran al archivo
		{
			archivo << listaT.array[i].iniciales << " " << listaT.array[i].habilidad << " " << listaT.array[i].velocidad << " " << listaT.array[i].partidos_ganados << " " << listaT.array[i].partidos_perdidos << endl;;
		}
	}

}
void mostrarOpciones() {
	cout << "<1> Ver datos tenistas" << endl;
	cout << "<2> Nuevo Tenista" << endl;
	cout << "<3> Eliminar Tenista" << endl;
	cout << "<4> Jugar Partido" << endl;
	cout << "<5> Torneo semifinales/final" << endl;
	cout << "<6> Torneo top-4" << endl;
	cout << "<0> Salir" << endl;
}
tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2, tListaTenistas& listaT) {
	tTenista tenista_golpea, ganadorjuego, fin;
	fin = NADIE;
	tenista_golpea = NADIE;
	ganadorjuego = NADIE;
	int saque;
	bool juego_aleatorio = NULL;
	bool endGame = false;
	aleatorio(juego_aleatorio);//elegir modo de juego
	cout << endl;
	saque = quien_comienza();//Averigua quien saca
	tenista1.datos.juegos = 0;
	tenista2.datos.juegos = 0;

	if (saque == 0) {//Condicional para saque de tenista
		tenista_golpea = TENISTA1;
		cout << "Servicio para : " << tenista1.iniciales << endl; //En caso de que empiece el jugador 1
	}
	else {
		tenista_golpea = TENISTA2;
		cout << "Servicio para : " << tenista2.iniciales << endl; //En caso de que empiece el jugador 2
	}
	while (endGame == false) {//Bucle hasta que hay un ganador
		inicializargolpes(tenista1.datos, tenista2.datos);//Reiniciar stats
		ganadorjuego = jugarJuego(tenista1, tenista2, tenista_golpea, juego_aleatorio);//Funcion que lleva a cabo el juego
		mostrarEstadisticas(tenista1.iniciales, tenista1.datos.golpes_ganadores, tenista1.datos.golpes);
		mostrarEstadisticas(tenista2.iniciales, tenista2.datos.golpes_ganadores, tenista2.datos.golpes);

		if (hayGanadorSet(tenista1, tenista2, listaT) == TENISTA1) {
			fin = TENISTA1;
			endGame = true;
		}
		else if (hayGanadorSet(tenista1, tenista2, listaT) == TENISTA2) {
			fin = TENISTA2;
			endGame = true;
		}
		else {
			turnox(tenista_golpea);//Cambio de servicio
		}
	}
	guardar(listaT);//LO guarda en archivo
	return fin;
}
tDatosTenista seleccionartenista(string iniciales, tListaTenistas& listaT) {
	tDatosTenista fin;
	for (int i = 0; i < listaT.contador; i++)//Recorrre el array hasta que las iniciales que buscas sean iguales a las de alguno de la lista
	{
		if (iniciales == listaT.array[i].iniciales) {
			fin = listaT.array[i];
		}
	}
	return fin;
}
void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4) {
	tTenista ganador1, ganador2, ganadorfinal;
	int indfinal1, indfinal2;
	indfinal1 = NULL;
	indfinal2 = NULL;
	ganador1 = NADIE;
	ganador2 = NADIE;
	ganadorfinal = NADIE;
	ganador1 = jugarPartido(listaT.array[indT1], listaT.array[indT2], listaT);
	if (ganador1 == TENISTA1) {//Condicional par decidir el ganador de cada partido
		cout << "*El ganador de la primera semifinal es  " << listaT.array[indT1].iniciales << "*";
		indfinal1 = indT1;
	}
	else {
		cout << "*El ganador de la primera semifinal es  " << listaT.array[indT2].iniciales << "*";
		indfinal1 = indT2;
	}
	cout << endl;
	ganador2 = jugarPartido(listaT.array[indT3], listaT.array[indT4], listaT);
	if (ganador2 == TENISTA1) {
		cout << "*El ganador de la segunda semifinal es  " << listaT.array[indT3].iniciales << "*";
		indfinal2 = indT3;
	}
	else {
		cout << "*El ganador de la segunda semifinal es  " << listaT.array[indT4].iniciales << "*";
		indfinal2 = indT4;
	}
	cout << endl;
	ganadorfinal = jugarPartido(listaT.array[indfinal1], listaT.array[indfinal2], listaT);
	if (ganadorfinal == TENISTA1) {
		cout << "*El ganador del torneo es :  " << listaT.array[indfinal1].iniciales << "*";
	}
	else {
		cout << "*El ganador del torneo es  " << listaT.array[indfinal2].iniciales << "*";
	}
	cout << endl;
}
int postenista(tListaTenistas& listaT, string iniciales) {
	int pos = -1;
	for (int i = 0; i < listaT.contador; i++)//Bucle para buscar un tenista
	{
		if (iniciales == listaT.array[i].iniciales) {//COndicional para declarar su posicion
			pos = i;
		}
	}
	return pos;
}
void ordenarlista(tListaTenistas& listaT) {
	tDatosTenista aux;
	for (int i = 0; i < listaT.contador; i++)//Bucle para recorreer array
	{
		for (int j = 0; j < listaT.contador; j++)
		{
			if (listaT.array[j + 1].partidos_ganados >= listaT.array[j].partidos_ganados) {//Condicional para ordenarlos por partidos ganados
				aux = listaT.array[j + 1];
				listaT.array[j + 1] = listaT.array[j];
				listaT.array[j] = aux;
			}
		}
	}
}
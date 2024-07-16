#include <iostream>
#include <fstream>
#include <string>
 

using namespace std;

const int MAX_COCHES = 200;
const int MAX_PLAZAS = 25;
const int MAX_ZONAS = 10;


typedef enum tipocoche {Mini,Medio,Suv,Grande};

typedef struct {
	tipocoche tipo;
	string matricula;
	string horallegada;
}tCoche;

typedef tCoche tarraycoches[MAX_COCHES];

typedef struct {
	tarraycoches listacoches;
	int contador;
	int desatendidos;
}tListacoches;

typedef struct {
	string matricula;
	string horallegada;
	tCoche coche;
}tPlaza;

typedef tPlaza tarrayplaza[MAX_PLAZAS];

typedef struct {
	char letra;
	int tipo;
	int capacidad;
	tarrayplaza listaplazas;
	int cochescolocados;
}tZona;

typedef tZona tarrayzona[MAX_ZONAS];

typedef struct {
	tarrayzona zona;
	int contador;
}tParking;

bool cargaZonas(tParking& parking);
bool cargaCoches(tListacoches& listacoches);
tipocoche Inttotipo(int tipo);
int siguiente(const tListacoches& listacoches);
int buscaZona(const tParking& parking, tCoche coche);
void asigna(tListacoches& desatendidos, tListacoches& listacoches, tParking& parking);
void elimina(tListacoches& listacoches, int indice);
void muestra(const tListacoches& listacoches);
void muestra2(const tParking& parking);
void guardar(const tListacoches& listacoches);

int main() {
	tParking parking;
	tListacoches listacoches;
	cargaZonas(parking);
	cargaCoches(listacoches);
	siguiente(listacoches);

	return 0;
}
bool cargaZonas(tParking& parking) {
	ifstream archivo;
	bool salida = true;
	char letra;
	int tipo;
	int capacidad;
	archivo.open("zonas.txt", ios::in);
	if (archivo.fail())
	{
		salida = false;
		cout << "No se ha podido abrir" << endl;
	}
	if (salida==true)
	{
		for (int i = 0; i < MAX_ZONAS; i++)
		{
			archivo >> letra;
			parking.zona[i].letra = letra;
			archivo >> tipo;
			parking.zona[i].tipo = tipo;
			archivo >> capacidad;
			parking.zona[i].capacidad = capacidad;
			
		}
	}
	archivo.close();
	return salida;
}
bool cargaCoches(tListacoches& listacoches) {
	ifstream archivo2;
	bool salida = true;
	listacoches.contador = 0;
	int tipo;
	string matricula;
	string horallegada;
	archivo2.open("coches.txt", ios::in);
	if (archivo2.fail())
	{
		salida = false;
		cout << "no se ha podido abrir" << endl;
	}
	if (salida==true)
	{
		archivo2 >> tipo;
		while ((tipo!=-1) && (listacoches.contador<MAX_COCHES))
		{
			listacoches.listacoches[listacoches.contador].tipo = Inttotipo(tipo);
			archivo2 >> matricula;
			listacoches.listacoches[listacoches.contador].matricula = matricula;
			archivo2 >> horallegada;
			listacoches.listacoches[listacoches.contador].horallegada = horallegada;
			listacoches.contador++;
			archivo2 >> tipo;
		}
	}

	archivo2.close();
	return salida;
}
tipocoche Inttotipo(int tipo) {
	tipocoche coche;
	if (tipo==0)
	{
		coche = Mini;
	}
	if (tipo == 1)
	{
		coche = Medio;
	}
	if (tipo == 2)
	{
		coche =Suv ;
	}
	if (tipo == 3)
	{
		coche = Grande;
	}

	return coche;
}
int siguiente(const tListacoches& listacoches) {
	
	int indice=-1;
	string mayor;
	bool salida = false;
	/*for (int i = 0;(i < listacoches.contador)&&(salida==false); i++)
	{
		if (listacoches.listacoches[i].horallegada.substr(0,2) > mayor.substr(0,2))
		{
			listacoches.listacoches[i].horallegada == mayor;
			indice = i;
			salida = true;
		}
		else if (listacoches.listacoches[i].horallegada.substr(0, 2) == mayor.substr(0,2))
		{
			if (listacoches.listacoches[i].horallegada.substr(2, 4) > mayor.substr(2,4)) {
				listacoches.listacoches[i].horallegada == mayor;
				indice = i;
				salida = true;
			}
			else if (listacoches.listacoches[i].horallegada.substr(2, 4) == mayor.substr(2, 4)) {
				if (listacoches.listacoches[i].horallegada.substr(4, 2) > mayor.substr(4, 2))
				{
					listacoches.listacoches[i].horallegada == mayor;
					indice = i;
					salida = true;
				}
			}
		}
	}*/
	for (int i = 0; i < listacoches.contador; i++)
	{
		if (listacoches.listacoches[i].horallegada >= mayor) {
			mayor = listacoches.listacoches[i].horallegada;
			indice = i;
		}
	}

	return indice;
}
int buscaZona(const tParking& parking, tCoche coche) {
	int indice=-1;
	bool salida = false;
	for (int i = 0; (salida==false )&&(i < parking.contador); i++)
	{
		if ((parking.zona[i].tipo==coche.tipo)&&(parking.zona[i].capacidad>0)) {
			indice = i;
			salida = true;
		}
	}
	return indice;
}
void asigna(tListacoches& desatendidos, tListacoches& listacoches, tParking& parking){
	int mayor;
	int indice;
	tCoche coche;
	desatendidos.desatendidos = 0;
	while(parking.contador>0)
	{
		mayor = siguiente(listacoches);
		indice = buscaZona(parking, listacoches.listacoches[mayor]);
		if (indice!=-1)
		{
			parking.zona[indice].listaplazas[parking.zona[indice].cochescolocados] = coche;
			parking.zona[indice].cochescolocados++;
			parking.zona[indice].capacidad--;
		}
		else
		{
			desatendidos.listacoches[desatendidos.desatendidos] = coche;
			desatendidos.desatendidos++;
		}
	}
}
void elimina(tListacoches& listacoches, int indice) {
	for (int i = indice; i < listacoches.contador - 1; i++)
	{
		listacoches.listacoches[i] = listacoches.listacoches[i + 1];
		
	}
	listacoches.contador--;
}
void muestra(const tListacoches& listacoches) {
	for (int i = 0; i < listacoches.contador; i++)
	{
		cout << listacoches.listacoches[i].matricula << "  " << listacoches.listacoches[i].horallegada << endl;
	}
}
void muestra2(const tParking& parking) {
	for (int i = 0; i < parking.contador; i++)
	{
		cout << "Zona  " << parking.zona[i].letra << "  -  " << parking.zona[i].tipo << "  ocupadas" << parking.zona[i].capacidaddisponible << "plazas de " << parking.zona[i].capacidad << endl;
		muestra(parking.zona[i].listaplazas[i]);
	}
	cout << "Coches que no han sido atendidos" << endl;
	for (int i = 0; i < parking; i++)
	{
		cout << "Zona  " << parking.zona[i].letra << "  -  " << parking.zona[i].tipo << "  ocupadas" << parking.zona[i].capacidaddisponible << "plazas de " << parking.zona[i].capacidad << endl;
		muestra();
	}
}
void guardar(const tListacoches& listacoches) {
	ofstream archivo;
	bool salida = true;
	int i = 0;
	archivo.open("desatendidos.txt", ios::out);
	if (archivo.fail())
	{
		cout << "No se ha podido crear" << endl;
		salida = false;
	}
	if (salida==true)
	{
		archivo << listacoches.listacoches[i].tipo;
		while (listacoches.listacoches[i].tipo != -1) {
			archivo << listacoches.listacoches[i].matricula;
			archivo << listacoches.listacoches[i].horallegada;
			i++;
		}
	}
	archivo << -1;
	archivo.close();
}

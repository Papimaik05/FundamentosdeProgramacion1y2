#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_AVISOS =50 ;
const int MAX_INCIDENCIAS = 3 ;

typedef string tArrayIncidencias[MAX_INCIDENCIAS];

typedef struct {
	tArrayIncidencias incidencias;
	int contador;

}tListaincidencias;

typedef struct {
	string identificador;
	int inicio;
	int final;
	tListaincidencias incidencias;
}tAviso;
typedef tAviso tArrayaviso[MAX_AVISOS];
typedef struct {
	tArrayaviso avisoarray;
	int contador;

}tRegistro;

bool cargar(tRegistro& registro);
int menu(tRegistro registro);
int buscar(tRegistro registro, string identificador, int puntokilometrico);
bool eliminar(tRegistro& registro, string identificador, int puntokilometrica);
void consultar(tRegistro registro, string identificador, int puntokilometrico);
void mostrar(tRegistro registro);

int main() {
	tRegistro registro;
	cargar(registro);
	menu(registro);


	return 0;
}
bool cargar(tRegistro& registro) {
	bool salida = true;
	ifstream archivo;
	string identificador;
	registro.contador = 0;
	int inicio;
	int final;
	int numincidencias;
	string incidencias;
	archivo.open("carreteras.txt", ios::in);
	if (archivo.fail())
	{
		salida = false;
		cout << "no se ha podido abrir el archivo" << endl;
	}
	else if (salida==true)
	{
		archivo >> identificador;
		while (identificador!="XXX")
		{
			registro.avisoarray[registro.contador].identificador = identificador;
			archivo >> inicio;
			registro.avisoarray[registro.contador].inicio = inicio;
			archivo >> final;
			registro.avisoarray[registro.contador].final = final;
			archivo >> numincidencias;
			registro.avisoarray[registro.contador].incidencias.contador = numincidencias;
			for (int i = 0; i < numincidencias; i++)
			{
				archivo >> incidencias;
				registro.avisoarray[registro.contador].incidencias.incidencias[i] = incidencias;
			}
			registro.contador++;
			archivo >> identificador;
		}
	}

	archivo.close();
	return salida;
}
int menu(tRegistro registro) {
	int opcion=1;

	string identificador;
	int puntokilometrico;
	bool salida;
	while (opcion != 0)
	{
		cout << "1 - Lista de avisos" << endl;
		cout << "2 - Consultar punto kilometrico " << endl;
		cout << "3 - Eliminar aviso" << endl;
		cout << "0 - Salir" << endl;
		cin >> opcion;

		if (opcion==1)
		{
			mostrar(registro);
		}
		if (opcion == 2)
		{
			cout << "Introduce identificador de via" << endl;
			cin >> identificador;
			cout << "Introduce punto kilometrico" << endl;
			cin >> puntokilometrico;

			consultar(registro, identificador, puntokilometrico);
		}
		if (opcion == 3)
		{
			cout << "Introduce identificador de via" << endl;
			cin >> identificador;
			cout << "Introduce punto kilometrico" << endl;
			cin >> puntokilometrico;
			salida=eliminar(registro, identificador, puntokilometrico);
		}

	}
	

	return opcion;
}
int buscar(tRegistro registro, string identificador, int puntokilometrico){
	int indice = -1;
	bool salida = false;
	for (int i = 0; (salida==false)&&(i < registro.contador); i++)
	{
		if ((identificador==registro.avisoarray[i].identificador)&&(registro.avisoarray[i].inicio <= puntokilometrico )&&(puntokilometrico <= registro.avisoarray[i].final)) {
			indice = i;
			salida = true;
		}
	}


	return indice;
}
bool eliminar(tRegistro &registro,string identificador,int puntokilometrico) {
	bool salida = true;
	int indice;
	indice = buscar(registro, identificador, puntokilometrico);
	if (indice!=-1)
	{
		for (int i = indice; i < registro.contador - 1; i++)
		{
			registro.avisoarray[i] = registro.avisoarray[i + 1];
		}
		registro.contador--;
	}
	else if (indice=-1)
	{
		cout << "no se ha encontrado un aviso que afecte a ese lugar" << endl;
		salida = false;
	}
	return salida;
}
void consultar(tRegistro registro, string identificador, int puntokilometrico) {
	int indice;
	indice = buscar(registro, identificador, puntokilometrico);
	if (indice != -1)
	{
		for (int i = 0; i < registro.avisoarray[indice].incidencias.contador; i++)
		{
			cout << registro.avisoarray[indice].incidencias.incidencias[i] << endl;
		}
	}
	else if (indice = -1)
	{
		cout << "Se puede transitar con normalidad" << endl;
	
	}
	
}
void mostrar(tRegistro registro) {
	for (int i = 0; i < registro.contador; i++)
	{
		cout << registro.avisoarray[i].identificador << "  " << registro.avisoarray[i].inicio << "  " << registro.avisoarray[i].final << "  " << registro.avisoarray[i].incidencias.contador <<"  ";
		for (int j = 0; j < registro.avisoarray[i].incidencias.contador; j++)
		{
			cout << registro.avisoarray[i].incidencias.incidencias[j] << " ";
		}
		cout << endl;
	}
}


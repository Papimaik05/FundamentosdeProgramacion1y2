#include <iostream>
#include <string>
#include "Funciones_TAD.h"
#include "wchar.h"

using namespace std;

const int MAX = 10;

typedef tConjunto tArrayPartida[MAX];

typedef struct {
    tArrayPartida partida;
    int contador;
}tPartida;


void partidamain(tPartida partida);
void mostrar(tPartida partida);
int opciones();


int main()
{
    tPartida partida;
    partida.contador = 0;
    setlocale(LC_ALL, "");
    partidamain(partida);
    return 1;
}

void partidamain(tPartida partida) {
    int respuesta=0;
    bool pertene = false;
    while (respuesta!=12) {
        system("cls");
        mostrar(partida);
        respuesta = opciones();
        if (respuesta==1) {
            crearConjuntoVacio(partida.partida[partida.contador]);
            partida.contador++;
        }
        else if (respuesta == 2) {
            int eleccion1, eleccion2;
            mostrar(partida);
            cout << "¿A que conjunto quieres añadir un elemento? ";
            cin >> eleccion1;
            cout << "¿Que elemento quieres añadir? ";
            cin >> eleccion2;
            insertar(partida.partida[eleccion1], eleccion2);
        }
        else if (respuesta ==3) {
            int elemento, eleccion1 = 0;
            cout << "¿A que conjunto quieres checkear? ";
            cin >> eleccion1;
            cout << "¿Que elemento quieres comprobar? ";
            cin >> elemento;
            pertene = pertenece(partida.partida[eleccion1], elemento);
            if (pertene) {
                cout << "El elemento pertenece\n";
            }
            else {
                cout << "El elemento NO pertenece\n";
            }
        }
        else if (respuesta == 4) {
            int elemento, eleccion1 = 0;
            cout << "¿A que conjunto quieres eliminar un elemento? ";
            cin >> eleccion1;
            cout << "¿Que elemento quieres eliminar? ";
            cin >> elemento;
            eliminar(partida.partida[eleccion1],elemento);
        }
        else if (respuesta == 5) {
            int eleccion1, eleccion2;
            cout << "¿elige el primer conjunto? ";
            cin >> eleccion1;
            cout << "¿elige el segundo conjunto? ";
            cin >> eleccion2;
            crearConjuntoVacio(partida.partida[partida.contador]);
            partida.partida[partida.contador] = partida.partida[eleccion1] * partida.partida[eleccion2];
            partida.contador++;
        }
        else if (respuesta == 6) {
            int eleccion1, eleccion2;
            cout << "¿elige el primer conjunto? ";
            cin >> eleccion1;
            cout << "¿elige el segundo conjunto? ";
            cin >> eleccion2;
            crearConjuntoVacio(partida.partida[partida.contador]);
            partida.partida[partida.contador] = partida.partida[eleccion1] + partida.partida[eleccion2];
            partida.contador++;
        }
        else if (respuesta == 7) {
            int eleccion1, eleccion2;
            cout << "¿elige el primer conjunto? ";
            cin >> eleccion1;
            cout << "¿elige el segundo conjunto? ";
            cin >> eleccion2;
            crearConjuntoVacio(partida.partida[partida.contador]);
            partida.partida[partida.contador] = partida.partida[eleccion1] - partida.partida[eleccion2];
            partida.contador++;
        }
        else if (respuesta == 8) {
            int eleccion1, eleccion2;
            bool pertence = false;
            cout << "¿elige el primer conjunto? ";
            cin >> eleccion1;
            cout << "¿elige el segundo conjunto? ";
            cin >> eleccion2;
            pertence = partida.partida[eleccion1] << partida.partida[eleccion2];
            if (pertence) {
                cout << "El conjunto "<<eleccion1 << " pertenece al conjunto "<< eleccion2 <<"\n";
            }
            else {
                cout << "El conjunto " << eleccion1 << " NO pertenece al conjunto " << eleccion2 << "\n";
            }
        }
        else if (respuesta == 9) {
            int eleccion1;
            bool pertence = false;
            cout << "¿elige el conjunto? ";
            cin >> eleccion1;
            pertence = conjuntoVacio(partida.partida[eleccion1]) ;
            if (pertence) {
                cout << "El conjunto "<<eleccion1<<" esta vacio\n";
            }
            else {
                cout << "El conjunto " << eleccion1 << " NO esta vacio\n";
            }
        }
        else if (respuesta == 10) {
            int eleccion1;
            cout << "¿Que conjunto quieres ver? ";
            cin >> eleccion1;
            cout << "- " << eleccion1 << " : ";
            mostrar(partida.partida[eleccion1]);
        }
        else if (respuesta == 11) {
        int eleccion1, eleccion2;
        bool pertence = false;
        cout << "¿elige el primer conjunto? ";
        cin >> eleccion1;
        cout << "¿elige el segundo conjunto? ";
        cin >> eleccion2;
        pertence = partida.partida[eleccion1] == partida.partida[eleccion2];
        if (pertence) {
            cout << "El conjunto " << eleccion1 << " es igual al conjunto " << eleccion2 << "\n";
        }
        else {
            cout << "El conjunto " << eleccion1 << " NO es igual al conjunto " << eleccion2 << "\n";
        }
        }
        else if (respuesta == 12) {
            cout << "Gracias por usar este programa.\n";
        }
        else {
            cout << "Opcion no valida";
            respuesta = 1;
        }
        system("pause");
    }
}


int opciones() {
    int eleccion=1;
    cout << "¿Que accion quieres realizar?:\n[1].Crear nuevo conjunto\n[2].Añadir elemeto al conjunto\n[3].Determina si un elemento pertenece a un conjunto\n[4].Eliminar elemento del conjunto\n[5].Interseccion de dos conjuntos\n[6].Union de dos conjuntos\n[7].Diferencia de dos conjuntos\n[8].Esta incluido un conjunto en otro\n[9].Determina si el conjutno esta vacio o no\n[10].Mostrar conjuntos\n[11].Comparar dos conjuntos\n[12].Salir\n";
    cin >> eleccion;
    while (eleccion <= 0 || eleccion >= 13) {
        cout << "Elige una opcion valida:\n";
        cin >> eleccion;
    }
    return eleccion;
}

void mostrar(tPartida partida) {
    cout << "Vamos a mostrar los conjuntos activos:\n";
    for (int i = 0; i < partida.contador;i++) {
        cout << "- " << i << " : ";
        mostrar(partida.partida[i]);
    }
    cout << endl;
}
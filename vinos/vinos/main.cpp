#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "Vinos.h"
#include "Bodega.h"

using namespace std;

int main() {
	tListaVinos vino;
	ifstream archivo;
	cargar(archivo, vino);
	mostrar(vino);

	return 0;
}
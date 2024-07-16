#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ESTANTERIAS =15 ;
const int MAX_LIBROS = 100;

typedef enum  tArea { Matematicas, Fisica, Informatica };
typedef struct {
	tArea area;
	int numpag;
	string titulo;
}tLibro;

typedef tLibro tArraylibros[MAX_LIBROS];

typedef struct {
	tArraylibros maxlistalibros;
	int contador;
	int librossincolocar;
}tListaLibros;

typedef struct {
	tArea area;
	tListaLibros  listalibros;
	int capacidad;
	int numpagdispo;
	int listalibroscolocados;
}tEstanteria;

typedef tEstanteria tArrayBiblioteca[MAX_ESTANTERIAS];
typedef struct {
	tArrayBiblioteca arraybiblio ;
	int contador;
}tBiblioteca;

tArea strToArea(string nombre);
bool cargarEstanterias(tBiblioteca& biblioteca);
bool cargarLibros(tListaLibros& listaLibros);
void borrarLibro(tListaLibros &listaLibros,int indice);
tLibro mayor(tListaLibros& listaLibros);
int buscarEstanteria(const tBiblioteca& biblioteca, tLibro libro);
void asignar(tBiblioteca& biblioteca, tListaLibros listaLibros, tListaLibros& sinColocar);
string areaToStr(tArea area);
void mostrarLibros(const tListaLibros& listaLibros);
void mostrarBiblioteca(const tBiblioteca& biblioteca);

int main() {








	return 0;
}
tArea strToArea(string nombre) {
	tArea area ;
	if (nombre == "Inf")
	{
		area = Informatica;
	}
	if (nombre == "Mat")
	{
		area = Matematicas;
	}
	if (nombre == "Fis")
	{
		area = Fisica;
	}
	return area;
}
bool cargarEstanterias(tBiblioteca& biblioteca) {
	ifstream archivo;
	int numeroestanterias;
	string area;
	int paginas;
	bool salida = true;
	archivo.open("biblioteca.txt", ios::in);
	if (archivo.fail())
	{
		cout << "No has podido abrir el archivo" << endl;
		salida = false;
	}
	if (salida==true)
	{
		archivo >> numeroestanterias;
		biblioteca.contador = numeroestanterias;
		for (int i = 0; i < biblioteca.contador; i++)
		{
			archivo >> area;
			biblioteca.arraybiblio[i].area = strToArea(area);
			archivo >> paginas;
			biblioteca.arraybiblio[i].capacidad = paginas;
			biblioteca.arraybiblio[i].numpagdispo = paginas;
		}
	}
	return salida;
}
bool cargarLibros(tListaLibros& listaLibros) {
	ifstream archivo2;
	bool salida = true;
	string area;
	int numpaginas;
	string titulo;
	listaLibros.contador = 0;
	archivo2.open("libros.txt", ios::in);
	if (archivo2.fail())
	{
		salida = false;
	}
	if (salida = true) {
		archivo2 >> area;
		while (area != "XXX")
		{
			listaLibros.maxlistalibros[listaLibros.contador].area = strToArea(area);
			archivo2 >> numpaginas;
			listaLibros.maxlistalibros[listaLibros.contador].numpag = numpaginas;
			getline(archivo2, titulo);
			listaLibros.maxlistalibros[listaLibros.contador].titulo = titulo;
			listaLibros.contador++;
		    archivo2 >> area;

		}
	}
	return salida;
}
void borrarLibro(tListaLibros& listaLibros,int indice){
	if (indice<0 || indice>listaLibros.contador) {
		cout << "No puedes eliminar este libro" << endl;
	}
	else
	{
		for (int i = indice; i < listaLibros.contador - 1; i++)
		{
			listaLibros.maxlistalibros[i] = listaLibros.maxlistalibros[i + 1];
		}
		listaLibros.contador--;
	}
	
}
tLibro mayor(tListaLibros& listaLibros) {
	tLibro libromayor;
	int masgrande;
	int mayor = 0;
	for (int i = 0; i < listaLibros.contador; i++)
	{
		if (listaLibros.maxlistalibros[i].numpag>=mayor)
		{
			mayor = listaLibros.maxlistalibros[i].numpag;
			masgrande = i;
			libromayor = listaLibros.maxlistalibros[masgrande];
		}
	}
	borrarLibro(listaLibros, masgrande);
	return libromayor;
}
int buscarEstanteria(const tBiblioteca& biblioteca, tLibro libro) {
	int indice;
	bool encontrado = false;
	for (int i = 0; (i < biblioteca.contador)&&(encontrado=false); i++)
	{
		if ((biblioteca.arraybiblio[i].area == libro.area) && (biblioteca.arraybiblio[i].numpagdispo > libro.numpag)) {
			indice = i;
			encontrado = true;
		}
		else
		{
			indice = -1;
		}
	}
	return indice;
}
void asignar(tBiblioteca& biblioteca, tListaLibros listaLibros, tListaLibros& sinColocar) {
	tLibro libromayor;
	int indice;
	listaLibros.librossincolocar = 0;
	while (listaLibros.contador > 0) {
		libromayor = mayor(listaLibros);
		indice = buscarEstanteria(biblioteca, libromayor);
		if (indice != -1)
		{
			biblioteca.arraybiblio[indice].listalibros.maxlistalibros[biblioteca.arraybiblio[indice].listalibroscolocados = libromayor;
		    biblioteca.arraybiblio[indice].capacidad -= listaLibros.maxlistalibros[indice].numpag;
			biblioteca.arraybiblio[indice].listalibroscolocados++;
		}
		if (indice = -1)
		{
			sinColocar.maxlistalibros[sinColocar.librossincolocar] = libromayor;
			sinColocar.librossincolocar++;
			
		}
		
	}
	
	

}
string areaToStr(tArea area) {
	string areato;
	if (area=Informatica)
	{
		areato = "Inf";
	}
	if (area = Matematicas)
	{
		areato = "Mat";
	}
	if (area = Fisica)
	{
		areato = "Fis";
	}


	return areato;
}
void mostrarLibros(const tListaLibros& listaLibros) {
	for (int i = 0; i < listaLibros.contador; i++)
	{
		cout << listaLibros.maxlistalibros[i].titulo << "  " << "(" << listaLibros.maxlistalibros[i].numpag << " " << "paginas)" << endl;
	}
	cout << "Libros sin colocar" << endl;
	for (int i = 0; i < listaLibros.librossincolocar; i++)
	{
		cout << listaLibros.maxlistalibros[i].titulo << "  " << "(" << listaLibros.maxlistalibros[i].numpag << " " << "paginas)" << endl;
	}
}
void mostrarBiblioteca(const tBiblioteca& biblioteca) {
	for (int i = 0; i < biblioteca.contador; i++)
	{
		cout << biblioteca.arraybiblio[i].area << "  (  " << biblioteca.arraybiblio[i].capacidad << "  /  " << biblioteca.arraybiblio[i].numpagdispo << ")" << endl;
		mostrarLibros(biblioteca.arraybiblio[i].listalibros);
	}
}
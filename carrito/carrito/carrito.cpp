#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_PRODUCTOS = 100;

typedef struct {

	string nombreproducto;
	int codigo;
	int unidadesdisponibles;
	double precio;

}tProducto;

typedef tProducto tArrayproductos[MAX_PRODUCTOS];

typedef struct {

	int unidades;
	tArrayproductos productoseleccionado;

}tProductosComprados;

typedef struct {

	int contador;
	tArrayproductos productos;

}tProductos;

typedef struct {

	double preciototal;
	tProductosComprados productos;

}tCarrito;

bool cargar(tProductos& productos);
void guardar(const tProductos& productos);
void generarFactura(tCarrito carrito);
bool codigoCorrecto(int codigo, const tProductos& productos);
bool cantidadCorrecta(int codigo, int cantidad, const tProductos& productos);
int elegirItem(tProductos& productos, tCarrito& carrito);
void mostrar(const tProductos& productos, const tCarrito& carrito);
void comprar(int codigo, int cantidad, tProductos& productos, tCarrito& carrito);
int menu(tProductos producto);
void eliminarItem(tProductos& productos, tCarrito& carrito);

int main() {
	tProductos  productos;
	tCarrito carrito;
	cargar(productos);
	guardar(productos);
	mostrar(productos, carrito);



	return 0;
}
bool cargar(tProductos& productos) {

	ifstream archivo;
	bool salida = true;
	int codigo;
	double precio;
	int unidades;
	string nombre;
	productos.contador = 0;
	archivo.open("catalogo.txt", ios::in);
	if (archivo.fail())
	{
		cout << "No se ha podido abrir el archivo" << endl;
		salida = false;
	}
	if (salida==true)
	{
		archivo >> codigo;
		while (codigo!=-1)
		{
			productos.productos[productos.contador].codigo = codigo;
			archivo >> precio;
			productos.productos[productos.contador].precio = precio;
			archivo >> unidades;
			productos.productos[productos.contador].unidadesdisponibles = unidades;
			getline(archivo, nombre);
			productos.productos[productos.contador].nombreproducto = nombre;
			productos.contador++;
			archivo >> codigo;
		}
		//productos.productos[productos.contador].codigo = codigo;
	}

	archivo.close();

	return salida;
}
void guardar(const tProductos& productos) {
	ofstream archivo2;
	bool salida = true;
	int i = 0;
	archivo2.open("catalogo2.txt", ios::out);
	if (archivo2.fail())
	{
		salida = false;
		cout << "no se ha podido abrir el archivo" << endl;
	}
	if (salida==true)
	{
		/*archivo2 << productos.productos[i].codigo;
		
		while (productos.productos[i].codigo != -1)
		{
			archivo2 << "  ";
			archivo2 << productos.productos[i].precio ;
			archivo2 << "  ";
			archivo2 << productos.productos[i].unidadesdisponibles ;
			archivo2 << productos.productos[i].nombreproducto << endl; 
			i++;
			archivo2 << productos.productos[i].codigo;
		}*/
		for (int i = 0; i < productos.contador; i++)
		{
			archivo2 << productos.productos[i].codigo;
			archivo2 << " ";
			archivo2 << productos.productos[i].precio;
			archivo2 << " ";
			archivo2 << productos.productos[i].unidadesdisponibles;
			archivo2 << " ";
			archivo2 << productos.productos[i].nombreproducto;
			archivo2 << endl;
		}
	}
	archivo2 << -1;

	archivo2.close();
}
void generarFactura(tCarrito carrito) {
	ofstream factura;
	bool salida = true;
	factura.open("factura.txt", ios::out);
	if (factura.fail())
	{
		salida = false;
		cout << "no se ha podido abrir el archivo" << endl;
	}
	if (salida == true)
	{
		for (int i = 0; i < carrito.productos.unidades; i++)
		{
			factura << carrito.productos.productoseleccionado[i].codigo;
			factura << " ";
			factura << carrito.productos.productoseleccionado[i].nombreproducto;
			factura << "  ";
			factura << carrito.productos.productoseleccionado[i].unidadesdisponibles;
			factura << " ";
			
		}
	}
	factura << carrito.preciototal;
}
bool codigoCorrecto(int codigo, const tProductos& productos){
	bool salida = false;
	for (int i = 0; i < productos.contador; i++)
	{
		if (codigo == productos.productos[i].codigo)
		{
			salida = true;
			cout << "el  codigo coincide" << endl;
		}
	}


	return salida;
}
bool cantidadCorrecta(int codigo, int cantidad, const tProductos& productos) {
	bool salida;
	bool cantidadcorrecta=false;
	salida = codigoCorrecto(codigo, productos);

	if (salida == true)
	{
		for (int i = 0; i < productos.contador; i++)
		{
			if ((cantidad <= productos.productos[i].unidadesdisponibles) && (codigo == productos.productos[i].codigo)) {
				cantidadcorrecta = true;
				cout << "No coincide la cantidad" << endl;
			}
		}
	
	}
	else if(salida==false)
	{
		cout << "el codigo no coincide" << endl;
	}

	return cantidadcorrecta;
}
int elegirItem(tProductos& productos, tCarrito& carrito) {

	bool cantidadcorrecta;
	mostrar(productos, carrito);
	int codigo;
	int unidad;
	cout << "Introduce el codigo de el producto que desea comprar" << endl;
	cin >> codigo;
	cout << "Introduce el numero de unidades que desea" << endl;
	cin >> unidad;
	bool cantidadcorrecta= cantidadCorrecta(codigo,unidad,productos);
	if (cantidadcorrecta==true)
	{
		comprar(codigo, unidad, productos, carrito);
	}
	else if (cantidadcorrecta == false) {
		cout << "No coincide el codigo o no hay el numero de unidades que desea" << endl;
	}
	return 1;
}
void comprar(int codigo, int cantidad, tProductos& productos, tCarrito& carrito) {
	int preciototal=0;
	productos.productos[productos.productos[productos.contador].codigo].unidadesdisponibles-=cantidad;
	carrito.productos.unidades++;
    preciototal += carrito.productos.productoseleccionado[productos.productos[productos.contador].codigo].precio;
	carrito.preciototal = preciototal * 0.21;
}
void mostrar(const tProductos& productos, const tCarrito& carrito) {
	cout << "Productos disponibles " << endl;
	cout << "Codigo" << "  " << " Precio " << "  " << "Cantidad" << "  " << "Nombre" << endl;
	cout << "========================================" << endl;
	for (int i = 0; i < productos.contador; i++)
	{
		cout << productos.productos[i].codigo << "        " << productos.productos[i].precio << "       " << productos.productos[i].unidadesdisponibles << "    " << productos.productos[i].nombreproducto << endl;
	}
	cout << "Estado del carrito" << endl;
	if (carrito.productos.unidades==0)
	{
		cout << "Carrito vacio" << endl;
	}
	else if (carrito.productos.unidades == 0)
		cout << "Codigo" << "  " << " Nombre " << "  " << "Precio" << endl;
	{
		for (int i = 0; i < carrito.productos.unidades; i++)
		{
			cout << carrito.productos.productoseleccionado[i].codigo << "  " << carrito.productos.productoseleccionado[i].nombreproducto << "  " << carrito.productos.productoseleccionado[i].precio << endl;
		}
	}
}
int menu(tProductos producto, tCarrito carrito) {
	int opcion=1;
	while (opcion!=0)
	{
		cout << "1.Aniadir al carrito"<< endl;
		cout << "2.Eliminar del carrito"<<endl;
		cout << "3.Efectuar pedido y terminar"<<endl;
		cin >> opcion;
		if (opcion == 1) {
			elegirItem(producto, carrito);
		}
		if (opcion == 2) {
			eliminarItem(producto, carrito);
		}
		if (opcion == 3) {
			generarFactura(carrito);
			opcion = 0;
		}
	}
	

	return opcion;
}
void eliminarItem(tProductos& productos, tCarrito& carrito) {

}
#include "Numeros_del_rey.h"
#include "Busqueda.h"
#include <iostream>
int main()
{
	Busqueda p;
	Nodo_agenda nodo_encontrado; 
	nodo_encontrado.posicion = -1; 
	int num = 32;
	if (p.busqueda_A(num, nodo_encontrado)) {
		cout << "Numero a buscar: " << num<<endl; 
		p.devuelve_la_ruta_encontrada(nodo_encontrado.posicion);
	}
	else {
		cout << "No fue posible llegar a una solucion para: " << num; 
	}
	return 0; 
}
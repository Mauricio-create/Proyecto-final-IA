#include "Puzzle.h"
#include "Busqueda.h"
#include <ctime>
int main() {
	Busqueda p;
	Nodo_agenda nodo_encontrado;
	nodo_encontrado.posicion = -1; 
	string camino;
	unsigned int t0, t1;
	t0 = clock();
	p.busqueda_A(nodo_encontrado, 16);
	t1 = clock();
	double time = double(t1 - t0) / CLOCKS_PER_SEC;
	p.devuelve_la_ruta_encontrada(nodo_encontrado.posicion);
	cout << endl << "Tiempo de ejecucion: " << time << "seg" << endl;
	cout << camino;
}
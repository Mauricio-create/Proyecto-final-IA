#include "Busqueda.h"
#include <stdio.h>
#include <iostream>
//Elaborar con el codigo proporcionado, con busqueda a lo ancho, un nuevo algoritmo, tinmarin con la siguiente, cuando inserta 
//en la parte de adelante, y el siguiente hijo en la parte de atrás

//Se extrae de la agena con la posicion media

//Algoritmo basado en k bins donde el tamaño k no es parametro, si no que cambia aleatoriamente en cada ciclo de busqueda
//Meno tamaño_agenda

//Algoritmo de branch and bound que una vez expanda el mejor y otra el peor

//Hacer que el grafo sea dirigido

//Busqueda bidireccional con ascenso a la colina y primero mejor

using namespace std;

int main(void)
{
	Busqueda p;
	string camino = "";
	int NodoEncontrado = -1;
	int NodoEncontradoInicio = -1;
	int NodoEncontradoFinal = -1;
	if (p.lee_grafo("Mexico_USA_Corregido.csv"))
	{
		if (p.busqueda_A_estrella("Matamoros", "Cisco", NodoEncontrado))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por A estrella: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por A estrella\n");
	}
}
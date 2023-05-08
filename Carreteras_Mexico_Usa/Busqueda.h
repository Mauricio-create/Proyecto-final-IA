#pragma once

#include <string>
#include <vector>
#include <stddef.h>

using namespace std;

struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";
	float costo_acumulado = 0.0f;
	float costo_estimado = 0.0f;
};

struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido;
	int padre = -1;
	unsigned int profundidad = 0;
	vector<unsigned int> hijos;
};

struct tipo_enlace_de_grafo
{
	string nodo_1 = "";
	float costo_nodo_1 = 0.0f;
	string nodo_2 = "";
	float costo_nodo_2 = 0.0f;
	float costo_del_enlace = 0.0f;
	float posicion_x_nodo_1 = 0.0f;
	float posicion_y_nodo_1 = 0.0f;
	float posicion_x_nodo_2 = 0.0f;
	float posicion_y_nodo_2 = 0.0f;
};

class Busqueda
{
public:
	Busqueda();
	~Busqueda();
	bool lee_grafo(string archivo);
	bool busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado);
	string devuelve_la_ruta_encontrada(int nodo_encontrado) const;


private:
	vector<tipo_enlace_de_grafo> grafo;
	vector<tipo_nodo_del_arbol> arbol_de_busqueda;
	vector<unsigned int> Agenda;
	vector<tipo_nodo_del_arbol> arbol_de_busqueda_desde_el_inicio;
	vector<unsigned int> Agenda_desde_el_inicio;
	vector<tipo_nodo_del_arbol> arbol_de_busqueda_desde_el_final;
	vector<unsigned int> Agenda_desde_el_final;

	float calcula_heuristica_a_la_meta(string nodo_actual, string meta) const;
	void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
	bool devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, vector<tipo_nodo_del_arbol> arbol_creado,
		int nodo_padre, tipo_nodo_informacion& informacion) const;
	void crea_arbol(tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol_creado);
	void agrega_hijo_a_un_nodo(vector<tipo_nodo_del_arbol>& arbol, int padre, tipo_nodo_informacion contenido);
	bool esta_un_nodo_en_ancestros(vector<tipo_nodo_del_arbol> arbol, const int nodo_origen, string nombre_del_nodo) const;
	bool existe_un_nodo_comun_en_las_agendas(vector<unsigned int> agenda_1, vector<unsigned int> agenda_2,
		int& nodo_comun_inicio, int& nodo_comun_final) const;
	void devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
};


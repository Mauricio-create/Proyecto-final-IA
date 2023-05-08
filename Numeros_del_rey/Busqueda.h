#pragma once
#include<string>
#include<vector>
#include <queue>
using namespace std;


struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";
	float costo_acumulado = 0.0f;
};

struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido;
	int padre = -1;
	unsigned int profundidad = 0;
	vector<unsigned int> hijos;
};

struct Nodo_agenda {
	int posicion;
	double costo;
};

struct ComparadorNodos {
	bool operator()(const Nodo_agenda& n1, const Nodo_agenda& n2) const {
		return n1.costo > n2.costo; // ordena por costo ascendente
	}
};


class Busqueda
{
public:
	Busqueda();
	~Busqueda();
	bool busqueda_A(int num_final, Nodo_agenda& nodo_encontrado);
	void devuelve_la_ruta_encontrada(int nodo_encontrado) const;
private:
	void crea_arbol(tipo_nodo_informacion contenido);
	void agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
	bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;
	bool esta_un_nodo_en_ancestros_prueba(const int nodo_origen, string nombre_del_nodo) const;
	vector<tipo_nodo_del_arbol>arbol_de_busqueda;
	priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> agenda;
};






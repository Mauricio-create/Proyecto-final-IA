#include "Numeros_del_rey.h"
#include "Busqueda.h"
#include <iostream>
#include <time.h>
using namespace std; 
Numeros_del_rey::Numeros_del_rey()
{

}
Numeros_del_rey::~Numeros_del_rey()
{

}
void Numeros_del_rey::mostrar_numeros()const
{
	for (char c : numeros)
		cout << c; 
	cout << endl;
}
vector<string> Numeros_del_rey::posibles_movimientos(int pos)const
{
	string temp;
	vector<string>posibles_mov;
	if (pos == 0)
	{
		int j = 0;
		//suma
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];
			else
				temp += "+";
		posibles_mov.push_back(temp);
		temp = "";

		j = 0;
		//resta
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];
			else
				temp += "-";
		posibles_mov.push_back(temp);
		temp = "";

		j = 0; 
		//multiplicacion
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];
			else
				temp += "*";
		posibles_mov.push_back(temp);
		temp = "";

		j = 0;
		//division
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];
			else
				temp += "/";
		posibles_mov.push_back(temp);
		temp = "";
	}
	else {
		vector<char>operaciones = { '+', '-', '*', '/'};
		vector<int>posiciones = { 1,3,5,7,9,11,13,15 };
		srand(time(NULL));
		for (unsigned int i = 0; i < 6; i++) {
			bool isIn = false;
			temp = numeros; 
			temp[posiciones[rand() % posiciones.size()]] = operaciones[rand() % operaciones.size()];
			for (string c : posibles_mov)
				if (c == temp)
					isIn = true;
			if(!isIn)
				posibles_mov.push_back(temp);
		}
	}
	
	return posibles_mov; 
}
void Numeros_del_rey::actualizar_numeros(string actualizar)
{
	numeros = actualizar; 
}
void Numeros_del_rey::crear_numeros()
{
	for (unsigned int i = 1; i <= 9; i++)
		numeros += to_string(i);
}
float Numeros_del_rey::evaluar_numeros(const string num)
{
	long long int suma = int(num[0]-48);
	char operacion = '0';
	for (unsigned int i = 0; i < num.size(); i++)
	{
		if (i % 2 == 0)
		{
			switch(operacion)
			{
				case '+':
					suma += int(num[i] - 48);
					break; 

				case '-':
					suma -= int(num[i] - 48);
					break;

				case '*':
					suma *= int(num[i] - 48);
					break;

				case '/':
					suma /= int(num[i] - 48);
					break;
				default:
					break;
			}
		}
		else {
			operacion = num[i];
		}
	}
	return suma; 
}

int Numeros_del_rey::heuristica(const string num, int final)
{
	int num_evaluar = evaluar_numeros(num);
	return abs(final - num_evaluar);
}

string Numeros_del_rey::devolver_nodo_actual()
{
	return numeros; 
}

Busqueda::Busqueda() {

}

//Destructor
Busqueda::~Busqueda() {

}

void Busqueda::crea_arbol(tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal;
	temporal.padre = -1;
	temporal.profundidad = 0;
	temporal.contenido = contenido;
	temporal.hijos.clear();
	arbol_de_busqueda.push_back(temporal);
}
void Busqueda::agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal;
	temporal.padre = padre;
	temporal.profundidad = arbol_de_busqueda[padre].profundidad + 1;
	temporal.contenido = contenido;
	temporal.hijos.clear();
	arbol_de_busqueda.push_back(temporal);
	arbol_de_busqueda[padre].hijos.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
}

bool Busqueda::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
	int temporal = arbol_de_busqueda[nodo_origen].padre;
	while (temporal != -1)
	{
		if (arbol_de_busqueda[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
			return true;
		temporal = arbol_de_busqueda[temporal].padre;
	}
	return false;
}
bool Busqueda::esta_un_nodo_en_ancestros_prueba(const int nodo_origen, string nombre_del_nodo) const
{
	for (unsigned int i = 0; i < nodo_origen; i++) {
		if (arbol_de_busqueda[i].contenido.nombre_del_nodo == nombre_del_nodo)
			return true;
	}
	return false;
}
bool Busqueda::busqueda_A(int num_final, Nodo_agenda& nodo_encontrado)
{
	Numeros_del_rey p; 
	p.crear_numeros();
	tipo_nodo_informacion informacion_del_nodo_inicio;
	tipo_nodo_informacion informacion_del_hijo_a_adicionar;
	Nodo_agenda nodo_actual;
	vector<string> vecinos;
	informacion_del_nodo_inicio.nombre_del_nodo = p.devolver_nodo_actual();
	crea_arbol(informacion_del_nodo_inicio);
	agenda.push({ 0,0 });
	int contador = 0; 
	while (!agenda.empty())
	{
		if (agenda.size() > 2000)
		{
			priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> help;
			for (unsigned int i = 0; i <= 2000; i++)
			{
				Nodo_agenda temp = agenda.top();
				agenda.pop();
				help.push(temp);
			}
			while (!agenda.empty()) {
				agenda.pop();
			}
			agenda = help;
		}
		nodo_actual = agenda.top();
		if (contador != 0)
		{
			tipo_nodo_del_arbol nodo;
			nodo = arbol_de_busqueda[nodo_actual.posicion];
			string cadena = nodo.contenido.nombre_del_nodo;

			// Crear un vector de caracteres y guardar cada caracter en el vector
			p.actualizar_numeros(cadena);
		}
		agenda.pop();
		float suma_final = p.evaluar_numeros(arbol_de_busqueda[nodo_actual.posicion].contenido.nombre_del_nodo);
		if (suma_final == num_final)
		{
			nodo_encontrado = nodo_actual;
			return true;
		}
		vecinos = p.posibles_movimientos(nodo_actual.posicion);
		for (unsigned int i = 0; i < vecinos.size(); i++)
			if (esta_un_nodo_en_ancestros(nodo_actual.posicion, vecinos[i]))
			{
				vecinos.erase(vecinos.begin() + i);
				i--;
			}
		for (unsigned int i = 0; i < vecinos.size(); i++)
		{
			informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i];
			informacion_del_hijo_a_adicionar.costo_acumulado = p.heuristica(vecinos[i], num_final);
			agrega_hijo_a_un_nodo(nodo_actual.posicion, informacion_del_hijo_a_adicionar);
			agenda.push({ int(arbol_de_busqueda.size() - 1) ,informacion_del_hijo_a_adicionar.costo_acumulado });
			if (informacion_del_hijo_a_adicionar.costo_acumulado == 0) {
				nodo_encontrado.posicion = int(arbol_de_busqueda.size() - 1);
				return true; 
			}
			contador++;
		}
		if (contador == 60000)
			return false; 
	}

	return false; 
}

void Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
	tipo_nodo_del_arbol camino = arbol_de_busqueda[nodo_encontrado];
	for (char c : camino.contenido.nombre_del_nodo)
	{
		cout << c << " ";
	}
}

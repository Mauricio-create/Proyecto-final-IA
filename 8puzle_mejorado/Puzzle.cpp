#include "Busqueda.h"
#include "Puzzle.h"
#include <unordered_map>
#include<iostream>
#pragma warning(disable : 6011)


float heuristica(const string& state) {
	int n = (int)sqrt(state.size());
	float dist = 0;

	for (int i = 0; i < (int)state.size(); i++) {
		if (state[i] != '0') {
			int currentRow = i / n;
			int currentCol = i % n;
			int targetRow, targetCol;
			int weight = 1; // peso adicional

			// obtiene la posicion objetivo de la ficha y ajusta el peso si es necesario
			if (state[i] >= '1' && state[i] <= '9') {
				targetRow = (state[i] - '1') / n;
				targetCol = (state[i] - '1') % n;
				if (currentRow != targetRow || currentCol != targetCol) {
					weight = 2;
				}
			}
			else {
				targetRow = (state[i] - 'A' + 9) / n;
				targetCol = (state[i] - 'A' + 9) % n;
				if (currentRow != targetRow || currentCol != targetCol) {
					weight = 2;
				}
			}

			int dx = currentCol - targetCol;
			int dy = currentRow - targetRow;
			dist += float(weight * sqrt(dx * dx + dy * dy));
		}
	}

	return dist;
}


//Funciones del puzzle
//Constructor
Puzzle::Puzzle()
{
	puzzle.clear();
	size_puzzle = 0;
}

//Destructor
Puzzle::~Puzzle()
{
}

//Devuelve si es posible la combinacion actual
bool Puzzle::posible()const
{
	unordered_map<char, int> mp;
	int inversiones = 0;
	string cadena = "";
	for (string c : puzzle)
	{
		cadena += c;
	}
	for (unsigned int i = 0; i < (unsigned int)cadena.size(); i++)
	{
		if (cadena[i] >= '0' && cadena[i] <= 'Z')
		{
			if (mp.count(cadena[i]) == 0)
			{
				mp[cadena[i]] = i;
			}
		}
		else
		{
			// La cadena de entrada contiene caracteres inválidos, lo cual no es válido.
			return false;
		}
	}

	// Se calcula el numero de inversiones.
	for (unsigned int i = 0; i < (unsigned int)cadena.size(); i++)
	{
		if (cadena[i] == '0')
		{
			continue;
		}
		for (unsigned int j = i + 1; j < cadena.size(); j++)
		{
			if (cadena[j] == '0')
			{
				continue;
			}
			if (mp[cadena[i]] > mp[cadena[j]])
			{
				inversiones++;
			}
		}
	}

	// Si el número de inversiones es par, la configuración es alcanzable.
	return (inversiones % 2 == 0);
}

//Revuelve el puzzle 
void Puzzle::shuffle()
{
	bool isPosible = posible();
	do {
		int raiz = (int)pow(puzzle.size(), 0.5);
		string ayuda = "";
		srand((unsigned int)time(NULL));

		for (unsigned int i = 0; i < size_puzzle; i++)
		{
			unsigned int aleatorio = rand() % size_puzzle;
			ayuda = puzzle.at(aleatorio);
			puzzle.erase(puzzle.begin() + aleatorio);
			aleatorio = rand() % size_puzzle;
			puzzle.insert(puzzle.begin() + aleatorio, ayuda);
		}
		isPosible = posible();
	} while (!isPosible);
}

//Print del puzzle actual 
void Puzzle::mostrar_puzzle()const
{
	int raiz = (int)pow(size_puzzle, 0.5);
	for (unsigned int i = 0; i < size_puzzle; i++)
	{
		if (i % raiz == 0) {
			cout << "\n";
			cout << puzzle.at(i);
		}
		else
			cout << puzzle.at(i);
	}
	cout << "\n";

}

//Devuelve vector con strings de los posibles movimientos(vecinos)
vector<string> Puzzle::posibles_movimientos(int num_linea, int raiz, int num_caracteres)const
{
	vector<string>posibles_movimientos;
	vector<string>puzzle_temporal;
	vector<float>heuristicas;
	float heuristica_temporal = 0.0;
	string temporal;
	string cadena_de_movimentos = "";
	int contador_de_ceros = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < (int)puzzle.size(); i++) {
		puzzle_temporal = puzzle;
		//Mov derecha
		if (((i + 1) % raiz) != 0 && i + 1 != size_puzzle)
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i + 1) != "0") {
				temporal = puzzle_temporal.at(i + 1);
				puzzle_temporal.erase(puzzle_temporal.begin() + i + 1);
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal);
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);
				posibles_movimientos.push_back(cadena_de_movimentos);
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}
		//Mov izquierda
		if (i != raiz && ((i) % raiz) != 0 && (i - 1) != -1)
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i - 1) != "0") {
				temporal = puzzle_temporal.at(i - 1);
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - 1));
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal);
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);
				posibles_movimientos.push_back(cadena_de_movimentos);
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}
		//Mov abajo
		if (i + raiz < (int)size_puzzle)
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i + raiz) != "0") {
				temporal = puzzle_temporal.at(i + raiz);
				puzzle_temporal.erase(puzzle_temporal.begin() + (i + raiz));
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal);
				temporal = puzzle_temporal.at(i + 1);
				puzzle_temporal.erase(puzzle_temporal.begin() + (i + 1));
				puzzle_temporal.insert(puzzle_temporal.begin() + (i + raiz), temporal);
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);
				posibles_movimientos.push_back(cadena_de_movimentos);
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}
		//Mov arriba
		if (i - raiz >= 0 && i - 1 != -1)
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i - raiz) != "0") {
				temporal = puzzle_temporal.at(i - raiz);
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - raiz));
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal);
				temporal = puzzle_temporal.at(i - 1);
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - 1));
				puzzle_temporal.insert(puzzle_temporal.begin() + (i - raiz), temporal);
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);
				posibles_movimientos.push_back(cadena_de_movimentos);
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}

	}
	return posibles_movimientos;
}


//Crea un puzzle de tamaño n
void Puzzle::crear_puzzle(unsigned int n) {
	size_puzzle = n;

	if (size_puzzle <= 9) {
		for (unsigned int i = 1; i <= size_puzzle; i++)
		{
			if (i < n)
				puzzle.push_back(to_string(i));
			else
				puzzle.push_back("0");
		}
	}
	else {
		string abecedario[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"
		,"T", "U", "V", "W", "X", "Y", "Z" };
		for (unsigned int i = 1; i < size_puzzle - 1; i++)
		{
			if (i <= 9)
				puzzle.push_back(to_string(i));
			else
				puzzle.push_back(abecedario[i - 10]);
		}
		puzzle.push_back("0");
		puzzle.push_back("0");

	}
}

//devuelve una cadena de caracteres de lo que hay en el puzzle
string Puzzle::primer_elemento()const
{
	string puzzle_actual = "";
	if (puzzle.size())
		for (string c: puzzle)
			puzzle_actual += c;
	return puzzle_actual;
}

//Actualiza el puzzle, esto se hara cada iteracion de busqueda
void Puzzle::actualizar_puzzle(vector<string> actualizar)
{
	puzzle = actualizar;
}


//Comrpueba si una linea del puzzle ya esta formada
bool Puzzle::revisar_linea(string cadena, int num_lineas, int raiz)const
{
	string abecedario[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"
		,"T", "U", "V", "W", "X", "Y", "Z" };
	int size = num_lineas * raiz;
	string cadena_ayuda = "";
	for (unsigned int i = 1; i <= (unsigned int)size; i++) {
		if (i <= 9)
			cadena_ayuda += to_string(i);
		else
			cadena += abecedario[i - 10];
	}
	string verificar = cadena.substr(0, size);
	return verificar == cadena_ayuda;
}


//Comprueba si n numero de caracteres ya estan en su lugar 
bool Puzzle::revisar_caracter(string cadena, int num_caracteres)const
{
	string abecedario[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"
		,"T", "U", "V", "W", "X", "Y", "Z" };
	int size = num_caracteres;
	string cadena_ayuda = "";
	for (unsigned int i = 1; i <= (unsigned int)size; i++) {
		if (i <= 9)
			cadena_ayuda += to_string(i);
		else
			cadena += abecedario[i - 10];
	}
	string verificar = cadena.substr(0, size);
	return verificar == cadena_ayuda;
}

//Devuelve el size de las filas y de las columnas que hay 
float Puzzle::raiz()const
{
	return (float)pow(size_puzzle, 0.5);
}

//Funciones de busqueda

//Constructor
Busqueda::Busqueda(){
	
}

//Destructor
Busqueda::~Busqueda(){

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
	for (unsigned int i = 0; i < (unsigned int)nodo_origen; i++) {
		if (arbol_de_busqueda[i].contenido.nombre_del_nodo == nombre_del_nodo)
			return true;
	}
	return false;
}


bool Busqueda::busqueda_A(Nodo_agenda& nodo_encontrado, int n)
{
	cout << "Rompe cabezas desarmado: " << endl;
	Puzzle p;
	p.crear_puzzle(n);
	p.shuffle();
	p.mostrar_puzzle();
	cout << endl << "Resolviendo rompecabezas ";
	int raiz = (int)p.raiz();
	tipo_nodo_informacion informacion_del_nodo_inicio;
	tipo_nodo_informacion informacion_del_hijo_a_adicionar;
	Nodo_agenda nodo_actual;
	vector<string> vecinos;
	unsigned int tamaño_agenda = 0;
	unsigned int tamaño_arbol = 0;
	informacion_del_nodo_inicio.nombre_del_nodo = p.primer_elemento();
	float costo_uno = heuristica(informacion_del_nodo_inicio.nombre_del_nodo);
	cout << "con una complejidad de " << costo_uno << ": " << endl;
	crea_arbol(informacion_del_nodo_inicio);
	agenda.push({ 0,0 });
	int contador = 0, contador2 = 0;
	int num_lineas = 1;
	int num_caracteres = 1;
	float costo_control = -1;

	while (!agenda.empty())
	{
		if (agenda.size() > 50)
		{
			priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> help;
			for (unsigned int i = 0; i <= 5; i++)
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
		if (contador != 0) {
			tipo_nodo_del_arbol nodo;
			nodo = arbol_de_busqueda[nodo_actual.posicion];
			string cadena = nodo.contenido.nombre_del_nodo;

			// Crear un vector de caracteres y guardar cada caracter en el vector
			vector<string> caracteres;
			for (char c : cadena) {
				caracteres.push_back(string(1, c));
			}
			p.actualizar_puzzle(caracteres);
		}
		tipo_nodo_del_arbol nodo_a_buscar;
		nodo_a_buscar = arbol_de_busqueda[nodo_actual.posicion];
		if (p.revisar_linea(nodo_a_buscar.contenido.nombre_del_nodo, num_lineas, raiz))
		{
			if (contador2 == 0) {
				vecinos.clear();
				vector<string> caracteres_ayuda;
				for (char c : nodo_a_buscar.contenido.nombre_del_nodo) {
					caracteres_ayuda.push_back(string(1, c));
				}
				contador2 += 1;
				p.actualizar_puzzle(caracteres_ayuda);
			}
			num_lineas += 1;
			nodo_encontrado = nodo_actual;
		}
		agenda.pop();
		tipo_nodo_del_arbol temporal;
		temporal = arbol_de_busqueda[nodo_actual.posicion];

		vecinos = p.posibles_movimientos(num_lineas, raiz, num_caracteres);

		for (unsigned int i = 0; i < (unsigned int)vecinos.size(); i++)
			if (esta_un_nodo_en_ancestros_prueba(nodo_actual.posicion, vecinos[i]))
			{
				vecinos.erase(vecinos.begin() + i);
				i--;
			}
		for (unsigned int i = 0; i < (unsigned int)vecinos.size(); i++)
		{
			if (nodo_encontrado.posicion == -1) {
				informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos.at(i);
				informacion_del_hijo_a_adicionar.costo_acumulado = heuristica(informacion_del_hijo_a_adicionar.nombre_del_nodo);
				agrega_hijo_a_un_nodo(nodo_actual.posicion,
					informacion_del_hijo_a_adicionar);
				agenda.push({ int(arbol_de_busqueda.size()-1), informacion_del_hijo_a_adicionar.costo_acumulado });
				contador += 1;
				if (p.revisar_caracter(informacion_del_hijo_a_adicionar.nombre_del_nodo, num_caracteres) && num_caracteres % raiz != 0) {
					if (agenda.size() > 3) {
						tipo_nodo_del_arbol nodo_temporal;
						Nodo_agenda posicion_actual1 = agenda.top();
						agenda.pop();
						Nodo_agenda posicion_actual2 = agenda.top();
						agenda.pop();
						Nodo_agenda posicion_actual3 = agenda.top();
						agenda.pop();
						while (!agenda.empty()) {
							agenda.pop();
						}
						agenda.push(posicion_actual1);
						agenda.push(posicion_actual2);
						agenda.push(posicion_actual3);
						num_caracteres += 1;
					}
						cout << endl << "---Nodo en su posicion---" << endl;
				}
			}
			else {
				informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos.at(i);
				informacion_del_hijo_a_adicionar.costo_acumulado = heuristica(informacion_del_hijo_a_adicionar.nombre_del_nodo);
				int lineas_limites = num_lineas - 1;
				if (costo_control == -1 && informacion_del_hijo_a_adicionar.costo_acumulado < 10 && informacion_del_hijo_a_adicionar.costo_acumulado > 7)
					costo_control = informacion_del_hijo_a_adicionar.costo_acumulado;
				if (p.revisar_linea(informacion_del_hijo_a_adicionar.nombre_del_nodo, lineas_limites, raiz)) {
					
					costo_control = informacion_del_hijo_a_adicionar.costo_acumulado;
					agrega_hijo_a_un_nodo(nodo_actual.posicion,
						informacion_del_hijo_a_adicionar);
					agenda.push({ int(arbol_de_busqueda.size() - 1), informacion_del_hijo_a_adicionar.costo_acumulado });
					contador += 1;
					contador2 += 1;
					if (costo_control == 0)
					{
						nodo_encontrado.posicion = arbol_de_busqueda.size() - 1;
						return true;
					}
				}
				if (p.revisar_caracter(informacion_del_hijo_a_adicionar.nombre_del_nodo, num_caracteres) && num_caracteres % raiz != 0) {
					if (agenda.size() > 3) {
						tipo_nodo_del_arbol nodo_temporal;
						Nodo_agenda posicion_actual1 = agenda.top();
						agenda.pop();
						Nodo_agenda posicion_actual2 = agenda.top();
						agenda.pop();
						Nodo_agenda posicion_actual3 = agenda.top();
						agenda.pop();
						while (!agenda.empty()) {
							agenda.pop();
						}
						agenda.push(posicion_actual1);
						agenda.push(posicion_actual2);
						agenda.push(posicion_actual3);
						num_caracteres += 1;
					}
						cout << endl << "---Nodo en su posicion---" << endl;
				}
			}
		}
		p.mostrar_puzzle();
	}
	return false;
}


void Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
	vector<unsigned int> vector_temporal;
	string camino = "";
	vector_temporal.clear();
	tipo_nodo_del_arbol temporal;
	cout << endl << "---------------------------Los movimientos utilizados son: ----------------------------------------" << endl;
	while (nodo_encontrado != -1)
	{
		vector_temporal.insert(vector_temporal.begin(), nodo_encontrado);
		temporal = arbol_de_busqueda[nodo_encontrado];
		nodo_encontrado = temporal.padre;
	}
	int contador = 0;
	int raiz = (int)pow(temporal.contenido.nombre_del_nodo.size(), 0.5);
	for (unsigned int i : vector_temporal) {
		temporal = arbol_de_busqueda[i];
		for (char c : temporal.contenido.nombre_del_nodo)
		{
			contador += 1;
			if (contador % raiz == 0)
			{
				cout << c << " ";
				cout << endl;
			}
			else
				cout << c << " ";
		}
		cout << endl;
		cout << endl;
		contador = 0;
	}

	cout << endl << "Movimientos utilizados: " << vector_temporal.size() << endl; 
}



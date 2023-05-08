#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Puzzle {
public:
	Puzzle();
	~Puzzle();
	void shuffle();
	bool posible()const;
	void mostrar_puzzle()const;
	void crear_puzzle(unsigned int n);
	vector<string> posibles_movimientos(int num_linea, int raiz, int num_caracteres)const;
	string primer_elemento()const;
	bool revisar_linea(string cadena, int num_lineas, int raiz)const;
	bool revisar_caracter(string cadena, int num_caracteres)const;
	void actualizar_puzzle(vector<string> actualizar);
	float raiz()const;
private:
	vector<string>puzzle;
	unsigned int size_puzzle;
};
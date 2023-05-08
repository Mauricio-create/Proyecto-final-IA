#pragma once
#include<string>
#include<vector>
using namespace std;

class Numeros_del_rey
{
public:
	Numeros_del_rey();
	~Numeros_del_rey();
	void mostrar_numeros()const;
	vector<string> posibles_movimientos(int pos)const;
	void actualizar_numeros(string actualizar);
	void crear_numeros();
	float evaluar_numeros(const string num);
	int heuristica(const string num, int final);
	string devolver_nodo_actual();

private:
	string numeros; 
};






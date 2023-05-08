#include "Busqueda.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <stddef.h>
#include <cmath>
#include <time.h>

using namespace std;

#pragma warning(disable : 6011)

Busqueda::Busqueda()
{
    grafo.clear();
    arbol_de_busqueda.clear();
}

Busqueda::~Busqueda()
{

}

bool Busqueda::lee_grafo(string archivo)
{
    string leida;
    tipo_enlace_de_grafo enlace;
    fstream newfile;
    vector<string> vector_de_cadenas;
    grafo.clear();
    newfile.open(archivo, ios::in);
    if (newfile.is_open())
    {
        getline(newfile, leida);
        while (getline(newfile, leida))
        {
            vector_de_cadenas.clear();
            stringstream cadena(leida);
            string temporal;
            while (getline(cadena, temporal, ','))
                vector_de_cadenas.push_back(temporal);
            enlace.nodo_1 = vector_de_cadenas[0];
            enlace.costo_nodo_1 = (float)atof(vector_de_cadenas[1].c_str());
            enlace.posicion_x_nodo_1 = (float)atof(vector_de_cadenas[2].c_str());
            enlace.posicion_y_nodo_1 = (float)atof(vector_de_cadenas[3].c_str());
            enlace.nodo_2 = vector_de_cadenas[4];
            enlace.costo_nodo_2 = (float)atof(vector_de_cadenas[5].c_str());
            enlace.posicion_x_nodo_2 = (float)atof(vector_de_cadenas[6].c_str());
            enlace.posicion_y_nodo_2 = (float)atof(vector_de_cadenas[7].c_str());
            enlace.costo_del_enlace = (float)atof(vector_de_cadenas[8].c_str());
            grafo.push_back(enlace);
        }
        newfile.close();
        return true;
    }
    else
        return false;
}
void Busqueda::devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);
}

void Busqueda::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    unsigned int posicion_a_empezar;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo) {
            vecinos.push_back(grafo[i]);

        }
        else if (grafo[i].nodo_2 == nodo)
        {
            temporal.nodo_1 = grafo[i].nodo_2;
            temporal.costo_nodo_1 = grafo[i].costo_nodo_2;
            temporal.posicion_x_nodo_1 = grafo[i].posicion_x_nodo_2;
            temporal.posicion_y_nodo_1 = grafo[i].posicion_y_nodo_2;
            temporal.nodo_2 = grafo[i].nodo_1;
            temporal.costo_nodo_2 = grafo[i].costo_nodo_1;
            temporal.posicion_x_nodo_2 = grafo[i].posicion_x_nodo_1;
            temporal.posicion_y_nodo_2 = grafo[i].posicion_y_nodo_1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }

}

bool Busqueda::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, vector<tipo_nodo_del_arbol> arbol,
    int nodo_padre, tipo_nodo_informacion& informacion) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1)
    {
        costo_acumulado_del_padre = arbol[nodo_padre].contenido.costo_acumulado;
        nombre_del_nodo_padre = arbol[nodo_padre].contenido.nombre_del_nodo;
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo &&
                grafo[i].nodo_2 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo &&
                grafo[i].nodo_1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        return false;
    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}

void Busqueda::crea_arbol(tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol_creado)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.profundidad = 0;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_creado.clear();
    arbol_creado.push_back(temporal);
}

void Busqueda::agrega_hijo_a_un_nodo(vector<tipo_nodo_del_arbol>& arbol, int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.profundidad = arbol[padre].profundidad + 1;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol.push_back(temporal);
    arbol[padre].hijos.push_back((unsigned int)(arbol.size() - 1));
}

bool Busqueda::esta_un_nodo_en_ancestros(vector<tipo_nodo_del_arbol> arbol, const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol[temporal].padre;
    }
    return false;
}

string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        camino = camino + " - " + arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo;
    camino += " Costo acumulado: " + to_string(arbol_de_busqueda.at(arbol_de_busqueda.size() - 1).contenido.costo_acumulado);
    //camino.erase(camino.begin(), camino.begin() + 3);
    return camino;
}


float Busqueda::calcula_heuristica_a_la_meta(string nodo_actual, string meta) const
{
    float calculo = 0.0f;
    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_1;
            y1 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_2;
            y1 = grafo[i].posicion_y_nodo_2;
            break;
        }
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_1;
            y2 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_2;
            y2 = grafo[i].posicion_y_nodo_2;
            break;
        }
    calculo = (float)pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
    return calculo;
}

bool Busqueda::busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    arbol_de_busqueda[0].contenido.costo_estimado = calcula_heuristica_a_la_meta(nodo_inicio, nodo_final);
    Agenda.clear();
    Agenda.push_back(0);
    while (!Agenda.empty())
    {
        mejor_nodo = Agenda[0];
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
            arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado +
                    arbol_de_busqueda[Agenda[i]].contenido.costo_estimado))
            {
                mejor_nodo = Agenda[i];
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
                    arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
            }
        Agenda.erase(Agenda.begin() + posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                arbol_de_busqueda[Agenda[mejor_nodo]].contenido.costo_acumulado)
                meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < Agenda.size(); i++)
                if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    Agenda.erase(Agenda.begin() + i);
                    i--;
                }
            if (Agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
        devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, mejor_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(vecinos[i].nodo_2,
                nodo_final);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, mejor_nodo, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
    }
    nodo_encontrado = meta_temporal;
    return meta_temporal != -1;
}



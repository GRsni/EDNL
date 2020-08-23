#ifndef LABERINTO
#define LABERINTO

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"

struct Casilla
{
    int fila, columna;
};

typedef int tCoste;

struct Pared
{
    Casilla casilla1;
    Casilla casilla2;
};

/*
template <>
ostream &operator<<<size_t>(ostream &os, const Lista<size_t> &L)
{
    typedef Lista<Grafo::vertice>::posicion posicion;
    for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
        os << L.elemento(i) << ' ';
    return os;
}
*/
bool casillas_adyacentes(Casilla &c1, Casilla &c2)
{
    int difFila = abs(c1.fila - c2.fila);
    int difColumna = abs(c1.columna - c2.columna);

    //La casillas son adyancentes si estan en la misma columna, y filas adyacentes
    //o en la misma fila y columnas adyacentes
    return ((difColumna == 0 && difFila == 1) || (difColumna == 1 && difFila == 0));
}

/**********
 * Calcula el nodo del grado de conexiones a partir de la columna
 * y fila de la casilla
 */
GrafoP<tCoste>::vertice casilla_to_nodo(int N, Casilla &c)
{
    return c.columna + c.fila * N;
}

/*****************
 * Calcula la casilla del laberinto a partir del nodo
 * y de la dimension del laberinto 
 */
Casilla nodo_to_casilla(int N, int nodo)
{
    Casilla c;
    c.columna = nodo / N;
    c.fila = nodo % N;
    return c;
}

/***
 * Inicializa la matriz de costes directos, poniendo a 0 los costes de
 * una casilla a si misma, y coste 1 en las casillas adyancentes
 */
template <typename tCoste>
void conectarCeldas(GrafoP<tCoste> &G)
{
    Casilla c1{}, c2{};

    for (int i = 0; i <= G.numVert() - 1; i++)
    {
        c1 = nodo_to_casilla(sqrt(G.numVert()), i);
        for (int j = i; j <= G.numVert() - 1; j++)
        {
            if (i == j)
            {
                G[i][j] = 0;
            }
            else
            {
                c2 = nodo_to_casilla(sqrt(G.numVert()), j);
                if (casillas_adyacentes(c1, c2))
                {
                    G[i][j] = 1;
                    G[j][i] = 1;
                }
            }
        }
    }
}

/*******
 * Coloca las paredes entre cada dos casillas del laberinto
 */
template <typename tCoste>
void poner_paredes(GrafoP<tCoste> &G, vector<Pared> &paredes)
{
    int dimLab = sqrt(G.numVert());
    for (Pared p : paredes)
    {
        typename GrafoP<tCoste>::vertice v1 = casilla_to_nodo(dimLab, p.casilla1);
        typename GrafoP<tCoste>::vertice v2 = casilla_to_nodo(dimLab, p.casilla2);

        std::cout << v1 << ", " << v2 << std::endl;
        G[v1][v2] = GrafoP<tCoste>::INFINITO;
        G[v2][v1] = GrafoP<tCoste>::INFINITO;
    }
}

/***
 * Devuelve el camino de coste minimo para llegar desde la casilla origen
 *  hasta la casilla destino de un laberinto de dimension N.
 * 
 */
template <typename tCoste>
typename GrafoP<tCoste>::tCamino
laberinto(int N, vector<Pared> &paredes, Casilla origen, Casilla destino)
{
    int numCasillas = N * N;
    GrafoP<tCoste> G(numCasillas);

    std::cout << G;

    conectarCeldas(G);

    std::cout << G;

    poner_paredes(G, paredes);

    std::cout << G;

    typename GrafoP<tCoste>::vertice nodoOrigen = casilla_to_nodo(G.numVert(), origen);
    typename GrafoP<tCoste>::vertice nodoDestino = casilla_to_nodo(G.numVert(), destino);

    vector<typename GrafoP<tCoste>::vertice> recorrido;

    vector<tCoste> costesMinimos = Dijkstra(G, nodoOrigen, recorrido);

    std::cout << "Costes minimos: "<<costesMinimos << std::endl;
    std::cout << "Recorrido: "<<recorrido << std::endl;

    return camino<tCoste>(nodoOrigen, nodoDestino, recorrido);
}

/***
 * Crea una pared a partir de la fila y columna de dos casillas
 */
Pared crear_pared(int fil1, int col1, int fil2, int col2)
{
    Casilla v1{fil1, col1};
    Casilla v2{fil2, col2};

    return Pared{v1, v2};
}

#endif

int main()
{
    int tam = 6;
    vector<Pared> paredes;
    Casilla origen{0, 0}, destino{0, tam - 1}, pared1, pared2;

    paredes.push_back(crear_pared(0, 0, 0, 1));
    paredes.push_back(crear_pared(1, 0, 1, 1));
    paredes.push_back(crear_pared(1, 1, 2, 1));
    paredes.push_back(crear_pared(0, 2, 1, 2));

    std::cout << laberinto<tCoste>(tam, paredes, origen, destino);
}
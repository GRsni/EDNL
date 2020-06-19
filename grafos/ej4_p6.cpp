#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef int tCoste;
typedef typename GrafoP<tCoste>::vertice vertice;

template <typename tCoste>
void distanciasZuelandia(GrafoP<tCoste> &G,
                         vector<bool> &ciudadesOcupadas,
                         vector<vector<bool>> &carreterasCortadas,
                         vertice &capital)
{
    int nCiud = G.numVert();

    std::cout << "inicial" << std::endl;
    std::cout << G << std::endl;

    //Se eliminan las ciudades ocupadas del grafo de costes directos
    for (int i = 0; i <= nCiud - 1; i++)
    {
        if (ciudadesOcupadas[i])
        {
            for (int j = 0; j <= nCiud - 1; j++)
            {
                //No se puede salir de la ciudad i
                G[i][j] = GrafoP<tCoste>::INFINITO;
                //No se puede llegar a la ciudad i
                G[j][i] = GrafoP<tCoste>::INFINITO;
            }
        }
    }

    //Se eliminan las carreteras ocupadas del grafo de costes directos
    for (int i = 0; i <= nCiud - 1; i++)
    {
        for (int j = 0; j <= nCiud - 1; j++)
        {
            if (carreterasCortadas[i][j])
            {
                G[i][j] = GrafoP<tCoste>::INFINITO;
            }
        }
    }

    std::cout << "Sin carreteras ni ciudades" << std::endl;
    std::cout << G << std::endl;

    vector<typename GrafoP<tCoste>::vertice> caminos{};
    vector<tCoste> llegarCapital = DijkstraInv(G, capital, caminos);
    vector<tCoste> salirCapital = Dijkstra(G, capital, caminos);

    for (int i = 0; i <= nCiud - 1; i++)
    {
        G[i][capital] = llegarCapital[i];
        G[capital][i] = salirCapital[i];
    }

    for (int i = 0; i <= nCiud - 1; i++)
    {
        for (int j = 0; j <= nCiud - 1; j++)
        {
            if (i != j)
            {
                G[i][j] = suma(G[i][capital], G[capital][j]);
            }
        }
    }
}

int main()
{
    srand(time(nullptr));

    int nCiud = 10;
    GrafoP<tCoste> ciudades(nCiud);
    vector<bool> ocupadas(nCiud, false);
    vector<vector<bool>> cortadas(nCiud, vector<bool>(nCiud, false));

    typename GrafoP<tCoste>::vertice capital = 1;

    for (int i = 0; i <= nCiud - 1; i++)
    {
        if (rand() < (RAND_MAX / 5) && i != capital)
        {
            ocupadas[i] = true;
        }
        for (int j = 0; j <= nCiud - 1; j++)
        {
            if (i == j)
            {
                ciudades[i][j] = 0;
            }
            else
            {
                ciudades[i][j] = rand() % 300;
            }
            if (rand() < (RAND_MAX / 5) && i != j)
            {
                cortadas[i][j] = true;
            }
        }
    }

    distanciasZuelandia(ciudades, ocupadas, cortadas, capital);

    std::cout << "Caminos finales:\n"
              << ciudades << std::endl;
}
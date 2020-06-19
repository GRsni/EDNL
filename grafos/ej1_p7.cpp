#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef float tCoste;

typedef typename GrafoP<tCoste>::vertice vertice;

struct Viaje
{
    tCoste precio;
    vertice origen;
    vertice destino;
};

template <typename tCoste>
matriz<tCoste> FloydMAX(const GrafoP<tCoste> &G)
{
    const size_t n = G.numVert();
    matriz<tCoste> A(n); // matriz de costes mínimos
    // Iniciar A con caminos directos entre cada par de vértices.
    for (vertice i = 0; i < n; i++)
    {
        A[i] = G[i]; // copia costes del grafo
        A[i][i] = 0; // diagonal a 0
    }
    // Calcular costes maximos entre vertices
    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++)
            {
                tCoste ikj = suma(A[i][k], A[k][j]);
                if (ikj != GrafoP<tCoste>::INFINITO)
                {
                    if (ikj > A[i][j] || A[i][j] == GrafoP<tCoste>::INFINITO)
                    {
                        A[i][j] = ikj;
                    }
                }
            }
    return A;
}

template <typename tCoste>
Viaje viaje_mas_caro(const GrafoP<tCoste> &G)
{
    Viaje v;
    int nCiud = G.numVert();
    tCoste coste = 0;

    matriz<tCoste> costesMaximos = FloydMAX(G);
    std::cout << costesMaximos << std::endl;

    for (int i = 0; i < nCiud; i++)
    {
        for (int j = 0; j < nCiud; j++)
        {
            if (costesMaximos[i][j] > v.precio)
            {
                v.precio = costesMaximos[i][j];
                v.origen = i;
                v.destino = j;
            }
        }
    }

    return v;
}

int main()
{

    GrafoP<tCoste> ciu3(3), ciu2(2);
    matriz<GrafoP<tCoste>::vertice> P;

    ciu3[0][0] = 0;
    ciu3[0][1] = 1;
    ciu3[0][2] = 1;
    ciu3[1][0] = GrafoP<tCoste>::INFINITO;
    ciu3[1][1] = 0;
    ciu3[1][2] = GrafoP<tCoste>::INFINITO;
    ciu3[2][0] = GrafoP<tCoste>::INFINITO;
    ciu3[2][1] = GrafoP<tCoste>::INFINITO;
    ciu3[2][2] = 0;

    std::cout << ciu3 << std::endl;
    Viaje v = viaje_mas_caro(ciu3);

    ciu2[0][0] = 0;
    ciu2[0][1] = 1;
    ciu2[1][0] = GrafoP<tCoste>::INFINITO;
    ciu2[1][1] = 0;

    std::cout << ciu2 << std::endl;
    v = viaje_mas_caro(ciu2);
}
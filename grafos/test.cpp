#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef float tCoste;
typedef typename GrafoP<tCoste>::vertice vertice;

int main()
{
    srand(time(nullptr));
    int average = 0;
    int tam = 100;
    int capacidad = 200;
    GrafoP<tCoste> mapa(tam);
    vector<vertice> vectorC;
    matriz<vertice> matrizC;

    for (int i = 0; i <= tam - 1; i++)
    {
        for (int j = 0; j <= tam - 1; j++)
        {
            if (i == j)
            {

                mapa[i][j] = 0;
            }
            else
            {
                mapa[i][j] = 1;
                //mapa[i][j] = rand() % 100;
            }
        }
    }
    for (int i = 0; i < 100; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < 100; j++)
        {
            vector<tCoste> costes = Dijkstra(mapa, 0, vectorC);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "en " << tiempo << " microsegundos." << std::endl;
        average += tiempo / 100;
    }
    std::cout << "Average time Dijkstra: " << average; //1796378 us

    for (int i = 0; i < 100; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        matriz<tCoste> costesM = Floyd(mapa, matrizC);
        auto end = std::chrono::high_resolution_clock::now();
        auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "en " << tiempo << " microsegundos." << std::endl;
        average += tiempo / 100;
    }
    std::cout << "Average time Floyd: " << average;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef float tCoste;
typedef typename GrafoP<tCoste>::vertice vertice;

int pedido()
{
    return rand() % 1;
}

vertice encontrar_siguiente(vector<tCoste> costes, vertice actual, vector<bool> servidos)
{
    tCoste coste_min = GrafoP<tCoste>::INFINITO;
    vertice sig = actual;

    for (int i = 0; i < costes.size(); i++)
    {
        if (i != actual && !servidos[i])
        {
            if (costes[i] < coste_min)
            {
                coste_min = costes[i];
                sig = i;
            }
        }
    }
    return sig;
}

float calcular_ruta(const GrafoP<tCoste> &G, int capacidad, vertice almacen)
{
    vector<int> pedidos(G.numVert(), 1);
    int cajas_actuales = capacidad;
    float dist_total = 0;
    vertice actual, cliente_sig;
    matriz<vertice> P;
    matriz<tCoste> costes = Floyd(G, P);

    int clientes_por_servir = G.numVert() - 1;
    vector<bool> clientes_servidos(G.numVert(), false);
    clientes_servidos[almacen] = true;
    pedidos[almacen] = 0;

    actual = almacen;

    while (clientes_por_servir > 0)
    {
        if (cajas_actuales > 0)
        {
            cliente_sig = encontrar_siguiente(costes[actual], actual, clientes_servidos);
            dist_total += costes[actual][cliente_sig];
            int ped = pedidos[cliente_sig];
            // std::cout << "Repartidas " << ped << " cajas a " << cliente_sig << std::endl;
            if (cajas_actuales >= ped)
            {
                // std::cout << "Repartidas " << ped << " cajas a " << cliente_sig << std::endl;
                pedidos[cliente_sig] = 0;
                cajas_actuales -= ped;
                clientes_servidos[cliente_sig] = true;
                clientes_por_servir--;
            }
            else
            {
                //  std::cout << "Repartidas " << cajas_actuales << " cajas a " << cliente_sig << std::endl;
                pedidos[cliente_sig] -= cajas_actuales;
                cajas_actuales = 0;
            }
            actual = cliente_sig;
        }
        else
        {
            // std::cout << "Vuelta al almacen." << std::endl;
            dist_total += costes[actual][almacen];
            cajas_actuales = capacidad;
            actual = almacen;
        }
    }
    if (actual != almacen)
    {
        dist_total += costes[actual][almacen];
    }
    return dist_total;
}

int main()
{
    srand(time(nullptr));
    int average = 0;
    int tam = 300;
    int capacidad = 200;
    GrafoP<tCoste> mapa(tam);

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
        //std::cout << mapa;
        std::cout << "Distancia : " << calcular_ruta(mapa, capacidad, 0);
        auto end = std::chrono::high_resolution_clock::now();
        auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "en " << tiempo << " microsegundos." << std::endl;
        average += tiempo / 100;
    }
    std::cout << "Average time: " << average;
}

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef float tCoste;

struct Ruta
{
    vector<int> cantidades;
    float costeTotal;
};

template <>
ostream &operator<<<size_t>(ostream &os, const Lista<size_t> &L)
{
    typedef Lista<Grafo::vertice>::posicion posicion;
    for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
        os << L.elemento(i) << ' ';
    return os;
}

int encontrar_menor(vector<tCoste> &costes, typename GrafoP<tCoste>::vertice origen)
{
    int indice = 0;
    tCoste min = std::numeric_limits<tCoste>::max();
    for (int i = 0; i <= costes.size() - 1; i++)
    {
        if (i != origen && costes[i] < min)
        {
            min = costes[i];
            indice = i;
        }
    }
    return indice;
}

template <typename tCoste>
void aplicar_descuento(vector<tCoste> &costes, vector<float> &subvenciones)
{
    for (int i = 0; i <= costes.size() - 1; i++)
    {
        costes[i] *= subvenciones[i] / 100;
    }
}

template <typename tCoste>
Ruta repartir_inventario(vector<tCoste> &costes, int cantidad)
{
}

template <typename tCoste>
Ruta calcula_ruta(typename GrafoP<tCoste>::vertice origen,
                  int cantidad,
                  GrafoP<tCoste> &G,
                  vector<int> &capacidades,
                  vector<float> &subvencion)
{
    vector<int> cantidades(G.numVert());
    vector<typename GrafoP<tCoste>::vertice> P;
    typename GrafoP<tCoste>::vertice destino;

    vector<tCoste> costes_minimos = Dijkstra(G, origen, P);
    aplicar_descuento(costes_minimos, subvencion);

    std::cout << costes_minimos << std::endl;

    int almacen = encontrar_menor(costes_minimos, origen);

    return repartir_inventario(costes_minimos, cantidad);
}

int main()
{
    srand(time(nullptr));

    int tam = 5;
    int cant = 1000;
    GrafoP<tCoste> G(tam);
    vector<int> cap;
    vector<float> sub;

    for (int i = 0; i < G.numVert(); i++)
    {
        for (int j = 0; j < G.numVert(); j++)
        {
            if (i == j)
            {
                G[i][j] = 0;
            }
            else
            {
                int val = rand() % 100;
                G[i][j] = val;
            }
        }
        cap.push_back(rand() % 500);
        sub.push_back(rand() % 100);
    }
    std::cout << G;

    Ruta r = calcula_ruta(0, cant, G, cap, sub);
}
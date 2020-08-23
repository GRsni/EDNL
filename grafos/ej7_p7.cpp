#include <iostream>
#include <cstdlib>
#include <ctime>

#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef float tCoste;

typedef typename GrafoP<tCoste>::vertice ciudad;

template <>
ostream &operator<<<size_t>(ostream &os, const Lista<size_t> &L)
{
    typedef Lista<Grafo::vertice>::posicion posicion;
    for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
        os << L.elemento(i) << ' ';
    return os;
}

template <typename tCoste>
tCoste calcula_ruta(const GrafoP<tCoste> &Tren, const GrafoP<tCoste> &Bus,
                    ciudad origen, ciudad destino, ciudad cambio1, ciudad cambio2,
                    typename GrafoP<tCoste>::tCamino &ruta)
{

    ciudad cambio_real;
    vector<ciudad> caminos_bus;
    vector<ciudad> caminos_tren;
    typename GrafoP<tCoste>::tCamino ruta_hasta_cambio;
    typename GrafoP<tCoste>::tCamino ruta_desde_cambio;
    vector<tCoste> costes_tren_desde_origen = Dijkstra(Tren, origen, caminos_tren);
    vector<tCoste> costes_bus_hasta_destino = DijkstraInv(Bus, destino, caminos_bus);

    std::cout << "Tren\n"
              << Tren;
    std::cout << "Bus\n"
              << Bus;
    std::cout << "Costes en tren desde origen:"<<costes_tren_desde_origen << std::endl;
    std::cout << "Costes en bus hasta destino:"<<costes_bus_hasta_destino << std::endl;

    tCoste coste_final = costes_tren_desde_origen[cambio1] + costes_bus_hasta_destino[cambio1];

    cambio_real = cambio1;
    std::cout << "costes primero:" << coste_final << std::endl;
    if (costes_tren_desde_origen[cambio2] + costes_bus_hasta_destino[cambio2] < coste_final)
    {
        coste_final = costes_tren_desde_origen[cambio2] + costes_bus_hasta_destino[cambio2];
        cambio_real = cambio2;
    }

    ruta_hasta_cambio = camino<tCoste>(origen, cambio_real, caminos_tren);
    std::cout << "Ruta hasta cambio: "<<ruta_hasta_cambio << std::endl;
    ruta_desde_cambio = camino<tCoste>(destino, cambio_real, caminos_bus);
    std::cout << "Ruta desde cambio: "<<ruta_desde_cambio << std::endl;

    ruta = ruta_desde_cambio;

    return coste_final;
}

int main()
{
    srand(time(nullptr));

    int tam = 20;
    GrafoP<tCoste> bus(tam);
    GrafoP<tCoste> tren(tam);
    typename GrafoP<tCoste>::tCamino ruta;

    for (int i = 0; i <= tam - 1; i++)
    {
        for (int j = 0; j <= tam - 1; j++)
        {
            if (i == j)
            {
                tren[i][j] = 0;
                bus[i][j] = 0;
            }
            else
            {
                bus[i][j] = rand() % 100;
                if(bus[i][j]<10){
                    bus[i][j]=GrafoP<tCoste>::INFINITO;
                }
                tren[i][j] = rand() % 100;
                if(tren[i][j]<10){
                    tren[i][j]=GrafoP<tCoste>::INFINITO;
                }
            }
        }
    }

    std::cout << "Coste de ruta: "<<calcula_ruta(tren, bus, 0, 4, 2, 3, ruta) << std::endl;
    std::cout << "Ruta: "<<ruta;
}
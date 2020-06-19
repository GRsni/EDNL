#include <iostream>

#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"

typedef double tCoste;

struct Viaje
{
   tCoste precio;
   typename GrafoP<tCoste>::vertice origen;
   typename GrafoP<tCoste>::vertice destino;
};
/*
// Suma de costes (Dijkstra y Floyd)
template <typename tCoste>
tCoste suma(tCoste x, tCoste y)
{
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   if (x == INFINITO || y == INFINITO)
      return INFINITO;
   else
      return x + y;
}*/

matriz<tCoste> FloydMAX(const GrafoP<tCoste> &G,
                        matriz<GrafoP<tCoste>::vertice> &P)
// Calcula los caminos de coste máximo entre cada
// par de vértices del grafo G. Devuelve una matriz
// de costes máximos A de tamaño n x n, con n = G.numVert()
// y una matriz de vértices P de tamaño n x n, tal que
// P[i][j] es el vértice por el que pasa el camino de coste
// mínimo de i a j, si este vértice es i el camino es directo.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n); // matriz de costes máximos

   // Iniciar A y P con caminos directos entre cada par de vértices.
   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++)
   {
      A[i] = G[i];                  // copia costes del grafo
      A[i][i] = 0;                  // diagonal a 0
      P[i] = vector<vertice>(n, i); // caminos directos
   }
   // Calcular costes máximos y caminos correspondientes
   // entre cualquier par de vértices i, j
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++)
         {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if (ikj != GrafoP<tCoste>::INFINITO)
            {
               //Las condiciones son: que exista el camino kij (que no sea infinito)
               //que el coste de ikj sea mayor que el ij (si ij no existe también)
               if (A[i][j] == GrafoP<tCoste>::INFINITO || ikj > A[i][j])
               {
                  A[i][j] = ikj;
                  P[i][j] = k;
               }
            }
         }
   return A;
}

Viaje Viaje_mas_caro(const GrafoP<tCoste> &G)
{
   Viaje V;
   matriz<tCoste> M;
   matriz<typename GrafoP<tCoste>::vertice> P;
   int i, j, max;

   std::cout << G << std::endl;
   M = FloydMAX(G, P);
   std::cout << M << std::endl;

   V.precio = 0;
   for (i = 0; i <= M.dimension() - 1; i++)
      for (j = 0; j <= M.dimension() - 1; j++)
         if (M[i][j] > V.precio)
         {
            V.precio = M[i][j];
            V.origen = i;
            V.destino = j;
         }
   return (V);
}

int main()
{

   GrafoP<tCoste> ciu3(3), ciu2(2);
   matriz<GrafoP<tCoste>::vertice> P;

   ciu3[0][0] = 0;
   ciu3[0][1] = 1;
   ciu3[0][2] = 1;
   ciu3[1][0] = 1;
   ciu3[1][1] = 0;
   ciu3[1][2] = GrafoP<tCoste>::INFINITO;
   ciu3[2][0] = 1;
   ciu3[2][1] = GrafoP<tCoste>::INFINITO;
   ciu3[2][2] = 0;

   std::cout << ciu3 << std::endl;
   Viaje v = Viaje_mas_caro(ciu3);

   ciu2[0][0] = 0;
   ciu2[0][1] = 1;
   ciu2[1][0] = 1;
   ciu2[1][1] = 0;

   std::cout << ciu2 << std::endl;
   v = Viaje_mas_caro(ciu2);
}
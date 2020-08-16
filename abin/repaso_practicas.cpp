#ifndef REPASO_PRACTICAS
#define REPASO_PRACTICAS

#include <cmath>
#include <iostream>
#include <stack>
#include <queue>

#include "Abin_din.hpp"

typedef float tElto;

int num_nodos_rec(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        std::cout << "Leyendo nodo: " << A.elemento(n) << std::endl;
        return 1 + num_nodos_rec(A, A.hijoIzqdo(n)) + num_nodos_rec(A, A.hijoDrcho(n));
    }
}

int num_nodos(Abin<tElto> A)
{

    return num_nodos_rec(A, A.raiz());
}

int altura_rec(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura_rec(A, A.hijoDrcho(n)), altura_rec(A, A.hijoIzqdo(n)));
    }
}

int altura(Abin<tElto> A)
{
    return altura_rec(A, A.raiz());
}

int profundidad(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidad(A, A.padre(n));
    }
}

bool hijos_completos(Abin<tElto> A, Abin<tElto>::nodo n)
{
    return A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO ||
           A.hijoDrcho(n) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO;
}

bool pseudocompleto_rec(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else if (profundidad(A, n) == altura(A) - 1)
    {
        return hijos_completos(A, n);
    }
    else
    {
        return pseudocompleto_rec(A, A.hijoIzqdo(n)) && pseudocompleto_rec(A, A.hijoDrcho(n));
    }
}

bool pseudocompleto(Abin<tElto> A)
{
    return pseudocompleto_rec(A, A.raiz());
}

#endif
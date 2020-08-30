#ifndef REPASO_PRACTICAS
#define REPASO_PRACTICAS

#include <cmath>
#include <iostream>
#include <stack>
#include <queue>

#include "Abin_din.hpp"
#include "Abin_E-S.hpp"

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

bool similares_rec(Abin<tElto> A, Abin<tElto>::nodo a, Abin<tElto> B, Abin<tElto>::nodo b)
{
    if (a == Abin<tElto>::NODO_NULO && b == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else if (a == Abin<tElto>::NODO_NULO && b != Abin<tElto>::NODO_NULO || a != Abin<tElto>::NODO_NULO && b == Abin<tElto>::NODO_NULO)
    {
        return false;
    }
    else
    {
        return similares_rec(A, A.hijoIzqdo(a), B, B.hijoIzqdo(b)) && similares_rec(A, A.hijoDrcho(a), B, B.hijoDrcho(b));
    }
}

bool similares(Abin<tElto> A, Abin<tElto> B)
{
    return similares_rec(A, A.raiz(), B, B.raiz());
}

void reflejado_rec(Abin<tElto>& A, Abin<tElto>::nodo n, Abin<tElto>& nuevo)
{
    if (n != Abin<tElto>::NODO_NULO)
    {
        std::cout<<"Leyendo nodo: "<<A.elemento(n)<<std::endl;
        imprimirAbin(nuevo);
        if (n == A.raiz())
        {
            nuevo.insertarRaiz(A.elemento(n));
        }
        else
        {
            if (A.hijoDrcho(n) != Abin<tElto>::NODO_NULO)
            {
                nuevo.insertarHijoIzqdo(n, A.elemento(n));
                reflejado_rec(A, A.hijoDrcho(n), nuevo);
            }
            if (A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO)
            {
                nuevo.insertarHijoDrcho(n, A.elemento(n));
                reflejado_rec(A, A.hijoIzqdo(n), nuevo);
            }
        }
    }
}

Abin<tElto> reflejado(Abin<tElto> A)
{
    Abin<tElto> ref;
    reflejado_rec(A, A.raiz(), ref);
    return ref;
}

#endif
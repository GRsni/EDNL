#ifndef OPER_ABIN_H
#define OPER_ABIN_H

#include <cmath>
#include <iostream>

#include "Abin_din.hpp"

typedef char tElto;

int numeroNodos_rec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return (1 + numeroNodos_rec(A.hijoDrcho(n), A) + numeroNodos_rec(A.hijoIzqdo(n), A));
    }
}

int numeroNodos(Abin<tElto> A)
{
    return numeroNodos_rec(A.raiz(), A);
}

int alturaAbin_rec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + fmax(alturaAbin_rec(A.hijoDrcho(n), A), alturaAbin_rec(A.hijoIzqdo(n), A));
    }
}

int alturaAbin(Abin<tElto> A)
{
    return alturaAbin_rec(A.raiz(), A);
}

int profArbol(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return (1 + profArbol(A.padre(n), A));
    }
}

int difAlturas(Abin<tElto>::nodo n, Abin<tElto> A)
{
    return abs(alturaAbin_rec(A.hijoDrcho(n), A) -
               alturaAbin_rec(A.hijoIzqdo(n), A));
}

int deseqArbol_rec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return fmax(difAlturas(n, A),
                    fmax(deseqArbol_rec(A.hijoDrcho(n), A),
                         deseqArbol_rec(A.hijoIzqdo(n), A)));
    }
}

int deseqArbol(Abin<tElto> A)
{
    return deseqArbol_rec(A.raiz(), A);
}

bool subarbolDeseq(Abin<tElto>::nodo n, Abin<tElto> A)
{
    return !((A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO) ||
             (A.hijoDrcho(n) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO));
}

bool pseudocompleto_rec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        //std::cout << A.elemento(n) << " ";
        if (A.profundidad(n) == A.altura() - 1)
        {
            return subarbolDeseq(n, A);
        }
        else
        {
            return pseudocompleto_rec(A.hijoDrcho(n), A) && pseudocompleto_rec(A.hijoIzqdo(n), A);
        }
    }
}

bool pseudocompleto(Abin<tElto> A)
{
    return pseudocompleto_rec(A.raiz(), A);
}

#endif //OPER_ABIN_H
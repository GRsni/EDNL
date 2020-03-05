#ifndef OPER_ABIN_H
#define OPER_ABIN_H

#include <cmath>
#include <iostream>

#include "Abin_din.h"

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
        return 1 + std::fmax(alturaAbin_rec(A.hijoDrcho(n), A),
                             alturaAbin_rec(A.hijoIzqdo(n), A));
    }
}

int alturaAbin(Abin<tElto> A)
{
    return alturaAbin_rec(A.raiz(), A);
}

#endif //OPER_ABIN_H
#ifndef REPASO_PRACTICAS
#define REPASO_PRACTICAS

#include <iostream>

#include "Agen_din.hpp"
#include "agen_E-S.h"

typedef float tElto;

int grado_rec(Agen<tElto> A, Agen<tElto>::nodo n)
{
    if (n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (A.hijoIzqdo(n) != Agen<tElto>::NODO_NULO)
        {
        }
    }
}

int grado(Agen<tElto> A)
{
    return grado_rec(A, A.raiz());
}

#endif //REPASO_PRACTICAS
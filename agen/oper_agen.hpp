#ifndef OPER_AGEN_H
#define OPER_AGEN_H

#include <cmath>
#include <iostream>
#include <stack>
#include <queue>
#include <limits>

//#include "Agen_vector.hpp"
#include "Agen_din.hpp"

typedef float T;

int numero_nodos_rec(Agen<T>::nodo n, Agen<T> &A)
{
    int num = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        num++;

        Agen<T>::nodo siguiente = A.hijoIzqdo(n);
        while (siguiente != Agen<T>::NODO_NULO)
        {
            num += numero_nodos_rec(siguiente, A);
            siguiente = A.hermDrcho(siguiente);
        }
    }
    return num;
}

int numero_nodos(Agen<T> &A)
{
    return numero_nodos_rec(A.raiz(), A);
}

bool mas_pobre_descendencia(Agen<T>::nodo n, T riqueza, Agen<T> &A)
{

    if (n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool prospero = true;
        Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO && prospero)
        {
            if (A.elemento(hijo) <= riqueza)
            {
                prospero = false;
            }
            prospero &= mas_pobre_descendencia(hijo, riqueza, A);
            hijo = A.hermDrcho(hijo);
        }
        return prospero;
    }
}

bool mas_rico_ascendencia(Agen<T>::nodo n, Agen<T> &A)
{
    bool prospero = true;
    Agen<T>::nodo ascendente = A.padre(n);
    while (ascendente != Agen<T>::NODO_NULO && prospero)
    {
        if (A.elemento(n) <= A.elemento(ascendente))
        {
            prospero = false;
        }
        ascendente = A.padre(ascendente);
    }
    return prospero;
}

bool es_prospero(Agen<T>::nodo n, Agen<T> &A)
{
    std::cout << A.elemento(n) << " es: " << mas_rico_ascendencia(n, A) << ", " << mas_pobre_descendencia(n, A.elemento(n), A) << std::endl;
    return mas_rico_ascendencia(n, A) && mas_pobre_descendencia(n, A.elemento(n), A);
}

int contar_numero_prosperos(Agen<T>::nodo n, Agen<T> &A)
{
    int prosperos = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (es_prospero(n, A))
        {
            prosperos++;
        }
        Agen<T>::nodo siguiente = A.hijoIzqdo(n);
        while (siguiente != Agen<T>::NODO_NULO)
        {
            prosperos += contar_numero_prosperos(siguiente, A);
            siguiente = A.hermDrcho(siguiente);
        }
    }
    return prosperos;
}

int prosperidad(Agen<T> &A)
{
    int numNodos = numero_nodos(A);
    int numProsperos = contar_numero_prosperos(A.raiz(), A);
    return (float)numProsperos / numNodos * 100.0;
}

/************************** NIETOS = 2* HIJOS *************************************/

int num_hijos(Agen<T>::nodo n, Agen<T> A)
{
    int num = 0;
    Agen<T>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != Agen<T>::NODO_NULO)
    {
        num++;
        hijo = A.hermDrcho(hijo);
    }
    return num;
}

int num_nietos(Agen<T>::nodo n, Agen<T> &A)
{
    int numNietos = 0;
    Agen<T>::nodo hijo = A.hijoIzqdo(n);
    while (hijo != Agen<T>::NODO_NULO)
    {
        numNietos += num_hijos(hijo, A);
        hijo = A.hermDrcho(hijo);
    }
    return numNietos;
}

bool es_nodo_verde(Agen<T>::nodo n, Agen<T> A)
{
    return num_hijos(n, A) * 2 == num_nietos(n, A);
}

int contar_nodos_verdes_rec(Agen<T>::nodo n, Agen<T> &A)
{
    int verdes = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (es_nodo_verde(n, A))
        {
            verdes++;
        }
        Agen<T>::nodo siguiente = A.hijoIzqdo(n);
        while (siguiente != Agen<T>::NODO_NULO)
        {
            verdes += contar_nodos_verdes_rec(siguiente, A);
            siguiente = A.hermDrcho(siguiente);
        }
    }
    return verdes;
}

int contar_nodos_verdes(Agen<T> &A)
{
    return contar_nodos_verdes_rec(A.raiz(), A);
}

int grado_Agen_rec(Agen<T>::nodo n, Agen<T> A)
{
    int base = num_hijos(n, A);
    n = A.hijoIzqdo(n);
    while (n != Agen<T>::NODO_NULO)
    {
        int num = grado_Agen_rec(n, A);
        n = A.hermDrcho(n);
        if (num > base)
            base = num;
    }
    return base;
}

int grado_Agen(const Agen<T> A)
{
    if (A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return grado_Agen_rec(A.raiz(), A);
    }
}

int profundidad(Agen<T>::nodo n, Agen<T> A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidad(A.padre(n), A);
    }
}

int altura_rec(Agen<T>::nodo n, Agen<T> A)
{
    Agen<T>::nodo m = A.hijoIzqdo(n);
    if (n = Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int desequilibrio(Agen<T> A)
{
    int max = 0, min = INT_MAX;
    Agen<T>::nodo n = A.hijoIzqdo(A.raiz());

    if (A.arbolVacio())
    {
        return 0;
    }
    else
    {
        while (n != Agen<T>::NODO_NULO)
        {
            int alt = altura_rec(n, A);
            if (alt > max)
                max = alt;
            else if (alt < min)
                min = alt;
            n = A.hermDrcho(n);
        }
        return max - min;
    }
}

#endif //OPER_AGEN_H
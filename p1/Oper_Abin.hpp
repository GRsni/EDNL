#ifndef OPER_ABIN_H
#define OPER_ABIN_H

#include <cmath>
#include <iostream>
#include <stack>
#include <queue>

#include "Abin_din.hpp"

typedef char tElto;

struct Expresion
{
    double val;
    char op;
    Expresion(double d = 0, char c = ' ') : val(d), op(c) {}
};

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

bool pseudocompleto_rec2(Abin<tElto>::nodo n, Abin<tElto> A) //ACABAR IMPLEMENTACION
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else if ((A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO) ||
             (A.hijoDrcho(n) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO))
    {
        return false;
    }
    else if (alturaAbin_rec(A.hijoDrcho(n), A) > alturaAbin_rec(A.hijoIzqdo(n), A))
    {
        return pseudocompleto_rec2(A.hijoDrcho(n), A);
    }
    return true;
}

bool pseudocompleto(Abin<tElto> A)
{
    return pseudocompleto_rec(A.raiz(), A);
}

bool arbolesSimilares_rec(Abin<tElto>::nodo a, Abin<tElto> A, Abin<tElto>::nodo b, Abin<tElto> B)
{
    /*
    if (a == Abin<tElto>::NODO_NULO && b != Abin<tElto>::NODO_NULO ||
        a != Abin<tElto>::NODO_NULO && b == Abin<tElto>::NODO_NULO)
    {
        return false;
    }
    else if (a == Abin<tElto>::NODO_NULO && b == Abin<tElto>::NODO_NULO)
    {
        return true;
    }*/

    /*NUEVA VERSION*/
    if (a == Abin<tElto>::NODO_NULO && b == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else if (a == Abin<tElto>::NODO_NULO || b == Abin<tElto>::NODO_NULO)
    {
        return false;
    }
    else
        return arbolesSimilares_rec(A.hijoIzqdo(a), A, B.hijoIzqdo(b), B) &&
               arbolesSimilares_rec(A.hijoDrcho(a), A, B.hijoDrcho(b), B);
}

bool arbolesSimilares(Abin<tElto> A, Abin<tElto> B)
{
    return arbolesSimilares_rec(A.raiz(), A, B.raiz(), B);
}

void reflejado_rec(Abin<tElto>::nodo a, Abin<tElto> A, Abin<tElto>::nodo b, Abin<tElto> B)
{
    if (A.hijoIzqdo(a) != Abin<tElto>::NODO_NULO)
    {
        B.insertarHijoDrcho(b, A.elemento(A.hijoIzqdo(a)));
        reflejado_rec(A.hijoIzqdo(a), A, B.hijoDrcho(b), B);
    }
    if (A.hijoDrcho(a) != Abin<tElto>::NODO_NULO)
    {
        B.insertarHijoIzqdo(b, A.elemento(A.hijoDrcho(a)));
        reflejado_rec(A.hijoDrcho(a), A, B.hijoIzqdo(b), B);
    }
}

Abin<tElto> reflejado(Abin<tElto> A)
{
    Abin<tElto> B;
    if (!A.arbolVacio())
    {
        B.insertarRaiz(A.elemento(A.raiz()));
        reflejado_rec(A.raiz(), A, B.raiz(), B);
    }
    return B;
}

double operar(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        std::cout << "Operador incorrecto.\n";
        return -1;
    }
}

double evaluar_rec(Abin<Expresion>::nodo n, Abin<Expresion> A)
{
    if (A.esHoja(n))
    {
        return A.elemento(n).val;
    }
    else
    {
        return operar(A.elemento(A.hijoIzqdo(n)).val, A.elemento(A.hijoDrcho(n)).val, A.elemento(n).op);
    }
}

double evaluar(Abin<Expresion> A)
{
    return evaluar_rec(A.raiz(), A);
}

/**************************SEMINARIOS*************************************/

int procesarNodo(Abin<tElto>::nodo n)
{
    return n != Abin<tElto>::NODO_NULO;
}

int numNodosProfIter(Abin<tElto> A)
{
    int contador = 0;
    std::stack<Abin<tElto>::nodo> pila;
    Abin<tElto>::nodo n;
    pila.push(A.raiz());
    do
    {
        n = pila.top();
        pila.pop();
        contador += procesarNodo(n);
        if (A.hijoDrcho(n) != Abin<tElto>::NODO_NULO)
        {
            pila.push(A.hijoDrcho(n));
        }
        if (A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO)
        {
        }

    } while (!(pila.empty() && n == Abin<tElto>::NODO_NULO));
    return contador;
}

int numNodosAnchuraIter(Abin<tElto> A)
{
    int contador = 0;
    std::queue<Abin<tElto>::nodo> cola;
    Abin<tElto>::nodo n;
    cola.push(A.raiz());
    while (!cola.empty())
    {
        n = cola.front();
        cola.pop();
        contador += procesarNodo(n);
        if (n != Abin<tElto>::NODO_NULO)
        {
            cola.push(A.hijoIzqdo(n));
            cola.push(A.hijoDrcho(n));
        }
    }
    return contador;
}

#endif //OPER_ABIN_H
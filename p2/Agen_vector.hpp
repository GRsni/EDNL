#ifndef AGEN_LIS_H
#define AGEN_LIS_H

#include <cassert>
#include "lista_en.h"

template <typename T>
class Agen
{
public:
    typedef int nodo;
    static const nodo NODO_NULO;
    explicit Agen(size_t maxNodos);
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHermDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHermDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T &elemento(nodo n) const;
    T &elemento(nodo n);
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hermDrcho(nodo n) const;

    Agen(const Agen<T> &A);
    Agen<T> &operator=(const Agen<T> &A);
    ~Agen();

private:
    struct celda
    {
        T elto;
        nodo padre;
        Lista<nodo> hijos;
    };
    celda *nodos;
    int maxNodos;
    int numNodos;
};

template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(-1);

template <typename T>
inline Agen<T>::Agen(size_t maxNodos) : nodos(new celda[maxNodos]),
                                        maxNodos(maxNodos), numNodos(0)
{
    for (nodo n = 0; n < maxNodos; n++)
    {
        nodos[n].padre = NODO_NULO;
    }
}

template <typename T>
void Agen<T>::insertarRaiz(const T &e)
{
    assert(numNodos == 0);
    numNodos = 1;
    nodos[0].elto = e;
}

template <typename T>
void Agen<T>::insertarHijoIzqdo(Agen<T>::nodo n, const T &e)
{
    nodo hizq;
    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);
    assert(numNodos < maxNodos);

    for (hizq = 1; nodos[hizq].padre != NODO_NULO; hizq++)
        ;
    nodos[hizq].elto = e;
    nodos[hizq].padre = n;

    Lista<nodo> &Lh = nodos[n].hijos;
    Lh.insertar(hizq, Lh.primera());
    ++numNodos;
}

template <typename T>
void Agen<T>::insertarHermDrcho(Agen<T>::nodo n, const T &e)
{
    nodo hder;
    assert(n >= 0 && n < maxNodos);
    assert(nodos[n].padre != NODO_NULO);
    assert(numNodos < maxNodos);

    for (hder = 1; nodos[hder].padre != NODO_NULO; hder++)
        ;
    nodos[hder].elto = e;
    nodos[hder].padre = nodos[n].padre;
    Lista<nodo> &Lhp = nodos[nodos[n].padre].hijos;
    Lhp.insertar(hder, Lhp.siguiente(Lhp.buscar(n)));
    ++numNodos;
}

template <typename T>
void Agen<T>::eliminarHijoIzqdo(Agen<T>::nodo n)
{
    nodo hizq;
    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);
    Lista<nodo> &Lh = nodos[n].hijos;
    assert(Lh.primera() != Lh.fin());

    hizq = Lh.elemento(Lh.primera());
    assert(nodos[hizq].hijos.primera() == nodos[hizq].hijos.fin());

    nodos[hizq].padre = NODO_NULO;
    Lh.eliminar(Lh.primera());
    --numNodos;
}

template <typename T>
void Agen<T>::eliminarHermDrcho(Agen<T>::nodo n)
{
    nodo hder;
    Lista<nodo>::posicion p;

    assert(n >= 0 && n < maxNodos);
    assert(nodos[n].padre != NODO_NULO);
    Lista<nodo> &Lhp = nodos[nodos[n].padre].hijos;
    p = Lhp.siguiente(Lhp.buscar(n));
    assert(p != Lhp.fin());
    hder = Lhp.elemento(p);
    assert(nodos[hder].hijos.primera() == nodos[hder].hijos.fin());
    nodos[hder].padre = NODO_NULO;
    Lhp.eliminar(p);
    --numNodos;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}

template <typename T>
inline bool Agen<T>::arbolVacio() const
{
    return (numNodos == 0);
}

template <typename T>
inline const T &Agen<T>::elemento(Agen<T>::nodo n) const
{
    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);

    return nodos[n].elto;
}

template <typename T>
inline T &Agen<T>::elemento(Agen<T>::nodo n)
{
    assert(numNodos > 0);
    assert(n > 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);

    return nodos[n].elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return (numNodos > 0) ? 0 : NODO_NULO;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::padre(Agen<T>::nodo n) const
{
    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);

    return nodos[n].padre;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen<T>::nodo n) const
{
    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);

    Lista<nodo> &Lh = nodos[n].hijos;
    if (Lh.primera() != Lh.fin())
        return Lh.elemento(Lh.primera());
    else
    {
        return NODO_NULO;
    }
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(Agen<T>::nodo n) const
{
    Lista<nodo>::posicion p;

    assert(numNodos > 0);
    assert(n >= 0 && n < maxNodos);
    assert(n == 0 || nodos[n].padre != NODO_NULO);

    if (n == 0)
        return NODO_NULO;
    else
    {
        Lista<nodo> &Lhp = nodos[nodos[n].padre].hijos;
        p = Lhp.siguiente(Lhp.buscar(n));
        if (p != Lhp.fin())
        {
            return Lhp.elemento(p);
        }
        else
            return NODO_NULO;
    }
}

template <typename T>
Agen<T>::Agen(const Agen<T> &A) : nodos(new celda[A.maxNodos]),
                                  maxNodos(A.maxNodos), numNodos(A.numNodos)
{
    for (nodo n = 0; n < maxNodos; n++)
    {
        nodos[n] = A.nodos[n];
    }
}

template <typename T>
Agen<T> &Agen<T>::operator=(const Agen<T> &A)
{
    if (this != &A)
    {
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
        numNodos = A.numNodos;
        for (nodo n = 0; n < maxNodos; n++)
        {
            nodos[n] = A.nodos[n];
        }
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    delete[] nodos;
}
#endif //AGEN_LIS_H

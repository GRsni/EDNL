#ifndef ABIN_REL_H
#define ABIN_REL_H

#include <cassert>

template <typename T>
class Abin
{
public:
    typedef int nodo;

    static const int NODO_NULO;
    explicit Abin(size_t maxNodos, const T &e_nulo = T());
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHijoDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T &elemento(nodo n) const;
    T &elemento(nodo n);
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T> &A);
    Abin<T> &operator=(const Abin<T> &A);
    ~Abin();

private:
    T *nodos;
    int maxNodos;
    T ELTO_NULO;
};

template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(-1);

template <typename T>
Abin<T>::Abin(size_t maxNodos, const T &e_nulo) : nodos(new T[maxNodos]),
                                                  maxNodos(maxNodos),
                                                  ELTO_NULO(e_nulo)
{
    for (nodo n = 0; n < maxNodos; n++)
    {
        nodos[n] = ELTO_NULO;
    }
}

template <typename T>
inline void Abin<T>::insertarRaiz(const T &e)
{
    assert(nodos[0] == ELTO_NULO);
    nodos[0] = e;
}

template <typename T>
void Abin<T>::insertarHijoIzqdo(Abin<T>::nodo n, const T &e)
{
    assert(n >= 0 && n < maxNodos);
    assert(nodos[n] != ELTO_NULO);
    assert(2 * n + 1 < maxNodos);
    assert(nodos[2 * n + 1] == ELTO_NULO);

    nodos[2 * n + 1] = e;
}

template <typename T>
void Abin<T>::insertarHijoDrcho(Abin<T>::nodo n, const T &e)
{
    assert(n >= 0 && n < maxNodos);
    assert(nodos[n] != ELTO_NULO);
    assert(2 * n + 2 < maxNodos);
    assert(nodos[2 * n + 2] != ELTO_NULO);

    nodos[2 * n + 2] = e;
}

template <typename T>
void Abin<T>::eliminarHijoIzqdo(Abin<T>::nodo n)
{
    assert(n >= 0 && n < maxNodos);
    assert(nodos[n] != ELTO_NULO);
    assert(2 * n + 1 < maxNodos);
    assert(nodos[2 * n + 1] != ELTO_NULO);
    if (4 * n + 4 < maxNodos)
    {
        assert(nodos[4 * n + 3] == ELTO_NULO && nodos[4 * n + 4] == ELTO_NULO);
    }
    else if (4 * n + 3 < maxNodos)
    {
        assert(nodos[4 * n + 3] == ELTO_NULO);
    }
    nodos[2 * n + 1] == ELTO_NULO;
}

template <typename T>
void Abin<T>::eliminarHijoDrcho(Abin<T>::nodo n)
{
    assert(n >= &&n <= maxNodos - 1);
    assert(nodos[n] != ELTO_NULO);
    assert(2 * n + 2 < maxNodos);
    assert(nodos[2 * n + 2] != ELTO_NULO);
    if (4 * n + 6 < maxNodos)
    {
        assert(nodos[4 * n + 5] == ELTO_NULO && nodos[4 * n + 6] == ELTO_NULO);
    }
    else if (4 * n + 5 < maxNodos)
    {
        assert(nodos[4 * n + 5] == ELTO_NULO);
    }
    nodos[2 * n + 2] = ELTO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(nodos[0] != ELTO_NULO);
    assert(nodos[1] == ELTO_NULO && nodos[2] == ELTO_NULO);
    nodos[0] = ELTO_NULO;
}

template <typename T>
inline bool Abin<T>::arbolVacio() const
{
    return (nodos[0] == ELTO_NULO);
}

template <typename T>
inline const T &Abin<T>::elemento(Abin<T>::nodo n) const
{
    assert(n >= &&n < maxNodos - 1);
    assert(nodos[n] != ELTO_NULO);
    return nodos[n];
}

template <typename T>
inline T &Abin<T>::elemento(Abin<T>::nodo n)
{
    assert(n >= 0 && n <= maxNodos);
    assert(nodos[n] != ELTO_NULO);
    return nodos[n];
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{
    return (nodos[0] == ELTO_NULO) ? NODO_NULO : 0;
}

template <typename T>
typename Abin<T>::nodo Abin<T>::padre(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);
    assert(nodos[n] != ELTO_NULO);
    return (n == 0) ? NODO_NULO : (n - 1) / 2;
}

template <typename T>
typename Abin<T>::nodo Abin<T>::hijoIzqdo(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);
    assert(nodos[n] != ELTO_NULO);
    return (2 * n + 1 > maxNodos || nodos[2 * n + 1] == ELTO_NULO) ? NODO_NULO : 2 * n + 1;
}

template <typename T>
typename Abin<T>::nodo Abin<T>::hijoDrcho(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);
    assert(nodos[n] != ELTO_NULO);
    return (2 * n + 2 >= maxNodos || nodos[2 * n + 2] == ELTO_NULO) ? NODO_NULO : 2 * n + 2;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &A) : nodos(new T[A.maxNodos]),
                                  maxNodos(A.maxNodos),
                                  ELTO_NULO(A.ELTO_NULO)
{
    for (nodo n = 0; n <= maxNodos - 1; n++)
    {
        nodos[n] = A.nodos[n];
    }
}

template <typename T>
inline Abin<T>::~Abin()
{
    delete[] nodos;
}

template <typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &A)
{
    if (this != &A)
    {
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        ELTO_NULO = A.ELTO_NULO;
        for (nodo n = 0; n <= maxNodos - 1; n++)
        {
            nodos[n] = A.nodos[n];
        }
        return *this;
    }
}

#endif
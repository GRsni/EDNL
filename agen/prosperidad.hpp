
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

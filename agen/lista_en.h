#ifndef LISTA_ENLA_H
#define LISTA_ENLA_H
#include <cassert>

template <typename T>
class Lista
{
    struct nodo;

public:
    typedef nodo *posicion;
    Lista();
    Lista(const Lista<T> &l);
    Lista<T> &operator=(const Lista<T> &l);
    void insertar(const T &x, posicion p);
    void eliminar(posicion p);
    int getTam() const;
    const T &elemento(posicion p) const;
    T &elemento(posicion p);
    posicion buscar(const T &x) const;    //orden n
    posicion siguiente(posicion p) const; //orden 1
    posicion anterior(posicion p) const;  //orden n
    posicion primera() const;             //orden 1
    posicion fin() const;                 //orden n siempre
    ~Lista();

private:
    struct nodo
    {
        T elto;
        nodo *sig;
        nodo(const T &e, nodo *p = 0) : elto(e), sig(p) {}
    };
    nodo *L;
    int tam;
    void copiar(const Lista<T> &l);
};

template <typename T>
void Lista<T>::copiar(const Lista<T> &l)
{
    L = new nodo(T());
    nodo *q = L;
    tam = l.tam;
    for (nodo *r = l.L->sig; r; r = r->sig)
    {
        q->sig = new nodo(r->elto);
        q = q->sig;
    }
}

template <typename T>
inline int Lista<T>::getTam() const
{
    return tam;
}

template <typename T>
inline Lista<T>::Lista() : L(new nodo(T())), tam(0) {}

template <typename T>
Lista<T>::Lista(const Lista<T> &l)
{
    copiar(l);
}

template <typename T>
Lista<T> &Lista<T>::operator=(const Lista<T> &l)
{
    if (this != &l)
    {
        this->~Lista();
        copiar(l);
    }
    return *this;
}

template <typename T>
void Lista<T>::insertar(const T &x, Lista<T>::posicion p)
{
    tam++;
    p->sig = new nodo(x, p->sig);
}

template <typename T>
void Lista<T>::eliminar(Lista<T>::posicion p)
{
    assert(p->sig);
    tam--;
    nodo *q = p->sig;
    p->sig = q->sig;
    delete q;
}

template <typename T>
inline const T &Lista<T>::elemento(Lista<T>::posicion p) const
{
    assert(p->sig);
    return p->sig->elto;
}

template <typename T>
inline T &Lista<T>::elemento(Lista<T>::posicion p)
{
    assert(p->sig);
    return p->sig->elto;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::buscar(const T &x) const
{
    nodo *q = L;
    bool encontrado = false;
    while (q->sig && !encontrado)
    {
        if (q->sig->elto == x)
        {
            encontrado = true;
        }
        else
            q = q->sig;
    }
    if (!encontrado)
    {
        q = 0;
    }
    return q;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::siguiente(Lista<T>::posicion p) const
{
    assert(p->sig);
    return p->sig;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::anterior(Lista<T>::posicion p) const
{
    nodo *q = L;
    assert(p != L);
    while (q->sig != p)
    {
        q = q->sig;
    }
    return q;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
    return L;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
    nodo *p = L;
    while (p->sig)
    {
        p = p->sig;
    }
    return p;
}

template <typename T>
inline Lista<T>::~Lista()
{
    nodo *q;
    while (L)
    {
        q = L->sig;
        delete L;
        L = q;
    }
}

#endif // LISTA_ENLA_H

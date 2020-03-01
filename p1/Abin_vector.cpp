
#ifndef ABIN_VECO_H
#define ABIN_VECO_H

template <typename T>
class AbinVec
{
public:
	typedef int nodo;
	static const nodo NODO_NULO;
	explicit AbinVec(size_t maxNodos);

	void insertarRaiz(const T &e);
	void insertarHijoIzq(nodo n, const T &e);
	void insertarHijoDer(nodo n, const T &e);
	void eliminarHijoIzq(nodo n);
	void eliminarHijoDer(nodo n);
	void eliminarRaiz();
	bool arbolVacio() const;
	const T &elemento(nodo n) const;
	T &elemento(nodo n);
	nodo raiz() const;
	nodo padre(nodo n) const;
	nodo hijoIzq(nodo n) const;
	nodo hijoDer(nodo n) const;
	AbinVec(const AbinVec<T> &A);
	AbinVec<T> &operator=(const AbinVec<T> &A);
	~AbinVec();

private:
	struct celda
	{
		T elto;
		nodo padre, hizq, hder;
	};
	celda *nodos;
	int maxNodos;
	int numNodos;
};

template <typename T>
inline AbinVec<T>::AbinVec(size_t maxNodos) : nodos(new celda[maxNodos]),
											  maxNodos(maxNodos),
											  numNodos(0)
{
}

template <typename T>
inline void AbinVec<T>::insertarRaiz(const T &e)
{
	assert(numNodos == 0);

	numNodos = 1;
	nodos[0].elto = e;
	nodos[0].padre = NODO_NULO;
	nodos[0].hizq = NODO_NULO;
	nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void AbinVec<T>::insertarHijoIzq(AbinVec<T>::nodo n, const T &e)
{
	assert(n >= 0 && n < numNodos);		// Nodo válido
	assert(nodos[n].hizq == NODO_NULO); // n no tiene hijo izqdo.
	assert(numNodos < maxNodos);		// Árbol no lleno
	// Añadir el nuevo nodo al final de la secuencia.
	nodos[n].hizq = numNodos;
	nodos[numNodos].elto = e;
	nodos[numNodos].padre = n;
	nodos[numNodos].hizq = NODO_NULO;
	nodos[numNodos].hder = NODO_NULO;
	++numNodos;
}

template <typename T>
inline void AbinVec<T>::insertarHijoDer(AbinVec<T>::nodo n, const T &e)
{
	assert(n >= 0 && n < numNodos);
	assert(nodos[n].hder == NODO_NULO);
	assert(numNodos < maxNodos);

	nodos[n].hder = numNodos;
	nodos[numNodos].elto = e;
	nodos[numNodos].padre = n;
	nodos[numNodos].hizq = NODO_NULO;
	nodos[numNodos].hder = NODO_NULO;
}

template <typename T>
void AbinVec<T>::eliminarHijoIzq(AbinVec<T>::nodo n)
{
	nodo hizqdo;
	assert(n >= 0 && n < numNodos); // Nodo válido
	hizqdo = nodos[n].hizq;
	assert(hizqdo != NODO_NULO); // Existe hijo izqdo. de n.
	assert(nodos[hizqdo].hizq == NODO_NULO &&
		   nodos[hizqdo].hder == NODO_NULO);
	if (hizqdo != numNodos - 1)
	{
		// Mover el último nodo a la posición del hijo izqdo.
		nodos[hizqdo] = nodos[numNodos - 1];
		// Actualizar la posición del hijo (izquierdo o derecho)
		// en el padre del nodo movido.
		if (nodos[nodos[hizqdo].padre].hizq == numNodos - 1)
		{
			nodos[nodos[hizqdo].padre].hizq = hizqdo;
		}
		else
		{
			nodos[nodos[hizqdo].padre].hder = hizqdo;
		}
		if (nodos[hizqdo].hizq != NODO_NULO)
		{
			nodos[nodos[hizqdo].hizq].padre = hizqdo;
		}
		if (nodos[hizqdo].hder != NODO_NULO)
		{
			nodos[nodos[hizqdo].hizq].padre = hizqdo;
		}
		nodos[n].hizq = NODO_NULO;
		--numNodos;
	}
}
#endif // !ABIN_VECO_H

#pragma once
#ifndef ABIN_VECO_H
#define ABIN_VECO_H

template <typename T> class AbinVec {
public:
	typedef int nodo;
	static const nodo NODO_NULO;
	explicit AbinVec(size_t maxNodos);

	void insertarRaiz(const T& e);
	void insertarHijoIzq(nodo n, const T& e);
	void insertarHijoDer(nodo n, const T& e);
	void eliminarHijoIzq(nodo n);
	void eliminarHijoDer(nodo n);
	void eliminarRaiz();
	bool arbolVacio() const;
	const T& elemento(nodo n) const;
	T& elemento(nodo n);
	nodo raiz() const;
	nodo padre(nodo n) const;
	nodo hijoIzq(nodo n) const;
	nodo hijoDer(nodo n) const;
	AbinVec(const AbinVec<T>& A);
	AbinVec<T>& operator =(const AbinVec<T>& A);
	~AbinVec();
private:
	struct celda {
		T elto;
		nodo padre, hizq, hder;
	};
	celda* nodos;
	int maxNodos;
	int numNodos;
};
#endif // !ABIN_VECO_H

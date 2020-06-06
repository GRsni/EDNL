

template <typename T>
int contar_nodos_verdes(const Agen<T>& A)
{
	return contar_nodos_verdes_rec(A.raiz(),A);
}


template <typename T>
int contar_nodos_verdes_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
	int numNietos = 0, numHijos = 0;
	typename Agen<T>::nodo hijo;// = A.hijoIzqdo(n);
	int verdes = 0;
	
	if(n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		if(verde(n,A))
		{
			//return 1 + contar_nodos_verdes_rec(A.hijoIzqdo(n), A);
			verdes++;
		}

		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO)
		{
			verdes += contar_nodos_verdes_rec(hijo,A);
			hijo = A.hermDrcho(hijo);
		}
			
	}
	return verdes;
}

template <typename T>
bool verde(typename Agen<T>::nodo n, const Agen<T>& A)
{
	int numNietos = 0, numHijos = 0;
	
	numNietos = NumNietos(n,A);
	//cout << "\nNumNietos de " << A.elemento(n) << " :" << numNietos;
	numHijos = NumHijos(n,A);
	//cout << "\nNumHijos de " << A.elemento(n) << " :" << numHijos;
	
	if(numNietos != 0 && numHijos != 0)
	{
		if(numNietos == (2 * numHijos))
			return true;
		else 
			return false;
	}
	return false;
}

template <typename T>
int NumHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		int cont = 0;
		while(hijo != Agen<T>::NODO_NULO)
		{
			hijo = A.hermDrcho(hijo);
			cont++;
		}
		return cont;
}


template <typename T>
int NumNietos(typename Agen<T>::nodo n, const Agen<T>& A)
{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		int cont = 0;
		while(hijo != Agen<T>::NODO_NULO)
		{
			cont += NumHijos(hijo,A);
			hijo = A.hermDrcho(hijo);
		}
		return cont;
}

template <typename T>
int contar_nodos_prospero(const Agen<T>& A)
{
	return contar_nodos_prospero_rec(A.raiz(),A);
}


template <typename T>
int contar_nodos_prospero_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
	int numNietos = 0, numHijos = 0;
	typename Agen<T>::nodo hijo;// = A.hijoIzqdo(n);
	int prospe = 0;
	
	if(n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		cout<<"\nElemento: "<<A.elemento(n)<<endl;
		if(padres_prospero(n,A.elemento(n),A) && hijos_prospero(n, A.elemento(n),A ))
		{
			//return 1 + contar_nodos_verdes_rec(A.hijoIzqdo(n), A);
			prospe++;
		}

		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO)
		{
			prospe += contar_nodos_prospero_rec(hijo,A);
			hijo = A.hermDrcho(hijo);
		}
			
	}
	return prospe;
}

template <typename T>
bool padres_prospero(typename Agen<T>::nodo n, int prosperidad,const Agen<T>& A)
{
	if(A.padre(n) != Agen<T>::NODO_NULO)
	{
		n = A.padre(n);
		if (A.elemento(n) > prosperidad)
			return false;
	}
	return true;
}

template <typename T>
bool hijos_prospero(typename Agen<T>::nodo n, int prosperidad, const Agen<T>& A)
{
	typename Agen<T>::nodo hijo;
	cout<<"\nPATATA"<<A.elemento(n);
	if(n == Agen<T>::NODO_NULO)
	{	
		return true;
	}
	else
	{
		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO)
		{
			if(prosperidad < A.elemento(hijo))
			{
				hijos_prospero(hijo, prosperidad,A);
				hijo = A.hermDrcho(hijo);
			}
			else return false;	
		}
		return true;
	}
}

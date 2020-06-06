#include <iostream>
#include <fstream>

#include "Abin_din.hpp"
#include "Oper_Abin.hpp"
#include "abin_E-S.hpp"

//typedef char tElto;
//const tElto fin = '#'; // Fin de lectura

typedef float tElto;
const tElto fin = -1;

int main()
{
    Abin<tElto> A, B;
    std::cout << "\n*** Lectura de arbol binario A de abin.dat ***\n";
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);          // Desde fichero.
    fe.close();
    std::cout << "\n*** Mostrar arbol binario A ***\n";
    imprimirAbin(A); // En std::cout
    std::cout << "El grado de prosperidad del arbol es: " << prosperidad(A) << std::endl;
    //std::cout << "Numero de nodos en A: " << numeroNodos(A) << std::endl;
    // std::cout << "Numero de nodos en A por Prof Iter: " << numNodosProfIter(A) << std::endl;
    //std::cout << "Numero de nodos en A por Anchura Iter: " << numNodosAnchuraIter(A) << std::endl;
    //std::cout << "Altura de A: " << A.altura() << std::endl;
    //Abin<tElto>::nodo n = A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())));
    //std::cout << "Profundidad del nodo " << A.elemento(n) << " en A: " << A.profundidad(n) << std::endl;
    //std::cout << "El desequilibrio del arbol es: " << deseqArbol(A) << std::endl;
    //std::cout << "El arbol esta pseudocompleto: " << pseudocompleto(A) << std::endl;
}
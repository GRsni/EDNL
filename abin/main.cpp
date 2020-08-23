#include <iostream>
#include <fstream>

#include "Abin_din.hpp"
#include "repaso_practicas.cpp"
//#include "Oper_Abin.hpp"
#include "abin_E-S.hpp"

//typedef char tElto;
//const tElto fin = '#'; // Fin de lectura

typedef float tElto;
const tElto fin = -1;

int main(int argc, char *argv[])
{
    Abin<tElto> A, B, C;
    std::cout << "\n*** Lectura de arbol binario A de " << (argc == 2 ? argv[1] : "abin.dat") << " ***\n";
    std::ifstream fe((argc == 2 ? argv[1] : "abin.dat")); // Abrir fichero de entrada.

    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    C = A;

    std::ifstream fe2("b.dat");

    rellenarAbin(fe2, B);
    fe2.close();

    std::cout << "\n*** Mostrar arbol binario A ***\n";
    imprimirAbin(A); // En std::cout

    // std::cout << "El grado de prosperidad del arbol es: " << prosperidad(A) << std::endl;
    std::cout << "Numero de nodos en A: " << num_nodos(A) << std::endl;
    // std::cout << "Numero de nodos en A por Prof Iter: " << numNodosProfIter(A) << std::endl;
    //std::cout << "Numero de nodos en A por Anchura Iter: " << numNodosAnchuraIter(A) << std::endl;
    std::cout << "Altura de A: " << A.altura() << std::endl;
    Abin<tElto>::nodo n = A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())));
    std::cout << "Profundidad del nodo " << A.elemento(n) << " en A: " << A.profundidad(n) << std::endl;
    //std::cout << "El desequilibrio del arbol es: " << deseqArbol(A) << std::endl;
    std::cout << "El arbol es pseudocompleto: " << (pseudocompleto(A) ? "true" : "false") << std::endl;

    std::cout << "\n*** Mostrar arbol binario B ***\n";
    imprimirAbin(B); // En std::cout

    std::cout << "\n*** Mostrar arbol binario C***\n";
    imprimirAbin(C); // En std::cout

    std::cout << "A y B son similares: " << similares(A, B) << std::endl;
    std::cout << "A y C son similares: " << similares(A, C) << std::endl;

    Abin<tElto> ref = reflejado(A);
    std::cout << "\n*** Mostrar arbol binario reflejado***\n";
    imprimirAbin(ref); // En std::cout
}

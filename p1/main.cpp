#include <iostream>
#include <fstream>

#include "Abin_din.hpp"
#include "abin_E-S.hpp"
#include "Oper_Abin.hpp"

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

int main()
{
    Abin<tElto> A;
    std::cout << "\n*** Lectura de arbol binario A de abin.dat ***\n";
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);          // Desde fichero.
    fe.close();
    std::cout << "\n*** Mostrar arbol binario A ***\n";
    imprimirAbin(A); // En std::cout
    std::cout << "Numero de nodos en A: " << numeroNodos(A) << std::endl;
    std::cout << "Altura de A: " << A.altura() << std::endl;
    //Abin<tElto>::nodo n = A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())));
    //std::cout << "Profundidad del nodo " << A.elemento(n) << " en A: " << A.profundidad(n) << std::endl;
    std::cout << "El desequilibrio del arbol es: " << deseqArbol(A) << std::endl;
    std::cout << "El arbol esta pseudocompleto: " << pseudocompleto(A) << std::endl;
}

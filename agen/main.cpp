#include <iostream>
#include <fstream>

#include "Agen_din.hpp"
#include "agen_E-S.h"

//typedef char tElto;
//const tElto fin = '#';

typedef float tElto;
const tElto fin = -1;

int main(int argc, char *argv[])
{
    Agen<tElto> A, B, C;

    std::cout << "\n*** Lectura de arbol binario A de " << (argc == 2 ? argv[1] : "agen.dat") << " ***\n";
    std::ifstream fe((argc == 2 ? argv[1] : "agen.dat")); // Abrir fichero de entrada.

    rellenarAgen(fe, A); // Desde fichero.
    fe.close();

    C = A;

    std::ifstream fe2("a.dat");

    rellenarAgen(fe2, B);
    fe2.close();

    imprimirAgen(A);
}
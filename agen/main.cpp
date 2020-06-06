#include <iostream>
#include <fstream>

#include "Agen_din.hpp"
#include "oper_agen.hpp"
#include "agen_E-S.h"

//typedef char tElto;
//const tElto fin = '#';

typedef float tElto;
const tElto fin = -1;

int main()
{
    Agen<tElto> A, B;

    std::ifstream fe("agen.dat");
    rellenarAgen(fe, A);
    fe.close();

    imprimirAgen(A);

    std::cout << "Grado del arbol:" << grado_Agen(A) << std::endl;

    std::cout << "verdes: " << contar_nodos_verdes(A) << std::endl;
    std::cout << "prosperidad: " << prosperidad(A) << std::endl;
}
#include <iostream>
#include <fstream>

#include "Abin_din.h"
#include "abin_E-S.h"
#include "Oper_Abin.h"

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

int main()
{
    Abin<tElto> A;
    std::cout << "\n*** Lectura de arbol binario A de abin.dat ***\n";
    std::ifstream fe("a.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);       // Desde fichero.
    fe.close();
    std::cout << "\n*** Mostrar arbol binario A ***\n";
    imprimirAbin(A); // En std::cout
    std::cout << "Numero de nodos en A: " << numeroNodos(A) << std::endl;
    std::cout << "Altura de A: " << alturaAbin(A) << std::endl;
}

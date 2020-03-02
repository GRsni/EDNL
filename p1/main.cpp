#include <iostream>
#include <fstream>

#include "Abin_din.h"
#include "abin_E-S.h"

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

int main()
{
    Abin<tElto> A, B;
    std::cout << "*** Lectura del arbol binario A ***\n";
    rellenarAbin(A, fin);         // Desde std::cin
    std::ofstream fs("abin.dat"); // Abrir fichero de salida.
    imprimirAbin(fs, A, fin);     // En fichero.
    fs.close();
    std::cout << "\n*** Arbol A guardado en fichero abin.dat ***\n";
    std::cout << "\n*** Lectura de arbol binario B de abin.dat ***\n";
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, B);          // Desde fichero.
    fe.close();
    std::cout << "\n*** Mostrar arbol binario B ***\n";
    imprimirAbin(B); // En std::cout
}

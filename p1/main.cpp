#include <iostream>
#include <fstream>

#include "Abin_vector.h"
#include "abin_E-S.h"

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

int main()
{
    Abin<tElto> A(100), B(100);
    std::cout << "*** Lectura del �rbol binario A ***\n";
    rellenarAbin(A, fin); // Desde std::cin
    //std::ofstream fs("abin.dat");   // Abrir fichero de salida.
    //imprimirAbin(fs, A, fin);  // En fichero.
    //fs.close();
    //std::cout << "\n*** �rbol A guardado en fichero abin.dat ***\n";
    //std::cout << "\n*** Lectura de �rbol binario B de abin.dat ***\n";
    //std::ifstream fe("abin.dat");   // Abrir fichero de entrada.
    //rellenarAbin(fe, B);
    // Desde fichero.
    //fe.close();
    //std::cout << "\n*** Mostrar �rbol binario B ***\n";
    //imprimirAbin(B);
    // En std::cout
}

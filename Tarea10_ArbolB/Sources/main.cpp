#include <iostream>
#include "../Headers/ArbolB.hpp"

int main() {
    
    ArbolB<int, 5> arbol;
    arbol.Agregar(10);
    arbol.Agregar(20);
    arbol.Agregar(5);
    arbol.Agregar(6);
    arbol.Agregar(30);

    arbol.ImprimirAsc();

    return 0;
}


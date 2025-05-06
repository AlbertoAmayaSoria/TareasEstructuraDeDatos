#include <iostream>
#include "../Headers/ArbolB.hpp"

int main() {
    
    ArbolB<int, 5> arbol;
    arbol.Agregar(1);
    arbol.Agregar(2);
    arbol.Agregar(3);
    arbol.Agregar(4);
    arbol.Agregar(5);
    /*arbol.Agregar(6);
    arbol.Agregar(7);
    arbol.Agregar(8);
    arbol.Agregar(9);
    arbol.Agregar(10);
    arbol.Agregar(11);*/
    std::cout << "La cantidad de elementos en el arbol es: " << arbol.CantElem() << std::endl;
    arbol.ImprimirAsc();
    arbol.ImprimirNiveles(); 

    return 0;
}


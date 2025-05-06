#include <iostream>
#include "../Headers/ArbolB.hpp"

int main() {
    
    ArbolB<int, 5> arbol;
    arbol.Agregar(100);
    arbol.Agregar(200);
    arbol.Agregar(300);
    arbol.Agregar(400);
    arbol.Agregar(500);
    arbol.Agregar(600);
    arbol.Agregar(700);
    //arbol.Agregar(800);
    std::cout << "La cantidad de elementos en el arbol es: " << arbol.CantElem() << std::endl;
    arbol.ImprimirAsc();

    return 0;
}


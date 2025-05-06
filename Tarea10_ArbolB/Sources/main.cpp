#include <iostream>
#include <ostream>
#include "../Headers/ArbolB.hpp"

int main() {
    
    ArbolB<int, 3> arbol;
    arbol.Agregar(1);
    arbol.Agregar(2);
    arbol.Agregar(3);
    arbol.Agregar(4);
    arbol.Agregar(5);
    arbol.Agregar(6);
    arbol.Agregar(7);
    arbol.Agregar(8);
    arbol.Agregar(9);
    arbol.Agregar(10);
    arbol.Agregar(11);
    arbol.Agregar(12);
    arbol.Agregar(13);
    arbol.Agregar(14);
    arbol.Agregar(15);
    
    std::cout << "La cantidad de elementos en el arbol es: " << arbol.CantElem() << std::endl;
    arbol.ImprimirAsc();
    arbol.ImprimirNiveles(); 
    
    std::cout << "Hay 11 en el arbol? ";
    arbol.Buscar(11) ? std::cout << "Si" : std::cout << "No";

    std::cout << "\nEliminando el numero 11: " << std::endl;
    arbol.Eliminar(11);
    arbol.ImprimirNiveles();

    std::cout << "\nEliminando el numero 1: " << std::endl;
    arbol.Eliminar(1);
    arbol.ImprimirNiveles();

    std::cout << "\nEliminando el numero 6: " << std::endl;
    arbol.Eliminar(6);
    arbol.ImprimirNiveles();

    std::cout << "\nEliminando el numero 7: " << std::endl;
    arbol.Eliminar(7);
    arbol.ImprimirNiveles();

    std::cout << "\nEliminando el numero 5: " << std::endl;
    arbol.Eliminar(5);
    arbol.ImprimirNiveles();

    std::cout << "Vaciando el arbol: " << std::endl;
    arbol.Vaciar();
    std::cout << "Elementos en el arbol: " << arbol.CantElem() << std::endl;
    
    /*std::cout << "Rellendando el arbol de 1 a 15: " << std::endl;
    for(int i = 1 ; i <= 15 ; ++i){
        arbol.Agregar(i);
        arbol.ImprimirNiveles();
    }
    arbol.ImprimirAsc();
    arbol.ImprimirDes();
    arbol.ImprimirNiveles();*/


    return 0;
}


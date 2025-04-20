#include <iostream>
#include "../Headers/ArbolAVL.hpp"

using namespace std;

int main() {
    ArbolAVL<int> arbol;

    cout << "=== Agregando nodos al Arbol AVL ===\n";
    arbol.Agregar(30);
    arbol.Agregar(20);
    arbol.Agregar(40);
    arbol.Agregar(10);
    arbol.Agregar(25);
    arbol.Agregar(35);
    arbol.Agregar(50);
    arbol.Agregar(5);
    arbol.Agregar(15);
    cout << "30, 20, 40, 10, 25, 35, 50, 5, 15" << endl;

    cout << "\n=== Imprimir Ascendente (In-Orden) ===\n";
    arbol.ImprimirAsc();

    cout << "\n=== Imprimir Descendente ===\n";
    arbol.ImprimirDec();

    cout << "\n=== Imprimir por Niveles ===\n";
    arbol.ImprimirNiveles();

    cout << "\n=== Buscar ===\n";
    cout << "¿Está el 25? " << (arbol.Buscar(25) ? "Sí" : "No") << endl;
    cout << "¿Está el 99? " << (arbol.Buscar(99) ? "Sí" : "No") << endl;

    cout << "\n=== Número de nodos: " << arbol.NumNodos() << endl;
    cout << "Altura del árbol: " << arbol.AlturaArbol() << endl;

    cout << "\n=== Eliminar nodos ===\n";
    arbol.Eliminar(10);
    arbol.Eliminar(30); // Raíz
    arbol.Eliminar(5);
    cout << "10, 30, 5" << endl;

    cout << "\n=== Imprimir Ascendente después de eliminar ===\n";
    arbol.ImprimirAsc();

    cout << "\n=== Vaciar el árbol ===\n";
    arbol.Vaciar();
    cout << "Número de nodos después de vaciar: " << arbol.NumNodos() << std::endl;

    return 0;}


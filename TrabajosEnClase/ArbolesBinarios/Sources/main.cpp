#include <iostream>
#include "../Headers/ArbolBB.h"

using namespace std;

int main() {
    ArbolBB<int> Arbol, arbol;

    // Agregamos algunos valores al árbol
    Arbol.Agregar(35);
    Arbol.Agregar(20);
    Arbol.Agregar(10);
    Arbol.Agregar(29);
    Arbol.Agregar(52);
    Arbol.Agregar(41);
    Arbol.Agregar(115);
    Arbol.Agregar(95);

    // Realizamos una copia del árbol
    arbol = Arbol;

    // Imprimimos el árbol en distintos órdenes
    cout << "Árbol en niveles: ";
    Arbol.ImprimirNiveles();  // Imprimir el árbol por niveles
    cout << endl;

    cout << "Árbol en orden ascendente: ";
    Arbol.ImprimirAsc();      // Imprimir el árbol en orden ascendente
    cout << endl;

    cout << "Árbol en orden descendente: ";
    Arbol.ImprimirDec();      // Imprimir el árbol en orden descendente
    cout << endl;

    // Eliminamos un valor (por ejemplo, 52)
    cout << "Eliminando 52..." << endl;
    Arbol.Eliminar(52);

    // Imprimimos el árbol después de eliminar el valor 52
    cout << "Árbol en niveles después de eliminar 52: ";
    Arbol.ImprimirNiveles();
    cout << endl;

    cout << "Árbol en orden ascendente después de eliminar 52: ";
    Arbol.ImprimirAsc();
    cout << endl;

    cout << "Árbol en orden descendente después de eliminar 52: ";
    Arbol.ImprimirDec();
    cout << endl;

    // Eliminamos otro valor (por ejemplo, 10)
    cout << "Eliminando 10..." << endl;
    Arbol.Eliminar(10);

    // Imprimimos el árbol después de eliminar el valor 10
    cout << "Árbol en niveles después de eliminar 10: ";
    Arbol.ImprimirNiveles();
    cout << endl;

    cout << "Árbol en orden ascendente después de eliminar 10: ";
    Arbol.ImprimirAsc();
    cout << endl;

    cout << "Árbol en orden descendente después de eliminar 10: ";
    Arbol.ImprimirDec();
    cout << endl;

    // Imprimimos el árbol copiado
    cout << "\nCopia del primer árbol (sin cambios): " << endl;
    arbol.ImprimirNiveles();

    return 0;
}


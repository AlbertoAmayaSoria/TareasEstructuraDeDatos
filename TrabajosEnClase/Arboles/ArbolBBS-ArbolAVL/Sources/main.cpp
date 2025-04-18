#include <iostream>
#include "../Headers/ArbolAVL.hpp"

using namespace std;

int main() {
    ArbolAVL<int> Arbol, arbol;

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

    // Impresión de órdenes
    /*cout << "Árbol en niveles: ";
    Arbol.ImprimirNiveles();  
    cout << endl;

    cout << "Árbol en orden ascendente: ";
    Arbol.ImprimirAsc();      
    cout << endl;

    cout << "Árbol en orden descendente: ";
    Arbol.ImprimirDec();      
    cout << endl;

    // Buscar elementos
    cout << "\nBuscando valores en el árbol:" << endl;
    cout << "¿Existe 29? " << (Arbol.Buscar(29) ? "Sí" : "No") << endl;
    cout << "¿Existe 100? " << (Arbol.Buscar(100) ? "Sí" : "No") << endl;

    // Número de nodos
    cout << "Número de nodos en el árbol: " << Arbol.NumeroNodos() << endl;

    // Obtener el valor mayor y menor
    cout << "Valor mayor en el árbol: " << Arbol.ObtenerMayor() << endl;
    cout << "Valor menor en el árbol: " << Arbol.ObtenerMenor() << endl;

    // Altura del árbol
    cout << "Altura del árbol: " << Arbol.AlturaArbol() << endl;

    // Eliminación de nodos
    cout << "\nEliminando 52..." << endl;
    Arbol.Eliminar(52);
    cout << "Árbol en niveles después de eliminar 52: ";
    Arbol.ImprimirNiveles();
    cout << endl;

    cout << "\nEliminando 10..." << endl;
    Arbol.Eliminar(10);
    cout << "Árbol en niveles después de eliminar 10: ";
    Arbol.ImprimirNiveles();
    cout << endl;

    // Podar un subárbol
    cout << "\nPodando subárbol con raíz 20..." << endl;
    Arbol.Podar(20);
    cout << "Árbol en niveles después de podar 20: ";
    Arbol.ImprimirNiveles();
    cout << endl;

    // Vaciar el árbol
    cout << "\nVaciando el árbol completo..." << endl;
    Arbol.Vaciar();
    cout << "Árbol en niveles después de vaciar: ";
    Arbol.ImprimirNiveles();
    cout << endl;
    cout << "¿Está vacío? " << (Arbol.NumeroNodos() == 0 ? "Sí" : "No") << endl;

    // Mostramos la copia del árbol original (debería conservar su estado original)
    cout << "\nCopia del árbol original (sin cambios): ";
    arbol.ImprimirNiveles();
    cout << endl;*/

    return 0;
}


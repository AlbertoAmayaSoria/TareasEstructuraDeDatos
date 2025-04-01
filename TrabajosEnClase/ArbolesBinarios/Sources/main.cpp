#include <iostream>
#include "../Headers/ArbolBB.h"

using namespace std;

int main()
{
    ArbolBB<int> Arbol, arbol;

    Arbol.Agregar(35);
    Arbol.Agregar(20);
    Arbol.Agregar(10);
    Arbol.Agregar(29);
    Arbol.Agregar(52);
    Arbol.Agregar(41);
    Arbol.Agregar(115);
    Arbol.Agregar(95);

    arbol = Arbol;
    
    Arbol.ImprimirNiveles();

    cout << endl;

    Arbol.ImprimirAsc();
    
    cout << endl;
    
    Arbol.ImprimirDec();

    cout << endl;

    Arbol.Podar(52);
    Arbol.ImprimirNiveles();

    cout << "\nCopia del primer arbol: " << endl;

    arbol.ImprimirNiveles();

}

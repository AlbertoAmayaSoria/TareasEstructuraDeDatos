#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    Grafica g;

    g.Agregar('a');
    g.Agregar('b');
    g.Agregar('c');
    g.Agregar('d');

    g.Agregar('a','b');
    g.Agregar('a','c');
    g.Agregar('b','c');
    g.Agregar('b','d');
    g.Agregar('c','d');

    g.Imprimir();


    return 0;
}

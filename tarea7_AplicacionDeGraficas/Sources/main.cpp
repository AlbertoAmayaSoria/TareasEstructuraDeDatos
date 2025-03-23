#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    Grafica g, f, i, j;
    
    // Agregar nodos y aristas
    g.Agregar('1');
    g.Agregar('2');
    g.Agregar('3');
    g.Agregar('4');
    
    g.Agregar('1', '2');
    g.Agregar('2', '4');
    g.Agregar('4', '3');
    g.Agregar('3', '1');
    
    // Imprimir la gráfica original
    cout << "Gráfica 1 original:" << endl;
    g.Imprimir();

    g.CaminoEuleriano();

    // Agregar nodos y aristas
    f.Agregar('a');
    f.Agregar('b');
    f.Agregar('c');
    f.Agregar('d');
    //f.Agregar('e');
    
    f.Agregar('a', 'b');
    f.Agregar('b', 'd');
    f.Agregar('d', 'c');
    f.Agregar('c', 'a');
    
    // Imprimir la gráfica original
    cout << "\nGráfica 2 original:" << endl;
    f.Imprimir();

    f.CaminoEuleriano();

    // Agregar nodos y aristas
    i.Agregar('a');
    i.Agregar('b');
    i.Agregar('c');
    i.Agregar('d');
    i.Agregar('e');
    
    i.Agregar('a', 'b');
    i.Agregar('a', 'c');
    i.Agregar('b', 'd');
    i.Agregar('d', 'c');
    i.Agregar('c', 'a');
    
    // Imprimir la gráfica original
    cout << "\nGráfica 3 original:" << endl;
    i.Imprimir();

    i.CaminoEuleriano();

    // Agregar nodos y aristas
    j.Agregar('a');
    j.Agregar('b');
    j.Agregar('c');
    j.Agregar('d');
    j.Agregar('e');
    
    j.Agregar('a', 'b');
    j.Agregar('b', 'd');
    j.Agregar('d', 'c');
    j.Agregar('c', 'a');
    
    // Imprimir la gráfica original
    cout << "\nGráfica 4 original:" << endl;
    j.Imprimir();

    j.CaminoEuleriano();

     
    
    return 0;
}


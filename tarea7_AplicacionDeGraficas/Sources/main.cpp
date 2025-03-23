#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    Grafica g;
    
    // Agregar nodos y aristas
    g.Agregar('1');
    g.Agregar('2');
    g.Agregar('3');
    g.Agregar('4');
    
    g.Agregar('1', '2');
    g.Agregar('2', '3');
    g.Agregar('3', '4');
    g.Agregar('4', '1');
    
    // Imprimir la gráfica original
    cout << "Gráfica original:" << endl;
    g.Imprimir();
    
    // Crear una copia del grafo
    Grafica copia_grafo = g;
    
    // Verificar y encontrar el camino Euleriano en la copia
    cout << "Camino Euleriano en la copia:" << endl;
    copia_grafo.CaminoEuleriano();
    
    // Imprimir la gráfica original para verificar que no fue modificada
    cout << "\nGráfica original después del cálculo del camino Euleriano:" << endl;
    g.Imprimir();
    
    return 0;
}


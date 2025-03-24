#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    // Grafo 1: Grafo con camino Euleriano (todos los grados pares, grafo conexo)
    Grafica g;
    g.Agregar('1');
    g.Agregar('2');
    g.Agregar('3');
    g.Agregar('4');
    
    g.Agregar('1', '2');
    g.Agregar('2', '4');
    g.Agregar('4', '3');
    g.Agregar('3', '1');
    
    cout << "Gráfica 1 original (camino Euleriano):" << endl;
    g.Imprimir();
    g.CaminoEuleriano();
    
    // Grafo 2: Grafo con camino Euleriano (todos los grados pares, grafo conexo)
    Grafica f;
    f.Agregar('a');
    f.Agregar('b');
    f.Agregar('c');
    f.Agregar('d');
    
    f.Agregar('a', 'b');
    f.Agregar('b', 'd');
    f.Agregar('d', 'c');
    f.Agregar('c', 'a');
    
    cout << "\nGráfica 2 original (camino Euleriano):" << endl;
    f.Imprimir();
    f.CaminoEuleriano();
    
    // Grafo 3: Grafo con camino Euleriano (todos los grados pares, grafo conexo)
    Grafica i;
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
    
    cout << "\nGráfica 3 original (camino Euleriano):" << endl;
    i.Imprimir();
    i.CaminoEuleriano();
    
    // Grafo 4: Grafo con camino Euleriano (todos los grados pares, grafo conexo)
    Grafica j;
    j.Agregar('a');
    j.Agregar('b');
    j.Agregar('c');
    j.Agregar('d');
    j.Agregar('e');
    
    j.Agregar('a', 'b');
    j.Agregar('b', 'd');
    j.Agregar('d', 'c');
    j.Agregar('c', 'a');
    
    cout << "\nGráfica 4 original (camino Euleriano):" << endl;
    j.Imprimir();
    j.CaminoEuleriano();
    
    // Grafo 5: Grafo sin camino Euleriano (grados impares)
    Grafica k;
    k.Agregar('1');
    k.Agregar('2');
    k.Agregar('3');
    
    k.Agregar('1', '2');
    k.Agregar('2', '3');
    
    cout << "\nGráfica 5 (sin camino Euleriano):" << endl;
    k.Imprimir();
    k.CaminoEuleriano();
    
    // Grafo 6: Grafo desconectado (sin camino Euleriano)
    Grafica l;
    l.Agregar('1');
    l.Agregar('2');
    l.Agregar('3');
    l.Agregar('4');
    
    l.Agregar('1', '2');
    // No hay conexión con 3 y 4
    
    cout << "\nGráfica 6 (desconectada, sin camino Euleriano):" << endl;
    l.Imprimir();
    l.CaminoEuleriano();
    
    // Grafo 7: Grafo con un solo vértice
    Grafica m;
    m.Agregar('1');
    
    cout << "\nGráfica 7 (un solo vértice):" << endl;
    m.Imprimir();
    m.CaminoEuleriano();
    
    // Grafo 8: Grafo con ciclo impar (sin camino Euleriano)
    Grafica n;
    n.Agregar('1');
    n.Agregar('2');
    n.Agregar('3');
    
    n.Agregar('1', '2');
    n.Agregar('2', '3');
    n.Agregar('3', '1');
    
    cout << "\nGráfica 8 (ciclo impar, sin camino Euleriano):" << endl;
    n.Imprimir();
    n.CaminoEuleriano();
    
    return 0;
}


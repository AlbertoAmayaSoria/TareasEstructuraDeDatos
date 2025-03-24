#include <iostream>
#include <chrono>
#include <thread>
#include "../Headers/Grafica.hpp"

using namespace std;

void LimpiarPantalla();

void DetenerImpresion(int milisegundos);

int main()
{

    LimpiarPantalla();

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
    g.CaminoEuleriano();  // Este grafo debe tener un camino Euleriano
   
    DetenerImpresion(8000);
    LimpiarPantalla();

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
    
    cout << "Gráfica 2 original (camino Euleriano):" << endl;
    f.Imprimir();
    f.CaminoEuleriano();  // Este grafo debe tener un camino Euleriano
    
    DetenerImpresion(8000);
    LimpiarPantalla();

    // Grafo 3: Grafo con camino Euleriano (todos los grados pares, grafo conexo)
    Grafica i;
    i.Agregar('a');
    i.Agregar('b');
    i.Agregar('c');
    i.Agregar('d');
    
    i.Agregar('a', 'b');
    i.Agregar('b', 'c');
    i.Agregar('c', 'd');
    i.Agregar('d', 'a');
    
    cout << "Gráfica 3 original (camino Euleriano):" << endl;
    i.Imprimir();
    i.CaminoEuleriano();  // Este grafo también tiene un camino Euleriano
    
    DetenerImpresion(8000);
    LimpiarPantalla();

    // Grafo 4: Grafo sin camino Euleriano (grados impares)
    Grafica k;
    k.Agregar('1');
    k.Agregar('2');
    k.Agregar('3');
    
    k.Agregar('1', '2');
    k.Agregar('2', '3');
    
    cout << "Gráfica 4 (sin camino Euleriano, tiene vértices con grado impar):" << endl;
    k.Imprimir();
    k.CaminoEuleriano();  // Este grafo no tiene un camino Euleriano

    return 0;
}

void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux y otros sistemas Unix
#endif
}

void DetenerImpresion(int milisegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milisegundos));  // Pausa en milisegundos
}

#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    Grafica g, m;

    g.Agregar('a');
    g.Agregar('b');
    g.Agregar('c');
    g.Agregar('d');

    //std::cout << "";
    g.Agregar('a','b');
    g.Agregar('a','c');
    g.Agregar('b','c');
    g.Agregar('b','d');
    g.Agregar('c','d');

    g.Imprimir();

    std::cout << "Copia de la grafica: " << std::endl;

    m = g;

    m.Imprimir();

    std::cout << "Número de Nodos: " << g.ObtenerNumNodos() << std::endl;
    
    std::cout << "Eliminar el nodo b: " << std::endl;

    g.Eliminar('b');
    
    g.Imprimir();

    std::cout << "Número de aristas: " << std::endl;

    std::cout << m.ObtenerNumAristas() << std::endl;

    std::cout << "Número de nodos: " << std::endl;

    std::cout << m.ObtenerNumNodos() << std::endl;

    //Grafica m;

    //m = g;

    //std::cout << "Copia de la grafica: " << std::endl;

    //m.Imprimir();


    return 0;
}

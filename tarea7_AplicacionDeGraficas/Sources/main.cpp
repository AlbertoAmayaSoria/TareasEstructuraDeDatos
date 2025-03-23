#include <iostream>
#include "../Headers/Grafica.hpp"

using namespace std;

int main()
{
    Grafica g, m;

    g.Agregar('1');
    g.Agregar('2');
    g.Agregar('3');
    g.Agregar('4');
    //g.Agregar('5');
    //g.Agregar('5');

    //std::cout << "";
    g.Agregar('1','2');
    //g.Agregar('1','1');
    g.Agregar('1','3');
    //g.Agregar('1','5');
    //g.Agregar('2','3');
    g.Agregar('2','4');
    g.Agregar('3','4');
    //g.Agregar('4','5');

    g.Imprimir();  

    std::cout << "Número de Nodos: " << g.ObtenerNumNodos() << std::endl;

    m = g;
 
    std::cout << "Grado del nodo 1: " << m.ObtenerGrado('1') << std::endl;
    std::cout << "Grado del nodo 2: " << m.ObtenerGrado('2') << std::endl;
    std::cout << "Grado del nodo 3: " << m.ObtenerGrado('3') << std::endl;
    std::cout << "Grado del nodo 4: " << m.ObtenerGrado('4') << std::endl;
    //std::cout << "Grado del nodo 5: " << m.ObtenerGrado('5') << std::endl;

    g.CaminoEuleriano(); 

    return 0;
}

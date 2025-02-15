/*
Descripción: 
Autor: Amaya Soria Angel Alberto
Fecha: 04 de Febrero de 2025
*/

#include <iostream>
#include "../Headers/Expresion.hpp"

using namespace std;

int main()
{
    try {
        
        Expresion exp("+1");
        exp.imprimirExpresion();
        std::cout << "Resultado: " << exp.evaluar() << std::endl;

    } catch(const char *mensaje) {
        cerr << "\n" << mensaje << endl;
    }

    cout << "Presiona ENTER para continuar...";
    cin.get();
    return 0;
}


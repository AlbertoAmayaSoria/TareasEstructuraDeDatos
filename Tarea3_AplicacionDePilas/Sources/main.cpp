/*
Descripci�n: 
Autor: Amaya Soria Angel Alberto
Fecha: 04 de Febrero de 2025
*/



#include "../Headers/Expresion.hpp"
#include "../Headers/CapturaSegura.hpp"
#include <iostream>

int main() { 
    try { 
        Expresion exp;  // Crear un objeto de la clase Expresion
        exp.capturarExpresion();  // Capturar la expresi�n desde la clase
        exp.imprimirExpresion();  // Imprimir la expresi�n infija y posfija
        std::cout << "Resultado: " << exp.evaluar() << std::endl;  // Evaluar la expresi�n
    
    } catch (const std::runtime_error& e) {
        std::cerr << "\nSe ha producido un error: " << e.what() << std::endl;
    }

    std::cout << "Presiona ENTER para continuar...";
    std::cin.get();
    return 0;
}


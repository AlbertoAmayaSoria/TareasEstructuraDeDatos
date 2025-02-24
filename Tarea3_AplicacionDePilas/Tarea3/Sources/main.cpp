/*
Descripción:este código permite:
            Leer una expresión matemática de la entrada del usuario.
            Validar la expresión para asegurar que esté bien formada.
            Convertirla a notación posfija para facilitar su evaluación.
            Evaluar la expresión para obtener su resultado. 

Autor: Amaya Soria Angel Alberto && Altamirano Ocejo Michell Berenice 
Fecha: 15 de Febrero de 2025
*/



#include "../Headers/Expresion.hpp"
#include "../Headers/CapturaSegura.hpp"
#include <iostream>

int main() { 
    try { 
        Expresion exp;  // Crear un objeto de la clase Expresion
        exp.capturarExpresion();  // Capturar la expresión desde la clase
        exp.imprimirExpresion();  // Imprimir la expresión infija y posfija
        std::cout << "Resultado: " << exp.evaluar() << std::endl;  // Evaluar la expresión
    
    } catch (const std::runtime_error& e) {
        std::cerr << "\nSe ha producido un error: " << e.what() << std::endl;
    }

    std::cout << "Presiona ENTER para continuar...";
    std::cin.get();
    return 0;
}


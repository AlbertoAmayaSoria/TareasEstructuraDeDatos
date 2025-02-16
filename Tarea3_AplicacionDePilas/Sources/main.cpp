/*
Descripci�n:este c�digo permite:
            Leer una expresi�n matem�tica de la entrada del usuario.
            Validar la expresi�n para asegurar que est� bien formada.
            Convertirla a notaci�n posfija para facilitar su evaluaci�n.
            Evaluar la expresi�n para obtener su resultado. 

Autor: Amaya Soria Angel Alberto && Altamirano Ocejo Michell Berenice 
Fecha: 15 de Febrero de 2025
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


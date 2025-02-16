#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <string>
#include <stdexcept>
#include "../Headers/CapturaSegura.hpp"

const char listaSimbolos[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '.', '+', '-', '*', '/', '^',
    '(', ')', '[', ']', '{', '}'
};

const unsigned NumSimbolos = 22;

class Expresion {
public:
    Expresion();
    //Expresion(std::string expresion);
    void capturarExpresion();
    void imprimirExpresion();
    int evaluar();

private:
    std::string infija;
    std::string posfija;
    bool valida;

    int prioridad(char operador);
    bool validarExpresion();
    std::string convertirAPosfija();
    bool esOperador(char c);
};

#endif // EXPRESION_HPP_INCLUDED


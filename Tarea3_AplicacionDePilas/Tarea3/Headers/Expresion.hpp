#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <string>
#include <stdexcept>
#include "../Headers/CapturaSegura.hpp"

// Definición de los símbolos permitidos en una expresión matemática
const char listaSimbolos[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',  // Dígitos
    '.', '+', '-', '*', '/', '^',  // Operadores y punto decimal
    '(', ')', '[', ']', '{', '}'  // Paréntesis y corchetes
};

// Número total de símbolos permitidos
const unsigned NumSimbolos = 22;

class Expresion {
public:
    // Constructor de la clase Expresion
    Expresion();
    
    /**
     * Método para capturar la expresión matemática desde la entrada estándar.
     * Utiliza la clase CapturaSegura para asegurar que solo se ingresen símbolos permitidos.
     */
    void capturarExpresion();

    /**
     * Método para imprimir la expresión infija y su conversión a notación posfija.
     * Primero valida la expresión y luego realiza la conversión y muestra ambos resultados.
     */
    void imprimirExpresion();

    /**
     * Método para evaluar la expresión en notación posfija.
     * Se realiza la evaluación utilizando una pila para manejar los operandos.
     * @return El resultado de la evaluación de la expresión.
     * @throws std::runtime_error si la expresión es inválida o si ocurre un error durante la evaluación.
     */
    int evaluar();

private:
    std::string infija;  // Expresión matemática en notación infija (entrada del usuario)
    std::string posfija; // Expresión matemática en notación posfija (resultado de la conversión)
    bool valida;         // Indica si la expresión es válida o no

    /**
     * Método para determinar la prioridad de un operador.
     * La prioridad se utiliza en la conversión a notación posfija.
     * @param operador El operador para evaluar.
     * @return Un valor entero que representa la prioridad del operador.
     */
    int prioridad(char operador);

    /**
     * Método para validar la expresión matemática.
     * Verifica que no haya errores de sintaxis, como paréntesis desbalanceados
     * o operadores en posiciones incorrectas.
     * @return true si la expresión es válida, false en caso contrario.
     * @throws std::runtime_error si la expresión no es válida.
     */
    bool validarExpresion();

    /**
     * Método para convertir la expresión infija a notación posfija.
     * Se utiliza el algoritmo de Shunting Yard para realizar la conversión.
     * @return La expresión matemática en notación posfija.
     */
    std::string convertirAPosfija();

    /**
     * Método para verificar si un carácter es un operador válido.
     * Los operadores válidos incluyen +, -, *, / y ^ (exponenciación).
     * @param c El carácter a verificar.
     * @return true si el carácter es un operador válido, false en caso contrario.
     */
    bool esOperador(char c);
};

#endif // EXPRESION_HPP_INCLUDED



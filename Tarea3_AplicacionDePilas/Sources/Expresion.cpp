#include "../Headers/Expresion.hpp"
#include <iostream>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <cmath>  // Para usar la función pow (potencia)
#include "../Headers/Pila.hpp"
#include "../Headers/CapturaSegura.hpp"

// Implementación de la clase Expresion

// Constructor de la clase Expresion
Expresion::Expresion() : infija(""), posfija(""), valida(true) {}

// Método para capturar una expresión matemática desde la entrada del usuario
void Expresion::capturarExpresion() {
    std::cout << "Introduce una expresión matemática: ";
    infija = CapturaSegura<std::string, std::string>().TextoPermitido(listaSimbolos, NumSimbolos);  // Utiliza TextoPermitido para capturar la expresión.

    // Validar la expresión después de capturarla
    if (!validarExpresion()) {
        throw std::runtime_error("Expresión inválida.");
    }
}

// Método para imprimir la expresión infija y su conversión a posfija
void Expresion::imprimirExpresion() {
    // Validar antes de convertir a posfija
    if (!validarExpresion()) {
        throw std::runtime_error("Expresión inválida.");
    }

    posfija = convertirAPosfija();
    std::cout << "Expresion Infija: " << infija << std::endl;
    std::cout << "Expresion Posfija: " << posfija << std::endl;
}

// Método para evaluar la expresión matemática en notación posfija
int Expresion::evaluar() {
    if (!valida) {
        throw std::runtime_error("No se puede evaluar una expresión inválida.");
    }

    posfija = convertirAPosfija();
    Pila pilaOperandos;
    std::stringstream ss(posfija);
    std::string elemento;

    // Evaluación de la expresión posfija
    while (ss >> elemento) {
        if (isdigit(elemento[0]) || (elemento[0] == '-' && elemento.size() > 1)) {
            pilaOperandos.Apilar(std::stoi(elemento));  // Si es número, apilarlo
        } else {
            if (pilaOperandos.ObtenerCantElem() < 2) {
                throw std::runtime_error("Error en la evaluación: Expresión incorrecta.");
            }

            int operando2 = pilaOperandos.ObtenerTope();  // Obtener el segundo operando
            pilaOperandos.Desapilar();
            int operando1 = pilaOperandos.ObtenerTope();  // Obtener el primer operando
            pilaOperandos.Desapilar();

            // Aplicar el operador correspondiente
            switch (elemento[0]) {
                case '+': pilaOperandos.Apilar(operando1 + operando2); break;
                case '-': pilaOperandos.Apilar(operando1 - operando2); break;
                case '*': pilaOperandos.Apilar(operando1 * operando2); break;
                case '/':
                    if (operando2 == 0) throw std::runtime_error("Error: División por cero.");
                    pilaOperandos.Apilar(operando1 / operando2);
                    break;
                case '^': 
                    pilaOperandos.Apilar(static_cast<int>(std::pow(operando1, operando2)));  // Exponenciación
                    break;
                default:
                    throw std::runtime_error("Operador desconocido.");
            }
        }
    }

    // Verificar que solo quede un elemento en la pila (el resultado)
    if (pilaOperandos.ObtenerCantElem() != 1) {
        throw std::runtime_error("Error en la evaluación: Expresión incorrecta.");
    }

    return pilaOperandos.ObtenerTope();  // Devolver el resultado
}

// Método para determinar la prioridad de un operador
int Expresion::prioridad(char operador) {
    if (operador == '+' || operador == '-') return 1;  // Baja prioridad
    if (operador == '*' || operador == '/') return 2;  // Prioridad media
    if (operador == '^') return 3;  // Alta prioridad (exponentes)
    return 0;  // Sin prioridad
}

// Método para validar la expresión matemática
bool Expresion::validarExpresion() {
    Pila<char> operadores;
    int balance = 0;
    bool ultimoFueOperador = true;

    // Recorrer cada carácter de la expresión
    for (size_t i = 0; i < infija.size(); ++i) {
        char c = infija[i];

        // Si es un dígito, no se espera un operador después
        if (std::isdigit(c)) {
            ultimoFueOperador = false;
        } 
        else if (c == '(' || c == '[' || c == '{') {
            operadores.Apilar(c);  // Apilar el paréntesis de apertura
            balance++;
            ultimoFueOperador = true;
        } 
        else if (c == ')' || c == ']' || c == '}') {
            if (operadores.EstaVacia()) {
                throw std::runtime_error("Error: Paréntesis de cierre sin apertura correspondiente.");
            }
            char tope = operadores.ObtenerTope();
            if ((c == ')' && tope != '(') || (c == ']' && tope != '[') || (c == '}' && tope != '{')) {
                throw std::runtime_error("Error: Paréntesis desbalanceados.");
            }
            operadores.Desapilar();
            balance--;
        } 
        else if (esOperador(c)) {
            if (ultimoFueOperador && (c == '+' || c == '-')) {
                // Si es un operador unario, se permite
                ultimoFueOperador = false;
            } else if (ultimoFueOperador) {
                throw std::runtime_error("Error: Dos operadores seguidos o mal posicionados.");
            }
            ultimoFueOperador = true;
        } 
        else {
            throw std::runtime_error("Error: Caracter inválido en la expresión.");
        }
    }

    // Verificar que los paréntesis estén balanceados
    if (!operadores.EstaVacia() || balance != 0) {
        throw std::runtime_error("Error: Paréntesis sin cerrar.");
    }

    return true;  // La expresión es válida
}

// Método para convertir la expresión infija a notación posfija (algoritmo de Shunting Yard)
std::string Expresion::convertirAPosfija() {
    std::stringstream salida;
    Pila<char> pilaOperadores;
    bool ultimoFueNumero = false;

    // Recorrer cada carácter de la expresión infija
    for (size_t i = 0; i < infija.size(); ++i) {
        char caracter = infija[i];

        if (std::isdigit(caracter)) {
            if (ultimoFueNumero) {
                salida << caracter;  // Continuar número
            } else {
                salida << " " << caracter;  // Empezar un número
                ultimoFueNumero = true;
            }
        } 
        else {
            ultimoFueNumero = false;

            if ((caracter == '-' || caracter == '+') && (i == 0 || infija[i - 1] == '(' || esOperador(infija[i - 1]))) {
                salida << " 0";  // Operador unario, agregar 0 antes
            }

            // Si es operador, manejar la prioridad y apilar según el caso
            if (esOperador(caracter)) {
                while (!pilaOperadores.EstaVacia() && prioridad(pilaOperadores.ObtenerTope()) >= prioridad(caracter)) {
                    salida << " " << pilaOperadores.ObtenerTope();
                    pilaOperadores.Desapilar();
                }
                pilaOperadores.Apilar(caracter);
            } 
            else if (caracter == '(' || caracter == '{' || caracter == '[') {
                pilaOperadores.Apilar(caracter);  // Apilar paréntesis de apertura
            } 
            else if (caracter == ')' || caracter == '}' || caracter == ']') {
                // Desapilar hasta encontrar el paréntesis de apertura
                while (!pilaOperadores.EstaVacia() && pilaOperadores.ObtenerTope() != '(' && pilaOperadores.ObtenerTope() != '{' && pilaOperadores.ObtenerTope() != '[') {
                    salida << " " << pilaOperadores.ObtenerTope();
                    pilaOperadores.Desapilar();
                }
                pilaOperadores.Desapilar();  // Eliminar paréntesis de apertura
            }
        }
    }

    // Desapilar el resto de los operadores
    while (!pilaOperadores.EstaVacia()) {
        salida << " " << pilaOperadores.ObtenerTope();
        pilaOperadores.Desapilar();
    }

    return salida.str();  // Devolver la expresión en notación posfija
}

// Método para verificar si un carácter es un operador válido
bool Expresion::esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');  // Operadores permitidos
}


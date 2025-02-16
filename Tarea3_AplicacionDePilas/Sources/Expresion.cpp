#include "../Headers/Expresion.hpp"
#include <iostream>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include "../Headers/Pila.hpp"
#include "../Headers/CapturaSegura.hpp"


// Implementación de la clase Expresion
Expresion::Expresion() : infija(""), posfija(""), valida(true) {}


void Expresion::capturarExpresion() {
    std::cout << "Introduce una expresión matemática: ";
    infija = CapturaSegura<std::string, std::string>().TextoPermitido(listaSimbolos, NumSimbolos);  // Utilizar TextoPermitido para capturar la expresión.

    // Validar la expresión después de capturarla
    if (!validarExpresion()) {
        throw std::runtime_error("Expresión inválida.");
    }
}

void Expresion::imprimirExpresion() {
    // Validar antes de convertir a posfija
    if (!validarExpresion()) {
        throw std::runtime_error("Expresión inválida.");
    }

    posfija = convertirAPosfija();
    std::cout << "Expresion Infija: " << infija << std::endl;
    std::cout << "Expresion Posfija: " << posfija << std::endl;
}

int Expresion::evaluar() {
    if (!valida) {
        throw std::runtime_error("No se puede evaluar una expresión inválida.");
    }

    posfija = convertirAPosfija();
    Pila pilaOperandos;
    std::stringstream ss(posfija);
    std::string elemento;

    while (ss >> elemento) {
        if (isdigit(elemento[0]) || (elemento[0] == '-' && elemento.size() > 1)) {
            pilaOperandos.Apilar(std::stoi(elemento));
        } else {
            if (pilaOperandos.ObtenerCantElem() < 2) {
                throw std::runtime_error("Error en la evaluación: Expresión incorrecta.");
            }

            int operando2 = pilaOperandos.ObtenerTope();
            pilaOperandos.Desapilar();
            int operando1 = pilaOperandos.ObtenerTope();
            pilaOperandos.Desapilar();

            switch (elemento[0]) {
                case '+': pilaOperandos.Apilar(operando1 + operando2); break;
                case '-': pilaOperandos.Apilar(operando1 - operando2); break;
                case '*': pilaOperandos.Apilar(operando1 * operando2); break;
                case '/':
                    if (operando2 == 0) throw std::runtime_error("Error: División por cero.");
                    pilaOperandos.Apilar(operando1 / operando2);
                    break;
                default:
                    throw std::runtime_error("Operador desconocido.");
            }
        }
    }

    if (pilaOperandos.ObtenerCantElem() != 1) {
        throw std::runtime_error("Error en la evaluación: Expresión incorrecta.");
    }

    return pilaOperandos.ObtenerTope();
}

int Expresion::prioridad(char operador) {
    if (operador == '+' || operador == '-') return 1;
    if (operador == '*' || operador == '/') return 2;
    return 0;
}


bool Expresion::validarExpresion() {
    Pila<char> operadores;
    int balance = 0;
    bool ultimoFueOperador = true;

    for (size_t i = 0; i < infija.size(); ++i) {
        char c = infija[i];

        if (std::isdigit(c)) {
            ultimoFueOperador = false;
        } else if (c == '(' || c == '[' || c == '{') {
            operadores.Apilar(c);
            balance++;
            ultimoFueOperador = true;
        } else if (c == ')' || c == ']' || c == '}') {
            if (operadores.EstaVacia()) {
                throw std::runtime_error("Error: Paréntesis de cierre sin apertura correspondiente.");
            }
            char tope = operadores.ObtenerTope();
            if ((c == ')' && tope != '(') || (c == ']' && tope != '[') || (c == '}' && tope != '{')) {
                throw std::runtime_error("Error: Paréntesis desbalanceados.");
            }
            operadores.Desapilar();
            balance--;
        } else if (esOperador(c)) {
            if (ultimoFueOperador && (c == '+' || c == '-')) {
                // Es un operador unario
                ultimoFueOperador = false;
            } else if (ultimoFueOperador) {
                throw std::runtime_error("Error: Dos operadores seguidos o mal posicionados.");
            }
            ultimoFueOperador = true;
        } else {
            throw std::runtime_error("Error: Caracter inválido en la expresión.");
        }
    }

    if (!operadores.EstaVacia() || balance != 0) {
        throw std::runtime_error("Error: Paréntesis sin cerrar.");
    }

    return true;
}

std::string Expresion::convertirAPosfija() {
    std::stringstream salida;
    Pila<char> pilaOperadores;
    bool ultimoFueNumero = false;

    for (size_t i = 0; i < infija.size(); ++i) {
        char caracter = infija[i];

        if (std::isdigit(caracter)) {
            if (ultimoFueNumero) {
                salida << caracter; // Continuamos el número
            } else {
                salida << " " << caracter; // Empezamos un número
                ultimoFueNumero = true;
            }
        } 
        else {
            ultimoFueNumero = false;

            if ((caracter == '-' || caracter == '+') && (i == 0 || infija[i - 1] == '(' || esOperador(infija[i - 1]))) {
                salida << " 0";  // Manejo del operador unario, agregando el 0 antes
            }

            if (esOperador(caracter)) {
                while (!pilaOperadores.EstaVacia() && prioridad(pilaOperadores.ObtenerTope()) >= prioridad(caracter)) {
                    salida << " " << pilaOperadores.ObtenerTope();
                    pilaOperadores.Desapilar();
                }
                pilaOperadores.Apilar(caracter);
            } 
            else if (caracter == '(' || caracter == '{' || caracter == '[') {
                pilaOperadores.Apilar(caracter);
            } 
            else if (caracter == ')' || caracter == '}' || caracter == ']') {
                while (!pilaOperadores.EstaVacia() && pilaOperadores.ObtenerTope() != '(' && pilaOperadores.ObtenerTope() != '{' && pilaOperadores.ObtenerTope() != '[') {
                    salida << " " << pilaOperadores.ObtenerTope();
                    pilaOperadores.Desapilar();
                }
                pilaOperadores.Desapilar();  // Elimina el paréntesis o corchete de apertura
            }
        }
    }

    while (!pilaOperadores.EstaVacia()) {
        salida << " " << pilaOperadores.ObtenerTope();
        pilaOperadores.Desapilar();
    }

    return salida.str();
}

bool Expresion::esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}


#include <cctype>  // Para verificar si un carácter es un dígito
#include <sstream> // Para manejar cadenas de texto
#include <cmath>   // Para operaciones matemáticas
#include <stdexcept> // Para manejar errores con std::runtime_error

#include "../Headers/Expresion.hpp"
#include "../Headers/Pila.hpp"

/**
 * @brief Constructor por defecto que inicializa la expresión como vacía.
 * Este constructor se utiliza para crear una instancia de la clase Expresion sin proporcionar
 * una cadena de expresión infija inicialmente.
 */
Expresion::Expresion() : infija(""), posfija(""), valida(true) {}

/**
 * @brief Constructor que inicializa la expresión con una cadena.
 * 
 * Este constructor recibe una cadena de caracteres que representa una expresión infija
 * y llama a la función 'capturarExpresion' para almacenarla y validarla.
 * 
 * @param expresion La expresión infija a almacenar.
 */
Expresion::Expresion(std::string expresion) {
    capturarExpresion(expresion);
}

/**
 * @brief Captura la expresión infija y valida su formato.
 * 
 * Esta función almacena la expresión infija proporcionada, y valida su formato. Si se
 * detecta algún error durante la validación, la función lanzará una excepción y terminará
 * el programa.
 * 
 * @param expresion La expresión infija a almacenar.
 */
void Expresion::capturarExpresion(std::string expresion) {
    infija = expresion;
    try {
    valida = validarExpresion();
   
    } catch (const std::runtime_error& e) {
        std::cerr << "Se ha producido un error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);  // Termina el programa con un código de error si la validación falla
    }
}

/**
 * @brief Imprime la expresión infija y su versión posfija.
 * 
 * Esta función convierte la expresión infija a notación posfija y luego imprime ambas
 * expresiones (infija y posfija) en la salida estándar.
 */
void Expresion::imprimirExpresion() {
    // Convertimos la expresión infija a posfija antes de imprimir
    posfija = convertirAPosfija(); 

    std::cout << "Expresion Infija: " << infija << std::endl;
    std::cout << "Expresion Posfija: " << posfija << std::endl;
}

/**
 * @brief Evalúa la expresión infija convertida a posfija.
 * 
 * Esta función evalúa la expresión matemática en notación posfija utilizando una pila.
 * Si la expresión es válida, la función devuelve el resultado de la operación.
 * Si hay un error de sintaxis o de ejecución, se lanzará una excepción.
 * 
 * @throws std::runtime_error Si la expresión es inválida o tiene errores en su sintaxis.
 * @return int Resultado de la evaluación.
 */
int Expresion::evaluar() {
    if (!valida) {
        throw std::runtime_error("No se puede evaluar una expresión inválida.");
    }

    posfija = convertirAPosfija(); // Convertimos la expresión a notación posfija
    Pila<int> pilaOperandos;
    std::stringstream tokens(posfija);
    std::string token;

    while (tokens >> token) {
        // Si el token es un número, se apila
        if (isdigit(token[0])) {
            pilaOperandos.Apilar(std::stoi(token));
        } 
        // Si es un operador, se desapilan operandos y se realiza la operación
        else {
            if (pilaOperandos.ObtenerCantElem() < 2) {
                throw std::runtime_error("Error en la evaluación: Expresión incorrecta.");
            }
            int operando2 = pilaOperandos.ObtenerTope(); 
            pilaOperandos.Desapilar();
            int operando1 = pilaOperandos.ObtenerTope(); 
            pilaOperandos.Desapilar();

            switch (token[0]) {
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

    return pilaOperandos.ObtenerTope(); // Devuelve el resultado final
}

/**
 * @brief Determina la precedencia de un operador matemático.
 * 
 * Esta función asigna un nivel de precedencia a los operadores matemáticos. Los operadores
 * de multiplicación (*) y división (/) tienen mayor precedencia que los operadores de suma
 * (+) y resta (-).
 * 
 * @param operador El operador matemático (+, -, *, /).
 * @return int Nivel de precedencia (mayor valor indica mayor precedencia).
 */
int Expresion::prioridad(char operador) {
    if (operador == '+' || operador == '-') return 1;
    if (operador == '*' || operador == '/') return 2;
    return 0;
}

/**
 * @brief Valida la expresión infija para asegurarse de que tiene una sintaxis correcta.
 * 
 * Esta función revisa los paréntesis y corchetes de la expresión infija para garantizar
 * que estén balanceados. Si detecta algún error en la sintaxis, lanzará una excepción.
 * 
 * @return true Si la expresión es válida.
 * @return false Si la expresión es inválida.
 */
bool Expresion::validarExpresion() {
    // Inicializamos la pila para los paréntesis y corchetes
    Pila<char> Operadores;

    // Recorremos cada caracter de la cadena
    for (size_t i = 0; i < infija.size(); ++i) {  // Usamos 'infija' en lugar de 'Cadena'
        // Si encontramos un paréntesis o corchete de apertura, lo apilamos
        if (infija[i] == '{' || infija[i] == '[' || infija[i] == '(') {
            Operadores.Apilar(infija[i]);
        }

        // Si encontramos un paréntesis o corchete de cierre, verificamos su correspondencia
        if (!Operadores.EstaVacia() && 
            ((infija[i] == ')' && Operadores.ObtenerTope() == '(') ||
             (infija[i] == ']' && Operadores.ObtenerTope() == '[') ||
             (infija[i] == '}' && Operadores.ObtenerTope() == '{'))) {
            Operadores.Desapilar();  // Si hay coincidencia, desapilamos el último elemento
        } 
        // Si el carácter es un cierre y no hay apertura correspondiente, lanzamos un error
        else if (infija[i] == ')' || infija[i] == ']' || infija[i] == '}') {
            throw std::runtime_error("Operación mal escrita. Paréntesis o corchete de cierre sin apertura correspondiente.");
        }
    }

    // Al final, si quedan elementos en la pila, significa que hay paréntesis o corchetes sin cerrar
    if (!Operadores.EstaVacia()) {
        throw std::runtime_error("Operación mal escrita. Paréntesis o corchete sin cerrar.");
    }

    // Si todo está balanceado, la expresión es correcta
    std::cout << "Expresión correcta." << std::endl;
    return true;
}

/**
 * @brief Convierte una expresión en notación infija a notación posfija (notación polaca inversa).
 * 
 * Utiliza el algoritmo de Shunting Yard para reorganizar los operadores y operandos. 
 * La notación posfija facilita la evaluación de la expresión sin necesidad de paréntesis.
 * 
 * @return std::string La expresión convertida en notación posfija.
 */
std::string Expresion::convertirAPosfija() {
    std::stringstream salida;
    Pila<char> pilaOperadores;

    for (size_t i = 0; i < infija.size(); ++i) {
        char caracter = infija[i];

        // Si es un número, se añade directamente a la salida
        if (std::isdigit(caracter)) {
            salida << caracter;
        } 
        // Si es un operador, se maneja la precedencia
        else if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            while (!pilaOperadores.EstaVacia() && prioridad(pilaOperadores.ObtenerTope()) >= prioridad(caracter)) {
                salida << ' ' << pilaOperadores.ObtenerTope();
                pilaOperadores.Desapilar();
            }
            salida << ' ';
            pilaOperadores.Apilar(caracter);
        } 
        // Si es un paréntesis de apertura, se apila
        else if (caracter == '(') {
            pilaOperadores.Apilar(caracter);
        } 
        // Si es un paréntesis de cierre, se desapilan operadores hasta encontrar '('
        else if (caracter == ')') {
            while (!pilaOperadores.EstaVacia() && pilaOperadores.ObtenerTope() != '(') {
                salida << ' ' << pilaOperadores.ObtenerTope();
                pilaOperadores.Desapilar();
            }
            pilaOperadores.Desapilar(); // Eliminar '('
        }
    }

    // Desapilar los operadores restantes
    while (!pilaOperadores.EstaVacia()) {
        salida << ' ' << pilaOperadores.ObtenerTope();
        pilaOperadores.Desapilar();
    }

    return salida.str();
}


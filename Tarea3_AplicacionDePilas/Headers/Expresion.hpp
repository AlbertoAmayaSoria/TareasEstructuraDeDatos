#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <iostream>
#include <string>

/**
 * @brief Clase que maneja y evalúa expresiones matemáticas en notación infija y posfija.
 * 
 * La clase proporciona métodos para almacenar, validar y evaluar expresiones matemáticas.
 * Permite convertir una expresión infija (por ejemplo, "3 + 2") a su equivalente en notación
 * posfija (por ejemplo, "3 2 +") y luego evaluar esa expresión.
 */
class Expresion {
public:
    /**
     * @brief Constructor por defecto que inicializa la expresión como vacía.
     * 
     * Este constructor inicializa la expresión infija y posfija como cadenas vacías y
     * establece la validez de la expresión como verdadera por defecto.
     */
    Expresion();

    /**
     * @brief Constructor que inicializa la expresión con una cadena.
     * 
     * Este constructor permite inicializar una expresión infija directamente al crear la instancia
     * de la clase, y llama a la función 'capturarExpresion' para validarla.
     * 
     * @param expresion La expresión infija que se desea almacenar.
     */
    Expresion(std::string expresion);

    /**
     * @brief Captura la expresión infija y valida su formato.
     * 
     * Este método almacena la expresión infija y valida su formato. Si la expresión es inválida,
     * se lanza una excepción.
     * 
     * @param expresion La expresión infija a almacenar.
     */
    void capturarExpresion(std::string expresion);

    /**
     * @brief Imprime la expresión infija y su versión posfija.
     * 
     * Este método convierte la expresión infija a notación posfija y luego imprime ambas expresiones
     * (infija y posfija) en la salida estándar para su visualización.
     */
    void imprimirExpresion();

    /**
     * @brief Evalúa la expresión infija convertida a posfija.
     * 
     * Este método convierte la expresión infija a notación posfija y la evalúa. Si la expresión es válida,
     * devuelve el resultado de la operación matemática. En caso de error, lanza una excepción.
     * 
     * @return int El resultado de la evaluación de la expresión.
     */
    int evaluar();

private:
    std::string infija;   ///< La expresión en notación infija.
    std::string posfija;  ///< La expresión en notación posfija.
    bool valida;          ///< Indica si la expresión es válida.

    /**
     * @brief Determina si un carácter es un operador matemático.
     * 
     * Este método verifica si un carácter dado corresponde a uno de los operadores matemáticos
     * básicos (+, -, *, /).
     * 
     * @param operador El carácter a verificar.
     * @return true Si el carácter es un operador.
     * @return false Si el carácter no es un operador.
     */
    bool esOperador(char operador);

    /**
     * @brief Determina la precedencia de un operador matemático.
     * 
     * Este método asigna un nivel de precedencia a los operadores matemáticos. Los operadores
     * de multiplicación (*) y división (/) tienen mayor precedencia que los operadores de suma
     * (+) y resta (-).
     * 
     * @param operador El operador matemático (+, -, *, /).
     * @return int Nivel de precedencia (mayor valor indica mayor precedencia).
     */
    int prioridad(char operador);

    /**
     * @brief Valida la expresión infija para asegurarse de que tiene una sintaxis correcta.
     * 
     * Este método revisa la expresión infija para asegurarse de que todos los paréntesis y corchetes
     * estén correctamente balanceados y que la expresión no tenga errores de sintaxis.
     * Si la expresión no es válida, lanza una excepción.
     * 
     * @return true Si la expresión es válida.
     * @return false Si la expresión es inválida.
     */
    bool validarExpresion();

    /**
     * @brief Convierte una expresión en notación infija a notación posfija (notación polaca inversa).
     * 
     * Este método convierte una expresión en notación infija a su equivalente en notación posfija
     * utilizando el algoritmo de Shunting Yard. Los operadores y operandos se reorganizan de manera
     * que facilitan la evaluación sin necesidad de paréntesis.
     * 
     * @return std::string La expresión convertida en notación posfija.
     */
    std::string convertirAPosfija();

    /**
     * @brief Evalúa una expresión en notación posfija.
     * 
     * Este método evalúa la expresión en notación posfija utilizando una pila. A medida que recorre
     * la expresión, apila los operandos y realiza las operaciones cuando encuentra los operadores.
     * 
     * @return int El resultado de la evaluación de la expresión.
     */
    int evaluarPosfija();
};

#endif // EXPRESION_HPP_INCLUDED


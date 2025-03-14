/**
 * @file ListaDobleCircular.hpp
 * @brief Definición de la clase ListaDobleCircular
 */

#ifndef LISTADOBLECIRCULAR_HPP
#define LISTADOBLECIRCULAR_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief Clase que implementa una lista doblemente enlazada circular.
 * @tparam T Tipo de dato almacenado en la lista.
 */
template <typename T>
class ListaDobleCircular {
public:

    // Métodos indispensables para el buen funcionamiento.

    /*  
     * @brief Constructor por defefecto.
     * Inicializa una lista vacía.
     */
    ListaDobleCircular();

    /*
     * @brief Constructor de copias.
     * @param otra lista a copiar.
     */
    ListaDobleCircular(const ListaDobleCircular& otra);

    /*
     * @brief Destructor.
     * Libera la memoria utilizada por la lista.
     */
    ~ListaDobleCircular();

    /*
     * @brief Sobrecarga del operador de asignación.
     * @param otra lista a copiar.
     * @return Referencia a la lista actual
     */
    ListaDobleCircular& operator=(const ListaDobleCircular& otra);

    /*
     * @brief Inserta un elemento en la cabeza de la lista.
     * @param valor Valor a insertar.
     */
    void insertar(T valor);

    /*
     * @brief eliminar el elemento en cabeza de la lista.
     * @throw std::out_of_range Si la lista esta vacía.
     */
    void eliminar();

    /*
     * @brief Buscar un valor en la lista.
     * @param valor Valor a buscar.
     * @return true si el valor está en la lista, false en caso contrario.
     */
    bool buscar(T valor) const;

    /*
     * @brief Avanza en uno la posición de la cabeza.
     * @throw std::out_of_range Si la lista esta vacía.
     */
    void avanzarCabeza();

    /*
     * @brief Retrocede en uno la posición de la cabeza.
     * @throw std::out_of_range Si la lista esta vacía.
     */
    void retrocederCabeza();

    /*
     * @brief Conocer el número de elementos en la lista.
     * @return Número de elementos.
     */
    size_t obtenerTamaño();

    /*
     * @brief Verifica si la lista está vacía.
     * @return true si estas vacía, false en caso constrario.
     */
    bool estaVacia();

    /*
     * @brief Vacía la lista.
     */
    void vaciar();

    /*
     * @brief Imprime la lista hacia adelante.
     */
    void imprimirAdelante();

    /*
     * @brief Imprime la lista hacia atras.
     */
    void imprimirReversa();


private:
    /**
     * @brief Estructura interna para representar un nodo de la lista.
     */
    struct Nodo {
        T dato; // Valor almacenado en el nodo.
        Nodo* anterior; // Puntero al nodo anterior.
        Nodo* siguiente; // Puntero al nodo siguiente.
        
        /**
         * @brief Constructor del nodo.
         * @param valor Valor a almacenar en el nodo.
         */
        Nodo(T valor) : dato(valor), anterior(nullptr), siguiente(nullptr) {}
    };
    
    Nodo* cabeza; // Puntero a la cabeza de la lista
    size_t tamaño; ///< Tamaño de la lista.
};


#include "../Templates/ListaDobleCircular.cpp"

#endif // LISTADOBLECIRCULAR_HPP

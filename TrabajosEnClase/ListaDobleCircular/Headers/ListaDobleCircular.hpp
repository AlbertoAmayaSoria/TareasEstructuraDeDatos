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
    

private:
    /**
     * @brief Estructura interna para representar un nodo de la lista.
     */
    struct Nodo {
        T dato; ///< Valor almacenado en el nodo.
        Nodo* anterior; ///< Puntero al nodo anterior.
        Nodo* siguiente; ///< Puntero al nodo siguiente.
        
        /**
         * @brief Constructor del nodo.
         * @param valor Valor a almacenar en el nodo.
         */
        Nodo(T valor) : dato(valor), anterior(nullptr), siguiente(nullptr) {}
    };
    
    Nodo* cabeza; // Puntero a la cabeza de la lista

    //Nodo* primero; ///< Puntero al primer nodo de la lista.
    //Nodo* ultimo;  ///< Puntero al último nodo de la lista.
    size_t tamaño; ///< Tamaño de la lista.
};

// Implementación de métodos en el archivo .tpp
#include "../Templates/ListaDobleCircular.tpp"

#endif // LISTADOBLECIRCULAR_HPP

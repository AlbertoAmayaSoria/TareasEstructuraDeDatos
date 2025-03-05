/**
 * @file LinkedList.hpp
 * @brief Definición de la clase ListaDoblementeEnlazada
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief Clase que implementa una lista doblemente enlazada.
 * @tparam T Tipo de dato almacenado en la lista.
 */
template <typename T>
class ListaDoblementeEnlazada {
public:
    /**
     * @brief Constructor por defecto.
     * Inicializa una lista vacía.
     */
    ListaDoblementeEnlazada();
    
    /**
     * @brief Constructor de copia.
     * @param otra Lista a copiar.
     */
    ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra);
    
    /**
     * @brief Destructor.
     * Libera la memoria utilizada por la lista.
     */
    ~ListaDoblementeEnlazada();
    
    /**
     * @brief Sobrecarga del operador de asignación.
     * @param otra Lista a copiar.
     * @return Referencia a la lista actual.
     */
    ListaDoblementeEnlazada& operator=(const ListaDoblementeEnlazada& otra);

    /**
     * @brief Inserta un elemento al inicio de la lista.
     * @param valor Valor a insertar.
     */
    void insertarInicio(T valor);
    
    /**
     * @brief Inserta un elemento al final de la lista.
     * @param valor Valor a insertar.
     */
    void insertarFinal(T valor);
    
    /**
     * @brief Inserta un elemento en una posición específica.
     * @param valor Valor a insertar.
     * @param pos Posición en la que se insertará el valor.
     * @throw std::out_of_range Si la posición es inválida.
     */
    void insertarPosicion(T valor, size_t pos);

    /**
     * @brief Elimina el primer elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    void eliminarInicio();
    
    /**
     * @brief Elimina el último elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    void eliminarFinal();
    
    /**
     * @brief Elimina un elemento en una posición específica.
     * @param pos Posición del elemento a eliminar.
     * @throw std::out_of_range Si la posición es inválida.
     */
    void eliminarPosicion(size_t pos);
    
    /**
     * @brief Elimina la primera ocurrencia de un valor en la lista.
     * @param valor Valor a eliminar.
     * @return true si el valor fue eliminado, false si no se encontró.
     */
    void eliminarValor(T valor);
    
    /**
     * @brief Elimina todas las ocurrencias de un valor en la lista.
     * @param valor Valor a eliminar.
     */
    void eliminarTodasOcurrencias(T valor);
    
    /**
     * @brief Elimina elementos que cumplen una condición.
     * @param condicion Función que define la condición de eliminación.
     */
    void eliminarPorCondicion(bool (*condicion)(T));
    
    /**
     * @brief Elimina elementos duplicados de la lista.
     */
    void eliminarElementosRepetidos();

    /**
     * @brief Busca un valor en la lista.
     * @param valor Valor a buscar.
     * @return true si el valor está en la lista, false en caso contrario.
     */
    bool buscar(T valor) const;

    /**
     * @brief Verifica si la lista está vacía.
     * @return true si la lista está vacía, false en caso contrario.
     */
    bool estaVacia() const;
    
    /**
     * @brief Obtiene el primer elemento de la lista.
     * @return El primer elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    T obtenerPrimero() const;
    
    /**
     * @brief Obtiene el último elemento de la lista.
     * @return El último elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    T obtenerUltimo() const;
    
    /**
     * @brief Obtiene un elemento en una posición específica.
     * @param posicion Posición del elemento a obtener.
     * @return El elemento en la posición especificada.
     * @throw std::out_of_range Si la posición es inválida.
     */
    T obtenerEnPosicion(size_t posicion) const;
    
    /**
     * @brief Obtiene el índice de un valor en la lista.
     * @param valor Valor a buscar.
     * @return El índice del valor, o -1 si no se encuentra.
     */
    int obtenerIndice(const T& valor) const;
    
    /**
     * @brief Modifica un valor en una posición específica.
     * @param posicion Posición del valor a modificar.
     * @param nuevoValor Nuevo valor a asignar.
     * @throw std::out_of_range Si la posición es inválida.
     */
    void modificarEnPosicion(size_t posicion, T nuevoValor);
    
    /**
     * @brief Obtiene el tamaño de la lista.
     * @return El tamaño de la lista.
     */
    size_t obtenerTamaño() const;
    
    /**
     * @brief Vacía la lista.
     */
    void vaciar();
    
    /**
     * @brief Imprime la lista en orden normal.
     */
    void imprimir() const;
    
    /**
     * @brief Imprime la lista en orden inverso.
     */
    void imprimirReversa() const;
    
    /**
     * @brief Sobrecarga del operador [] para acceder a elementos por índice.
     * @param index Índice del elemento a acceder.
     * @return Referencia al elemento en la posición especificada.
     * @throw std::out_of_range Si el índice es inválido.
     */
    T& operator[](size_t index);
    
    /**
     * @brief Sobrecarga del operador [] para acceso constante.
     * @param index Índice del elemento a acceder.
     * @return Referencia constante al elemento en la posición especificada.
     * @throw std::out_of_range Si el índice es inválido.
     */
    const T& operator[](size_t index) const;
    
    /**
     * @brief Ordena la lista en orden ascendente.
     */
    void ordenarAscendente();
    
    /**
     * @brief Intercambia los elementos de la lista con otra.
     * @param otra Lista con la que se intercambiarán los elementos.
     */
    void intercambiar(ListaDoblementeEnlazada<T>& otra);
    
    /**
     * @brief Transfiere elementos de una posición a otra lista.
     * @param otra Lista a la que se transferirán los elementos.
     * @param inicio Índice de inicio del rango de elementos a transferir.
     * @param fin Índice de fin del rango de elementos a transferir.
     */
    void transferirElementos(ListaDoblementeEnlazada<T>& otra, size_t inicio, size_t fin);
    
    /**
     * @brief Transfiere elementos desde un índice específico a otra lista.
     * @param otra Lista a la que se transferirán los elementos.
     * @param indice Índice desde el cual se transferirán los elementos.
     */
    void transferirDesdeIndice(ListaDoblementeEnlazada<T>& otra, size_t indice);
    
    /**
     * @brief Transfiere todos los elementos a otra lista.
     * @param otra Lista a la que se transferirán los elementos.
     */
    void transferirTodos(ListaDoblementeEnlazada<T>& otra);

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
    
    Nodo* primero; ///< Puntero al primer nodo de la lista.
    Nodo* ultimo;  ///< Puntero al último nodo de la lista.
    size_t tamaño; ///< Tamaño de la lista.
};

// Implementación de métodos en el archivo .tpp
#include "../Templates/ListaDoblementeEnlazada.tpp"

#endif // LINKEDLIST_HPP

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept> // Para manejar excepciones

template <typename T>
class ListaDoblementeEnlazada {

public:
    // Constructor
    ListaDoblementeEnlazada();
    // Constructor de copia
    ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra);
    // Destructor
    ~ListaDoblementeEnlazada();
    // Sobrecarga del operador =
    ListaDoblementeEnlazada& operator=(const ListaDoblementeEnlazada& otra);

    // Métodos de inserción
    void insertarInicio(T valor);
    void insertarFinal(T valor);
    void insertarPosicion(T valor, size_t pos);

    // Métodos de eliminación
    void eliminarInicio();
    void eliminarFinal();
    void eliminarPosicion(size_t pos);
    void eliminarValor(T valor);

    // Métodos de búsqueda
    bool buscar(T valor);

    // Métodos para obtener datos
    T obtenerPrimero() const;
    T obtenerUltimo() const;
    T obtenerEnPosicion(size_t posicion) const;
    int obtenerIndice(const T& valor) const;

    // Método para obtener el tamaño de la lista
    size_t obtenerTamaño() const;

    // Métodos para imprimir la lista
    void imprimir() const;
    void imprimirReversa() const;

private:
    struct Nodo {
        T dato;          // Dato del nodo
        Nodo* anterior;  // Puntero al nodo anterior
        Nodo* siguiente; // Puntero al siguiente nodo
        Nodo(T valor) : dato(valor), anterior(nullptr), siguiente(nullptr) {}
    };

    Nodo* primero;   // Puntero al primer nodo
    Nodo* ultimo;    // Puntero al último nodo
    size_t tamaño;   // Tamaño de la lista
};

#include "../Templates/ListaDoblementeEnlazada.tpp"

#endif // LINKEDLIST_HPP


#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept> // Para manejar excepciones

template <typename T>
class ListaDoblementeEnlazadaOrdenada {

public:
    // Constructor
    ListaDoblementeEnlazadaOrdenada();
    // Constructor de copia
    ListaDoblementeEnlazadaOrdenada(const ListaDoblementeEnlazadaOrdenada& otra);
    // Destructor
    ~ListaDoblementeEnlazadaOrdenada();
    // Sobrecarga del operador =
    ListaDoblementeEnlazadaOrdenada& operator=(const ListaDoblementeEnlazadaOrdenada& otra);

    // Método de inserción
    void insertar(T valor);

    // Métodos de eliminación
    void eliminarValor(T valor); //primera ocurrencia

    // Métodos de búsqueda
    bool buscar(T valor);

    // Métodos para obtener datos

    // Método para obtener el tamaño de la lista
    size_t obtenerTamaño() const;

    // Método para saber si la lista esta vacía
    bool estaVacia();

    // Método para vaciar la lista
    void vaciar();

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


#include "../Templates/ListaDoblementeEnlazadaOrdenada.tpp"

#endif // LINKEDLIST_HPP


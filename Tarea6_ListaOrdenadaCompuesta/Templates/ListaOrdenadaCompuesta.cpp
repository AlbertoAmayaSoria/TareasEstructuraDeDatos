#include "../Headers/ListaOrdenadaCompuesta.hpp"
#include <iostream>

// Constructor
template <typename T>
ListaOrdenadaCompuesta<T>::ListaOrdenadaCompuesta() {}

// Método para insertar un valor de forma ordenada
template <typename T>
void ListaOrdenadaCompuesta<T>::insertar(T valor) {
    size_t size = lista.obtenerTamaño();
    if (size == 0) {
        lista.insertarInicio(valor); // Si la lista está vacía, insertamos al inicio
    } else {
        size_t i = 0;
        while (i < size && valor > lista.obtenerEnPosicion(i)) {
            i++; // Encontramos la posición correcta para insertar el valor
        }
        lista.insertarPosicion(valor, i); // Insertamos el valor en la posición encontrada
    }
}

// Método para eliminar la primera ocurrencia de un valor
template <typename T>
void ListaOrdenadaCompuesta<T>::eliminar(T valor) {
    int indice = lista.obtenerIndice(valor); // Buscamos la primera ocurrencia
    if (indice != -1) {
        lista.eliminarPosicion(indice); // Eliminamos el valor en el índice encontrado
    }
}

// Método para buscar un valor en la lista
template <typename T>
bool ListaOrdenadaCompuesta<T>::buscar(T valor) {
    return lista.buscar(valor); // Usamos el método de búsqueda de la lista interna
}

// Método para vaciar la lista
template <typename T>
void ListaOrdenadaCompuesta<T>::vaciar() {
    while (!estaVacia()) {
        lista.eliminarInicio(); // Eliminamos el primer nodo hasta que la lista esté vacía
    }
}

// Método para verificar si la lista está vacía
template <typename T>
bool ListaOrdenadaCompuesta<T>::estaVacia() const {
    return lista.obtenerTamaño() == 0; // Verificamos si el tamaño de la lista es 0
}

// Método para obtener el tamaño de la lista
template <typename T>
size_t ListaOrdenadaCompuesta<T>::tamaño() const {
    return lista.obtenerTamaño(); // Devolvemos el tamaño de la lista interna
}

// Método para imprimir la lista en orden
template <typename T>
void ListaOrdenadaCompuesta<T>::imprimir() const {
    lista.imprimir(); // Usamos el método de impresión de la lista interna
}

// Método para imprimir la lista en orden inverso
template <typename T>
void ListaOrdenadaCompuesta<T>::imprimirReversa() const {
    lista.imprimirReversa(); // Usamos el método de impresión en reversa de la lista interna
}


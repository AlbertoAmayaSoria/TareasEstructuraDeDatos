#ifndef LISTAORDENADACOMPUESTA_HPP
#define LISTAORDENADACOMPUESTA_HPP

#include "../Headers/ListaDoblementeEnlazada.hpp"
#include <functional> // Para el comparador de ordenación

template <typename T>
class ListaOrdenadaCompuesta {
private:
    ListaDoblementeEnlazada<T> lista; // La lista interna de la cual hacemos uso

public:
    // Constructor por defecto
    ListaOrdenadaCompuesta();

    // Destructor
    ~ListaOrdenadaCompuesta();

    // Constructor de copia
    ListaOrdenadaCompuesta(const ListaOrdenadaCompuesta<T>& otra);

    // Sobrecarga del operador =
    ListaOrdenadaCompuesta<T>& operator=(const ListaOrdenadaCompuesta<T>& otra);

    // Métodos requeridos
    void insertar(T valor); // Insertar de forma ordenada
    void eliminar(T valor); // Eliminar la primera ocurrencia de un valor
    bool buscar(T valor); // Buscar un valor
    void vaciar(); // Vaciar la lista
    bool estaVacia() const; // Verificar si la lista está vacía
    size_t tamaño() const; // Obtener el tamaño de la lista
    void imprimir() const; // Imprimir la lista en orden
    void imprimirReversa() const; // Imprimir la lista en orden inverso
};

#include "../Templates/ListaOrdenadaCompuesta.tpp"

#endif // LISTAORDENADACOMPUESTA_HPP

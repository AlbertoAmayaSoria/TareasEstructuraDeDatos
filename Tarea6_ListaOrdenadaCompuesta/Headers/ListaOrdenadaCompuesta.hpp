#ifndef LISTAORDENADACOMPUESTA_HPP_INCLUDED
#define LISTAORDENADACOMPUESTA_HPP_INCLUDED
#include "../Headers/ListaDoblementeEnlazada.hpp"
#include <cstddef>

template <typename T>
class ListaOrdenadaCompuesta {

    public:
    // Constructor
    ListaOrdenadaCompuesta();
    // Constructor de copias
    ListaOrdenadaCompuesta(const ListaOrdenadaCompuesta& otra);
    // Destructor
    ~ListaOrdenadaCompuesta();
    // Sobre carga del operador =
    ListaOrdenadaCompuesta& operator=(const ListaOrdenadaCompuesta& otra);

    // Agregar un elemento de forma ordenada
    void insertar(T valor);

    // Eliminar un elemento (primera ocurrencia)
    void eliminar(T valor);

    // Buscar un elemento
    bool buscar(T valor);

    // Vaciar la lista
    void vaciar();

    // Conocer si la lista esta vacía
    bool estaVacia();

    // Conocer el tamaño de la lista
    std::size_t tamaño();

    // Imprimir la lista de forma ascendente
    void imprimir();

    // Imprimir la lista de forma descendente
    void imprimirReversa();

    // Mezclar dos listas
    void mezclar();


    private:
    ListaDoblementeEnlazada<T> lista;


}

#endif // !LISTAORDENADACOMPUESTA_HPP_INLCUDED

/**
 * \file Nodo.hpp
 */

#ifndef NODO_HPP_INCLUDED
#define NODO_HPP_INCLUDED

#include "../Headers/Arista.hpp"

struct Nodo{
    char nombre;
    int grado;
    Arista *primera, *ultima;
    Nodo *siguiente;

    Nodo(char nom, Nodo *sig = NULL);

    //Agregar una arista
    void Agregar(Nodo *ady);

    //Eliminar una arista
    void Eliminar(Nodo *ady);

    //Vaciar el nodo
    int Vaciar();

    //Buscar una arista
    bool Buscar(Nodo *ady) const;

    //Imprimir información de un nodo
    void Imprimir() const;

    Arista * BuscarDireccion(Nodo *ady, Arista **ant = NULL) const;

};

#endif // NODO_HPP_INCLUDED

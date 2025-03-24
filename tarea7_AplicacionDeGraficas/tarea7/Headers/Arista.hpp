/**
 * \file Arista.hpp
 */

#ifndef ARISTA_HPP_INCLUDED
#define ARISTA_HPP_INCLUDED

struct Nodo;

struct Arista{
    Nodo * adyacente;
    Arista *siguiente;

    Arista(Nodo *ady, Arista *sig=NULL):adyacente(ady), siguiente(sig){}
};

#endif // ARISTA_HPP_INCLUDED

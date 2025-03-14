//
// Created by Michell O on 3/12/2025.
//

#ifndef NODO_H
#define NODO_H
#include "arista.h"

struct  Nodo {
    char nombre;
    int grado;
    Arista *primera, *ultima;
    Nodo *siguiente;

    Nodo(char nom, Nodo *sig = NULL);

    //Agregar arista
    void Agregar(Nodo *ady);

    //Eliminar una arista
    void Eliminar(Nodo *ady);

    //Vaciar el nodo
    void Vaciar();

    //Buscar arista
    bool Buscar(Nodo *ady) const;

    //imprimir informacion deun nodo
    void Imprimir() const;

    //Direccion de una arista
    Arista * BuscarDireccion (Nodo *ady, Arista **ant = NULL) const;
}


class nodo {

};



#endif //NODO_H

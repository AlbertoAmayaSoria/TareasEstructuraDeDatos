//
// Created by Michell O on 3/12/2025.
//

#include "nodo.h"

Nodo::Nodo(char nom, Nodo *sig /*NULL*/):nombre(nom), grado (0),
    primera(NULL), ultima(NULL),siguiente(sig){}
////////////////////////////////////////////////////////////////////

void Nodo::Agregar(Nodo *ady) {
    Arista *nueva=new Arista(ady);
    grado == 0 ? primera = nueva: ultima ->siguiente = nueva;
    ultima = nueva;
    ++grado;

}
//////////////////////////////////////////////////////////////////////////

void Nodo::Eliminar(Nodo *ady) {
    Arista *ant, *porBorrar = BuscarDireccion(ady, &ant);
}
////////////////////////////////////////////////////////////////

Arista *Nodo::BuscarDireccion(Nodo *ady, Arista **ant) const {
    Arista *aux = primera;
    if (ant != NULL) *ant=NULL;
    while (aux != NULL && aux->adyacente != ady) {
        if (ant != NULL) *ant =aux;
        aux = aux->siguiente;
    }
    return aux;
}


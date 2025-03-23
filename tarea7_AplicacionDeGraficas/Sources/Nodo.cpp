/*
Nombre del archivo: Nodo.cpp
*/
#include <iostream>
#include "../Headers/Nodo.hpp"
//******************************************************

Nodo::Nodo(char nom, Nodo *sig /*=NULL*/) : nombre(nom), grado(0), primera(NULL), ultima(NULL), siguiente(sig), visitado(false) {}

//******************************************************
void Nodo::Agregar(Nodo *ady)
{
    Arista *nueva = new Arista(ady);
    grado == 0 ? primera = nueva : ultima->siguiente = nueva;
    ultima = nueva;
    ++grado;
}
//******************************************************
void Nodo::Eliminar(Nodo *ady)
{
    Arista *ant, *porBorrar = BuscarDireccion(ady,&ant);
    if(porBorrar == NULL) return;
    ant == NULL ? primera = primera->siguiente : ant->siguiente = porBorrar->siguiente;
    if(primera == NULL) ultima = NULL;
    delete porBorrar;
    --grado;
}
//******************************************************
int Nodo::Vaciar()
{
    int numAristas = 0;
    while(primera != NULL){
        Arista *porBorrar = primera;
        //Si la arista no es un lazo, se elimina a este vértice del
        //de la lista de aristas del vértice adyacente
        if(primera->adyacente != this) primera->adyacente->Eliminar(this);
        primera = primera->siguiente;
        delete porBorrar;
        ++numAristas;
    }
    ultima = NULL;
    grado = 0;
    return numAristas;
}
//******************************************************
bool Nodo::Buscar(Nodo *ady) const
{
    return BuscarDireccion(ady) != NULL;
}
//******************************************************
void Nodo::Imprimir() const
{
    Arista *visitada = primera;
    while(visitada != NULL){
        std::cout << visitada->adyacente->nombre << ", ";
        visitada = visitada->siguiente;
    }
    std::cout << "\b\b ";
}
//******************************************************
Arista * Nodo::BuscarDireccion(Nodo *ady, Arista **ant /*=NULL*/)const
{
    Arista *aux = primera;
    if(ant != NULL) *ant = NULL;
    while(aux != NULL && aux->adyacente != ady){
        if(ant != NULL) *ant = aux;
        aux = aux->siguiente;
    }
    return aux;
}

//******************************************************



//
// Created by Michell O on 3/12/2025.
//
//estructua arista
#ifndef ARISTA_H
#define ARISTA_H
struct Nodo;
struct Arista {
    Nodo * adyacente;
    Arista * siguiente;

    Arista (Nodo * ady, Arista * sig=NULL):adyacente(ady), siguiente(sig) {}



};



class arista {

};



#endif //ARISTA_H

#include <iostream>
#include "../Headers/Grafica.hpp"

//*************************************************
Grafica::Grafica():primero(NULL),ultimo(NULL),numNodos(0),
    numAristas(0){}
//*************************************************
Grafica::Grafica(const Grafica &g):primero(NULL),
    ultimo(NULL),numNodos(0),numAristas(0)
{
    *this = g;
}
//*************************************************
Grafica::~Grafica()
{
    Vaciar();
}
//*************************************************
Grafica & Grafica::operator=(const Grafica &g)
{
    if(this == &g) return *this;
    Vaciar();
    Nodo *nodoVisitado = g.primero;
    while(nodoVisitado != NULL){
        Agregar(nodoVisitado->nombre);
        nodoVisitado = nodoVisitado->siguiente;
    }
    nodoVisitado = g.primero;
    Arista *aristaVisitada;
    while(nodoVisitado != NULL){
        aristaVisitada = nodoVisitado->primera;
        while(aristaVisitada != NULL){
            if(!Buscar(nodoVisitado->nombre,
            aristaVisitada->adyacente->nombre)){

                Agregar(nodoVisitado->nombre,
                aristaVisitada->adyacente->nombre);
            }
            aristaVisitada = aristaVisitada->siguiente;
        }
        nodoVisitado = nodoVisitado->siguiente;
    }
    return *this;
}
//*************************************************
void Grafica::Agregar(char nom)
{
    Nodo * nuevo = new Nodo(nom);
    numNodos == 0 ? primero = nuevo : ultimo->siguiente = nuevo;
    ultimo = nuevo;
    ++numNodos;
}
//*************************************************
void Grafica::Agregar(char nomInicial, char nomFinal)
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return;
    //Agregar el nodo final en la lista del nodo inicial
    dirInicial->Agregar(dirFinal);
    //Agregar el nodo inicial en la lista del nodo final
    dirFinal->Agregar(dirInicial);
    ++numAristas;
}
//*************************************************
void Grafica::Eliminar(char nom)
{
    Nodo *ant, *porBorrar = BuscarDireccion(nom,&ant);
    if(porBorrar == NULL) return;
    numAristas -= porBorrar->Vaciar();
    if(ant == NULL) primero = primero->siguiente;
    if(primero == NULL) ultimo = NULL;
    delete porBorrar;
    --numNodos;
}
//*************************************************
void Grafica::Eliminar(char nomInicial, char nomFinal)
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return;
    //Eliminar el final de la lista del inicial
    dirInicial->Eliminar(dirFinal);
    //Eliminar el inicial de la lista del final
    dirFinal->Eliminar(dirInicial);
    --numAristas;
}
//*************************************************
int Grafica::ObtenerNumNodos() const
{
    return numNodos;
}

//*************************************************
int Grafica::ObtenerNumAristas() const
{
    return numAristas;
}

//*************************************************
int Grafica::ObtenerGrado(char nom) const
{
    Nodo *nodoBuscado = BuscarDireccion(nom);
    if(nodoBuscado == NULL) throw "Nodo inexistente";
    return nodoBuscado->grado;
}

//*************************************************
bool Grafica::Buscar(char nom) const
{
    return BuscarDireccion(nom) != NULL;
}
//*************************************************
bool Grafica::Buscar(char nomInicial, char nomFinal) const
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return false;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return false;

    return dirInicial->Buscar(dirFinal);
}
//*************************************************
void Grafica::Imprimir()const
{
    Nodo *visitado = primero;
    while(visitado != NULL){
        std::cout << visitado->nombre << ": ";
        visitado->Imprimir();
        visitado = visitado->siguiente;
        std::cout << std::endl;
    }
}
//*************************************************
void Grafica::Vaciar(char nom)
{
    Nodo *porVaciar = BuscarDireccion(nom);
    if(porVaciar == NULL) return;
    numAristas -= porVaciar->Vaciar();
}
//*************************************************
void Grafica::Vaciar()
{
    while(primero != NULL) Eliminar(primero->nombre);
}
//*************************************************
Nodo * Grafica::BuscarDireccion(char nom, Nodo **ant /*=NULL*/)const
{
    Nodo *aux = primero;
    if(ant != NULL) *ant = NULL;
    while(aux != NULL && aux->nombre != nom){
        if(ant != NULL) *ant = aux;
        aux = aux->siguiente;
    }
    return aux;
}

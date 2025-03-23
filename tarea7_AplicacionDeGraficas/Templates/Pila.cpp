#include <iostream>


//************************************************************************************************
template <typename Tipo>
Pila<Tipo>::Pila(int  cap) : tope(-1)
{
    this -> cap = cap;
    try{
        elemento = new Tipo[cap];
    }catch(std::bad_alloc&){
        throw "Problemas de asignaci\242n de memoria\n";
    }
}
//************************************************************************************************
template <typename Tipo>
Pila<Tipo>::Pila(const Pila &p)
{
    *this = p;
}
//************************************************************************************************
template <typename Tipo>
Pila<Tipo>::~Pila()
{
    delete [] elemento;
}
//************************************************************************************************
template <typename Tipo>
Pila<Tipo> & Pila<Tipo>::operator=(const Pila<Tipo> &p)
{
    if(this == &p) return *this;
    delete [] elemento;
    cap = p.cap;
    tope = p.tope;
    try{
        elemento = new Tipo[cap];
        for(int i = 0; i < tope; ++i){
        elemento[i] = p.elemento[i];
        }
    }catch (std::bad_alloc &){
    throw "Problemas de asignaci\242n de memoria";
    }
    return *this;
}
//************************************************************************************************
template <typename Tipo>
void Pila<Tipo>::Apilar(Tipo valor)
{
    if(EstaLlena()) throw "Pila llena...";
    ++tope;
    elemento[tope] = valor;
}
//************************************************************************************************
template <typename Tipo>
void Pila<Tipo>::Desapilar()
{
    if(EstaVacia()) throw "Pila vacia...";
    --tope;
}
//************************************************************************************************
template <typename Tipo>
Tipo Pila<Tipo>::ObtenerTope() const
{
    if(EstaVacia()) throw "Pila vacia...";
    return elemento[tope];
}
//************************************************************************************************
template <typename Tipo>
bool Pila<Tipo>::EstaVacia() const
{
    return tope == -1;
}
//************************************************************************************************
template <typename Tipo>
bool Pila<Tipo>::EstaLlena() const
{
    return tope + 1 == MAX_TAM;
}
//************************************************************************************************
template <typename Tipo>
void Pila<Tipo>::Imprimir() const
{
    for(int i = 0; i <= tope; ++i){
        std::cout << elemento[i] << ", ";
    }
    std::cout << "\b\b <- TOPE" << std::endl;
}
//************************************************************************************************
template <typename Tipo>
void Pila<Tipo>::Vaciar()
{
    tope = -1;
}
//************************************************************************************************

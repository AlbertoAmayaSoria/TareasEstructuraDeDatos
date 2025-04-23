#include <iostream>


//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
Pila<Tipo, cap>::Pila() : tope(-1) {}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
void Pila<Tipo, cap>::Apilar(Tipo valor)
{
    if(EstaLlena()) throw "Pila llena...";
    ++tope;
    elemento[tope] = valor;
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
void Pila<Tipo, cap>::Desapilar()
{
    if(EstaVacia()) throw "Pila vacia...";
    --tope;
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
Tipo Pila<Tipo, cap>::ObtenerTope() const
{
    if(EstaVacia()) throw "Pila vacia...";
    return elemento[tope];
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
bool Pila<Tipo, cap>::EstaVacia() const
{
    return tope == -1;
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
bool Pila<Tipo, cap>::EstaLlena() const
{
    return tope + 1 == MAX_TAM;
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
void Pila<Tipo, cap>::Imprimir() const
{
    for(int i = 0; i <= tope; ++i){
        std::cout << elemento[i] << ", ";
    }
    std::cout << "\b\b <- TOPE";
}
//************************************************************************************************
template <typename Tipo/*  = int*/, int cap/* = 10*/>
void Pila<Tipo, cap>::Vaciar()
{
    tope = -1;
}
//************************************************************************************************

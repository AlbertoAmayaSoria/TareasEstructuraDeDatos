#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

#include "../Headers/Nodo.hpp"

class Grafica{
public:
    Grafica();
    Grafica(const Grafica &g);
    ~Grafica();
    Grafica & operator=(const Grafica &g);

    //Agregar nodo
    void Agregar(char nom);
    //AgregarArista
    void Agregar(char nomInicial, char nomFinal);

    //Eliminar nodo
    void Eliminar(char nom);
    //Eliminar arista
    void Eliminar(char nomInicial, char nomFinal);

    int ObtenerNumNodos() const;
    int ObtenerNumAristas() const;
    int ObtenerGrado(char nom) const;

    //Buscar nodo
    bool Buscar(char nom) const;
    //Buscar arista
    bool Buscar(char nomInicial, char nomFinal) const;

    void Imprimir() const;

    //Vaciar nodo
    void Vaciar(char nom);
    //Vaciar toda la gráfica
    void Vaciar();

private:
    Nodo *primero, *ultimo;
    int numNodos, numAristas;

    Nodo *BuscarDireccion(char nom, Nodo **ant = NULL) const
    ;
};

#include "../Templates/Grafica.tpp"

#endif // GRAFICA_HPP_INCLUDED

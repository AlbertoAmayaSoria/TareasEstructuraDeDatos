#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

template <typename Type, char MaxOMin>
class Heap{
public:

    explicit Heap();

    Heap(const Heap &H);

    ~Heap();

    Heap & operator=(const Heap &&H);

    void Agregar();

    void Eliminar();
    
    Type ObtenerFrente() const;

    bool EstaVacia() const;

    void Vaciar();

    int CantElem() const;

    int CapMont() const; // Para pruebas
    
    void ImprimirElem() const; // Para pruebas

private:

    int cantElem;
    int capacidad;

    int Redimensionar();

    void EmpujarAbajo();

    void EmpujarArriba();

    //Type *elementos[capacidad];

}

#include "../Templates/Heap.tpp"

#endif //HEAP_HPP_INCLUDED

#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

template <typename Type, bool MaxOMin>
class Heap{
public:

    explicit Heap();

    Heap(const Heap &c);

    ~Heap();

    Heap & operator=(const Heap &c);

    void Agregar(Type valor);

    void Eliminar();
    
    Type ObtenerFrente() const;

    bool EstaVacia() const;

    void Vaciar();

    int CantElem() const;

    int CapMont() const; // Para pruebas
    
    void ImprimirElem() const; // Para pruebas

private:

    Type *elemento;

    int cantElem;
    int capacidad;
    int tope;

    int Redimensionar();

    void EmpujarArriba(int indice);

    void EmpujarAbajo(int indice);

};

#include "../Templates/Heap.tpp"

#endif //HEAP_HPP_INCLUDED

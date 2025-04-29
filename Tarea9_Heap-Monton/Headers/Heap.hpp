#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

#include <iostream>

// Funciones de comparación

// Mínimo (por default)
template <typename T>
bool minimo(const T& a, const T& b) {
    return a <= b;
}

// Máximo
template <typename T>
bool maximo(const T& a, const T& b) {
    return a >= b;
}

// Clase plantilla Heap
template <typename Type>
class Heap {
public:
    explicit Heap(bool (*cmp)(const Type&, const Type&) = minimo<Type>); // Constructor por default
    Heap(const Heap& c); // Constructor copia
    ~Heap(); // Destructor
    Heap& operator=(const Heap& c); // Operador asignación

    void Agregar(Type valor);
    void Eliminar();
    Type ObtenerFrente() const;
    bool EstaVacio() const;
    void Vaciar();
    int NumElem() const;
    int CapacidadHeap() const;
    void Imprimir() const;

private:
    Type* elementos;
    int capacidad;
    int ultimo;
    bool (*comparador)(const Type&, const Type&);

    void Redimensionar();
    void EmpujarArriba(int indice);
    void EmpujarAbajo(int indice);
};

#include "../Templates/Heap.tpp"

#endif // HEAP_HPP_INCLUDED

#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

// Plantilla de Heap: puede ser Max-Heap (MaxOMin=true) o Min-Heap (MaxOMin=false)
template <typename Type, bool MaxOMin>
class Heap {
public:

    explicit Heap(); // Constructor por defecto

    Heap(const Heap &c); // Constructor copia

    ~Heap(); // Destructor

    Heap& operator=(const Heap &c); // Operador asignación

    void Agregar(Type valor); // Agrega un nuevo elemento

    void Eliminar(); // Elimina el frente (raíz)

    Type ObtenerFrente() const; // Devuelve el elemento raíz

    bool EstaVacia() const; // Revisa si no hay elementos

    void Vaciar(); // Libera toda la memoria usada

    int CantElem() const; // Devuelve la cantidad de elementos actuales

    int CapMont() const; // Devuelve la capacidad actual (lo uso para pruebas)

    void ImprimirElem() const; // Imprime el contenido del heap (también para pruebas)

private:

    Type* elemento; // Arreglo dinámico donde guarda los elementos

    int cantElem; // Cantidad actual de elementos
    int capacidad; // Capacidad máxima actual
    int tope; // implementar que al eliminar mueva el tope y no elimine los elementos

    int Redimensionar(); // Duplica el tamaño del arreglo si hace falta

    void EmpujarArriba(int indice); // Sube un elemento para mantener la propiedad de heap

    void EmpujarAbajo(int indice); // Baja un elemento para mantener la propiedad de heap
};


#include "../Templates/Heap.tpp"

#endif // HEAP_HPP_INCLUDED


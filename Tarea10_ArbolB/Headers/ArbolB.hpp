#ifndef ARBOLB_HPP_INCLUDED
#define ARBOLB_HPP_INCLUDED

template <typename Type, int grado = 5>
class ArbolB {
public:

    explicit ArbolB(); // Constructor por defecto
    ArbolB(const ArbolB &c); // Constrctor de copia
    ~ArbolB(); // Destructor
    ArbolB& operator=(const ArbolB &c); // Operador asignación

    void Agregar(Type valor); // Agrega un nuevo elemento
    void Eliminar(Type valor); // Elimina el primer elemento con este valor

    void BuscarElem(); // Busca un elemento en el árbol
    int CantElem() const; // Devuelve la cantidad de elementos actuales

    void Vaciar(); // Vacía el árbol

    // Imprimir
    void ImprimirAsc() const;

    void ImprimirDes() const;

    void ImprimirNiveles() const;


private:

    int cantElem;

    struct Nodo{
        int elemNodo;

        Type claves[grado];

        Nodo * hijo[grado + 1];
    } *raiz;

    Nodo* CopiarArbol(Nodo* subraiz);

    void Agregar(Type valor, Nodo*subraiz);

    bool EsHoja(Nodo* nodo);

    // Método para dividir un nodo
    void dividirNodo(Nodo* padre, int i);

    void ImprimirAsc(Nodo* nodo, int nivel);
};

#include "../Templates/ArbolB.tpp"

#endif // ARBOLB_HPP_INCLUDED

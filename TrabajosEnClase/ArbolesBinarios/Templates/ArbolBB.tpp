#include "../Headers/ArbolBB.h"
#include "../Headers/Cola.hpp"

//Constructor
template <typename Type>
ArbolBB<Type>::ArbolBB(): numNodos(0), raiz(nullptr){}

template <typename Type>
ArbolBB<Type>::ArbolBB(const ArbolBB &ABB): numNodos(0), raiz(nullptr){
    *this = ABB;

}

template <typename Type>
ArbolBB<Type>::~ArbolBB(){
    Vaciar();
}

template <typename Type>
void ArbolBB<Type>::Vaciar(){
    Podar(raiz);
}

// Implementación del operador de asignación
template <typename Type>
ArbolBB<Type>& ArbolBB<Type>::operator=(const ArbolBB<Type> &ab) {
    // Verificamos si estamos intentando asignar el mismo objeto
    if (this == &ab) return *this;

    // Liberamos los nodos del árbol actual
    Vaciar();

    // Copiamos el árbol de 'ab' en este objeto
    if (ab.raiz != nullptr) {
        raiz = CopiarArbol(ab.raiz);
        numNodos = ab.numNodos;
    }

    return *this;
}

// Función auxiliar para copiar un árbol recursivamente
template <typename Type>
typename ArbolBB<Type>::Nodo* ArbolBB<Type>::CopiarArbol(Nodo* subraiz) {
    if (subraiz == nullptr) return nullptr;

    // Creamos un nuevo nodo para el valor del nodo actual
    Nodo* nuevoNodo = new Nodo(subraiz->valor);

    // Copiamos recursivamente los subárboles izquierdo y derecho
    nuevoNodo->hijoIzq = CopiarArbol(subraiz->hijoIzq);
    nuevoNodo->hijoDer = CopiarArbol(subraiz->hijoDer);

    return nuevoNodo;
}

template <typename Type>
void ArbolBB<Type>::Podar(Type valor){
    Nodo *& dirNodo = BuscarDir(valor, raiz);
    Podar(dirNodo);
}

template <typename Type>
void ArbolBB<Type>::Podar(Nodo *&subraiz){
    if(subraiz != nullptr){
        Podar(subraiz->hijoIzq);
        Podar(subraiz->hijoDer);
        delete subraiz;
        subraiz = nullptr;
        --numNodos;
    }
}

template <typename Type>
typename ArbolBB<Type>::Nodo *& ArbolBB<Type>::BuscarDir(Type valor, Nodo *&subraiz) const{

    if(subraiz != nullptr){
        if(valor < subraiz->valor) return BuscarDir(valor, subraiz->hijoIzq);
        else if(valor > subraiz->valor) return BuscarDir(valor, subraiz->hijoDer);
    }
    return subraiz;
}

template <typename Type>
void ArbolBB<Type>::Agregar(Type valor){
    Agregar(valor, raiz);
}

template <typename Type>
void ArbolBB<Type>::Agregar(Type valor, Nodo *&subraiz){
    if(subraiz == nullptr){
        subraiz = new Nodo(valor);
        ++numNodos;
    }else if(valor == subraiz->valor) return;
    else if(valor < subraiz->valor) Agregar(valor, subraiz->hijoIzq);
    else Agregar(valor,subraiz->hijoDer);

}

template <typename Type>
void ArbolBB<Type>::ImprimirAsc() const{
    ImprimirAsc(raiz);
}

template <typename Type>
void ArbolBB<Type>::ImprimirAsc(Nodo *subraiz) const{
    if(subraiz != nullptr){
        ImprimirAsc(subraiz->hijoIzq);
        std::cout << subraiz->valor << " ";
        ImprimirAsc(subraiz->hijoDer);
    }

}

template <typename Type>
void ArbolBB<Type>::ImprimirDec() const{
    ImprimirDec(raiz);
}

template <typename Type>
void ArbolBB<Type>::ImprimirDec(Nodo *subraiz) const{
    if(subraiz != nullptr){
        ImprimirDec(subraiz->hijoDer);
        std::cout << subraiz->valor << " ";
        ImprimirDec(subraiz->hijoIzq);
    }

}

template <typename Type>
void ArbolBB<Type>::ImprimirNiveles() const{
    if (raiz == nullptr) return;

    Queue<Nodo*> cola;
    cola.Enqueue(raiz);

    while (!cola.IsEmpty()) {
        Nodo* actual = cola.Front();
        cola.Dequeue();

        std::cout << actual->valor << " ";

        if (actual->hijoIzq != nullptr)
            cola.Enqueue(actual->hijoIzq);
        if (actual->hijoDer != nullptr)
            cola.Enqueue(actual->hijoDer);
    }




}


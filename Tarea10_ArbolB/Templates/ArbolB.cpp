/**
* @brief Constructor por defecto de la clse ArbolB
*
* Crea un árbolB
*/

#include "../Headers/ArbolB.hpp"
#include <iostream>
#include <stdexcept>

/**
* @brief Construye un árbolB vacío
*/
template <typename Type, int grado = 5>
ArbolB<Type, grado>::Arbol() : cantElem(0), raiz(nullptr) {}

/**
* @brief Construye un árbolB como copia de otro.
* @param c árbolB de origen para copia.
*/
template <typename Type, int grado = 5>
ArbolB<Type, grado>::ArbolB(const ArbolB *c) {
    *this = c;
}

/**
* @brief Destruye el árbolB, liberando todos los nodos y arreglos dentro de nodos
*/
template <typename Type, int grado = 5>
ArbolB<Type, grado>::~ArbolB() {
    Vaciar();
}

/**
* @brief Asigna los contenidos de otro árbolB a este.
* @param c árbol de origen.
* @return Referencia al árbol asignado.
*/
template <typename Type, int grado = 5>
ArbolB<Type, grado>& ArbolB<Type, grado>::operator=(const ArbolB<Type, grado> &c) {
    if(this == &c) return *this;

    Vaciar();
    if(c.raiz != nullptr) {
        raiz = CopiarArbol(c.raiz);
        cantElem = c.cantElem;
    }

    return *this;
}

/**
* @brief
*/
template<typename Type, int grado = 5>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::CopiarArbol(Nodo* subraiz) {
    if(subraiz == nullptr)
        return nullptr;
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->elemNodo = subraiz->elemNodo;

    // Copiamos las claves del nodo
    for(int i = 0 ; i < subraiz->claves ; ++i) {
        nuevoNodo->claves[i] = subraiz->claves[i];
    }

    // Copiamos recursivamente los hijos del nodo
    for(int i = 0 ; i < subraiz->claves ; ++i) {
        nuevoNodo->hijo[i] = CopiarArbol(subraiz->hijo[i]);
    }

    return nuevoNodo;
}

template <typename Type, int grado = 5>
void ArbolB<Type, grado>::Agregar(Type valor) {
    Agregar(valor, raiz);
}

template <typename Type, int grado = 5>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    
}

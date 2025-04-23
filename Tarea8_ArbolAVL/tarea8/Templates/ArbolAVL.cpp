/**
 * @file ArbolAVL.tpp
 * @brief Implementación de los métodos de la clase ArbolAVL.
 *
 * Este archivo contiene las definiciones de las funciones miembro de la
 * clase ArbolAVL declaradas en ArbolAVL.hpp, incluyendo operaciones de
 * inserción, eliminación, búsqueda, recorrido y balanceo (rotaciones).
 */

#include "../Headers/ArbolAVL.hpp"
#include "../Headers/Cola.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

// Constructor por defecto
/**
 * @brief Construye un árbol AVL vacío.
 */
template <typename Type>
ArbolAVL<Type>::ArbolAVL(): numNodos(0), raiz(nullptr) {}

// Constructor de copia
/**
 * @brief Construye un árbol AVL como copia de otro.
 * @param AVL Árbol AVL de origen para copia.
 */
template <typename Type>
ArbolAVL<Type>::ArbolAVL(const ArbolAVL &AVL): numNodos(0), raiz(nullptr) {
    *this = AVL;
}

// Destructor
/**
 * @brief Destruye el árbol AVL, liberando todos los nodos.
 */
template <typename Type>
ArbolAVL<Type>::~ArbolAVL() {
    Vaciar();
}

// Vaciar árbol
/**
 * @brief Elimina todos los nodos del árbol.
 */
template <typename Type>
void ArbolAVL<Type>::Vaciar() {
    Podar(raiz);
}

// Operador de asignación
/**
 * @brief Asigna los contenidos de otro árbol AVL a este.
 * @param AVL Árbol de origen.
 * @return Referencia al árbol asignado.
 */
template <typename Type>
ArbolAVL<Type>& ArbolAVL<Type>::operator=(const ArbolAVL<Type> &AVL) {
    if (this == &AVL)
        return *this;

    Vaciar();
    if (AVL.raiz != nullptr) {
        raiz = CopiarArbol(AVL.raiz);
        numNodos = AVL.numNodos;
    }
    return *this;
}

// Copiar árbol recursivamente
/**
 * @brief Copia recursivamente un subárbol.
 * @param subraiz Puntero a la raíz del subárbol a copiar.
 * @return Puntero a la nueva raíz copiada.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo* ArbolAVL<Type>::CopiarArbol(Nodo* subraiz) {
    if (subraiz == nullptr)
        return nullptr;
    Nodo* nuevoNodo = new Nodo(subraiz->valor);
    nuevoNodo->hijoIzq = CopiarArbol(subraiz->hijoIzq);
    nuevoNodo->hijoDer = CopiarArbol(subraiz->hijoDer);
    return nuevoNodo;
}

// Podar subárbol
/**
 * @brief Libera los nodos de un subárbol.
 * @param subraiz Raíz del subárbol a eliminar.
 */
template <typename Type>
void ArbolAVL<Type>::Podar(Nodo *subraiz) {
    if (subraiz != nullptr) {
        Podar(subraiz->hijoIzq);
        Podar(subraiz->hijoDer);
        delete subraiz;
        subraiz = nullptr;
        --numNodos;
    }
}

// Buscar dirección para inserción o eliminación
/**
 * @brief Encuentra la referencia al puntero donde debería ubicarse un valor.
 * @param valor Valor a buscar.
 * @param subraiz Subárbol en el que se busca.
 * @return Referencia al puntero del nodo encontrado o al lugar de inserción.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::BuscarDir(Type valor, Nodo *&subraiz) const {
    if (subraiz != nullptr) {
        if (valor < subraiz->valor)
            return BuscarDir(valor, subraiz->hijoIzq);
        else if (valor > subraiz->valor)
            return BuscarDir(valor, subraiz->hijoDer);
    }
    return subraiz;
}

// Agregar valor
/**
 * @brief Inserta un valor en el árbol.
 * @param valor Valor a insertar.
 */
template <typename Type>
void ArbolAVL<Type>::Agregar(Type valor) {
    Agregar(valor, raiz);
}

/**
 * @brief Inserta un valor en un subárbol dado y lo balancea.
 * @param valor Valor a insertar.
 * @param subraiz Subárbol donde se insertará.
 */
template <typename Type>
void ArbolAVL<Type>::Agregar(Type valor, Nodo *&subraiz) {
    if (subraiz == nullptr) {
        subraiz = new Nodo(valor);
        ++numNodos;
    } else if (valor == subraiz->valor) {
        return;
    } else if (valor < subraiz->valor) {
        Agregar(valor, subraiz->hijoIzq);
    } else {
        Agregar(valor, subraiz->hijoDer);
    }
    if (subraiz != nullptr) {
        subraiz = Balancear(subraiz);
    }
}

// Eliminar valor
/**
 * @brief Elimina un valor del árbol si existe.
 * @param valor Valor a eliminar.
 */
template <typename Type>
void ArbolAVL<Type>::Eliminar(Type valor) {
    Eliminar(valor, raiz);
}

/**
 * @brief Elimina un valor de un subárbol dado y lo balancea.
 * @param valor Valor a eliminar.
 * @param subraiz Subárbol donde se eliminará.
 */
template <typename Type>
void ArbolAVL<Type>::Eliminar(Type valor, Nodo *&subraiz) {
    if (subraiz == nullptr)
        return;
    if (valor < subraiz->valor) {
        Eliminar(valor, subraiz->hijoIzq);
    } else if (valor > subraiz->valor) {
        Eliminar(valor, subraiz->hijoDer);
    } else {
        // Caso hoja
        if (subraiz->hijoIzq == nullptr && subraiz->hijoDer == nullptr) {
            delete subraiz;
            subraiz = nullptr;
            --numNodos;
        }
        // Caso un solo hijo
        else if (subraiz->hijoIzq == nullptr) {
            Nodo* temp = subraiz;
            subraiz = subraiz->hijoDer;
            delete temp;
            --numNodos;
        } else if (subraiz->hijoDer == nullptr) {
            Nodo* temp = subraiz;
            subraiz = subraiz->hijoIzq;
            delete temp;
            --numNodos;
        }
        // Caso dos hijos
        else {
            Nodo* sucesor = BuscarSucesor(subraiz->hijoDer);
            subraiz->valor = sucesor->valor;
            Eliminar(sucesor->valor, subraiz->hijoDer);
        }
    }
    if (subraiz != nullptr) {
        subraiz = Balancear(subraiz);
    }
}

// Buscar sucesor in-order
/**
 * @brief Encuentra el sucesor in-order en un subárbol.
 * @param subraiz Raíz del subárbol derecho.
 * @return Nodo sucesor (mínimo valor del subárbol).
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo* ArbolAVL<Type>::BuscarSucesor(Nodo* subraiz) const {
    while (subraiz && subraiz->hijoIzq) {
        subraiz = subraiz->hijoIzq;
    }
    return subraiz;
}

// Búsqueda iterativa
/**
 * @brief Busca un valor en el árbol.
 * @param valor Valor a buscar.
 * @return true si se encontró, false en caso contrario.
 */
template <typename Type>
bool ArbolAVL<Type>::Buscar(Type valor) const {
    Nodo* actual = raiz;
    while (actual) {
        if (valor == actual->valor)
            return true;
        else if (valor < actual->valor)
            actual = actual->hijoIzq;
        else
            actual = actual->hijoDer;
    }
    return false;
}

// Obtener número de nodos
/**
 * @brief Devuelve el conteo de nodos actuales.
 * @return Número de nodos.
 */
template <typename Type>
int ArbolAVL<Type>::NumNodos() const {
    return numNodos;
}

// Obtener valor máximo y mínimo
/**
 * @brief Devuelve el valor máximo en el árbol.
 * @return Valor máximo.
 * @throws std::runtime_error si el árbol está vacío.
 */
template <typename Type>
Type ArbolAVL<Type>::ObtenerMayor() const {
    Nodo* actual = raiz;
    if (!actual) throw std::runtime_error("árbol vacío");
    while (actual->hijoDer) actual = actual->hijoDer;
    return actual->valor;
}

/**
 * @brief Devuelve el valor mínimo en el árbol.
 * @return Valor mínimo.
 * @throws std::runtime_error si el árbol está vacío.
 */
template <typename Type>
Type ArbolAVL<Type>::ObtenerMenor() const {
    Nodo* actual = raiz;
    if (!actual) throw std::runtime_error("árbol vacío");
    while (actual->hijoIzq) actual = actual->hijoIzq;
    return actual->valor;
}

// Altura del árbol
/**
 * @brief Calcula la altura total del árbol.
 * @return Altura (número de niveles).
 */
template <typename Type>
int ArbolAVL<Type>::AlturaArbol() const {
    return AlturaArbol(raiz);
}

/**
 * @brief Calcula la altura de un subárbol.
 * @param subraiz Raíz del subárbol.
 * @return Altura desde subraiz.
 */
template <typename Type>
int ArbolAVL<Type>::AlturaArbol(Nodo* subraiz) const {
    if (!subraiz) return 0;
    int izq = AlturaArbol(subraiz->hijoIzq);
    int der = AlturaArbol(subraiz->hijoDer);
    return 1 + std::max(izq, der);
}

// Impresión en orden ascendente y descendente
/**
 * @brief Imprime valores en orden ascendente.
 */
template <typename Type>
void ArbolAVL<Type>::ImprimirAsc() const {
    ImprimirAsc(raiz);
}

/**
 * @brief Imprime recursivamente en orden ascendente.
 * @param subraiz Raíz del subárbol.
 */
template <typename Type>
void ArbolAVL<Type>::ImprimirAsc(Nodo* subraiz) const {
    if (subraiz) {
        ImprimirAsc(subraiz->hijoIzq);
        std::cout << subraiz->valor << " ";
        ImprimirAsc(subraiz->hijoDer);
    }
}

/**
 * @brief Imprime valores en orden descendente.
 */
template <typename Type>
void ArbolAVL<Type>::ImprimirDec() const {
    ImprimirDec(raiz);
}

/**
 * @brief Imprime recursivamente en orden descendente.
 * @param subraiz Raíz del subárbol.
 */
template <typename Type>
void ArbolAVL<Type>::ImprimirDec(Nodo* subraiz) const {
    if (!subraiz) return;
    ImprimirDec(subraiz->hijoDer);
    std::cout << subraiz->valor << " ";
    ImprimirDec(subraiz->hijoIzq);
}

// Impresión por niveles
/**
 * @brief Imprime los valores del árbol nivel por nivel.
 */
template <typename Type>
void ArbolAVL<Type>::ImprimirNiveles() const {
    if (!raiz) return;
    Cola<Nodo*> cola;
    cola.Encolar(raiz);
    while (!cola.EstaVacia()) {
        Nodo* actual = cola.ConocerPrim(); cola.Desencolar();
        std::cout << actual->valor << " ";
        if (actual->hijoIzq) cola.Encolar(actual->hijoIzq);
        if (actual->hijoDer) cola.Encolar(actual->hijoDer);
    }
}

// Balanceo y rotaciones
/**
 * @brief Balancea un subárbol usando rotaciones.
 * @param subraiz Raíz del subárbol.
 * @return Nueva raíz balanceada.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::Balancear(Nodo *&subraiz) {
    int fb = FactorBalance(subraiz);
    if (fb == 2) {
        int fbDer = FactorBalance(subraiz->hijoDer);
        if (fbDer >= 0) return RSI(subraiz);
        else return RDI(subraiz);
    } else if (fb == -2) {
        int fbIzq = FactorBalance(subraiz->hijoIzq);
        if (fbIzq <= 0) return RSD(subraiz);
        else return RDD(subraiz);
    }
    return subraiz;
}

/**
 * @brief Calcula el factor de balance de un nodo.
 * @param subraiz Nodo a evaluar.
 * @return Altura derecha menos altura izquierda.
 */
template <typename Type>
int ArbolAVL<Type>::FactorBalance(Nodo *subraiz) {
    if (!subraiz) return 0;
    return AlturaArbol(subraiz->hijoDer) - AlturaArbol(subraiz->hijoIzq);
}

/**
 * @brief Rotación simple a la izquierda.
 * @param x Subárbol a rotar.
 * @return Nueva raíz tras la rotación.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::RSI(Nodo *&x) {
    Nodo *y = x->hijoDer;
    Nodo *b = y->hijoIzq;
    x->hijoDer = b;
    y->hijoIzq = x;
    x = y;
    return x;
}

/**
 * @brief Rotación simple a la derecha.
 * @param x Subárbol a rotar.
 * @return Nueva raíz tras la rotación.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::RSD(Nodo *&x) {
    Nodo *y = x->hijoIzq;
    Nodo *b = y->hijoDer;
    x->hijoIzq = b;
    y->hijoDer = x;
    x = y;
    return x;
}

/**
 * @brief Rotación doble a la izquierda.
 * @param x Subárbol a rotar.
 * @return Nueva raíz tras la rotación.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::RDI(Nodo *&x) {
    RSD(x->hijoDer);
    return RSI(x);
}

/**
 * @brief Rotación doble a la derecha.
 * @param x Subárbol a rotar.
 * @return Nueva raíz tras la rotación.
 */
template <typename Type>
typename ArbolAVL<Type>::Nodo*& ArbolAVL<Type>::RDD(Nodo *&x) {
    RSI(x->hijoIzq);
    return RSD(x);
}


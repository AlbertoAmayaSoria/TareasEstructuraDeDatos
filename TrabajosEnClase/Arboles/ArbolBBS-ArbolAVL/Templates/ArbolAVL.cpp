#include "../Headers/ArbolAVL.hpp"
#include "../Headers/Cola.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

// Constructor
template <typename Type>
ArbolAVL<Type>::ArbolAVL(): numNodos(0), raiz(nullptr){}

template <typename Type>
ArbolAVL<Type>::ArbolAVL(const ArbolAVL &AVL): numNodos(0), raiz(nullptr){
    *this = AVL;
}

template <typename Type>
ArbolAVL<Type>::~ArbolAVL(){
    Vaciar();
}

template <typename Type>
void ArbolAVL<Type>::Vaciar(){
    Podar(raiz);
}

// Implementación del operador de asignación 
template <typename Type>
ArbolAVL<Type>& ArbolAVL<Type>::operator=(const ArbolAVL<Type> &AVL){
    // Verificamos si estamos intentando asignar el mismo objeto
    if(this == &AVL) return *this;

    // Liberamos los nodos del árbol actual
    Vaciar();

    // Copiamos el árbol de "AVL" a este objeto
    if(AVL.raiz != nullptr){
        raiz = CopiarArbol(AVL.raiz);
        numNodos = AVL.numNodos;
    }

    return *this;
}

// Función auxiliar par copiar el árbol recursivamente
template <typename Type>
typename ArbolAVL<Type>::Nodo* ArbolAVL<Type>::CopiarArbol(Nodo* subraiz) {
    if(subraiz == nullptr) return nullptr;

    // Creamos un nuevo nodo para el valor del nodo actual
    Nodo* nuevoNodo = new Nodo(subraiz->valor);

    // Copiamos recursivamente los subárbole izquierdo y derecho
    nuevoNodo->hijoIzq = CopiarArbol(subraiz->hijoIzq);
    nuevoNodo->hijoDer = CopiarArbol(subraiz->hijoDer);

    return nuevoNodo;
}

template <typename Type>
void ArbolAVL<Type>::Podar(Nodo *subraiz) {
    if(subraiz != nullptr) {
        Podar(subraiz->hijoIzq);
        Podar(subraiz->hijoDer);
        delete subraiz;
        subraiz = nullptr;
        --numNodos;
    }
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::BuscarDir(Type valor, Nodo *&subraiz) const {
    
    if(subraiz != nullptr) {
        if(valor < subraiz->valor) return BuscarDir(valor, subraiz->hijoIzq);
        else if(valor > subraiz->valor) return BuscarDir(valor, subraiz->hijoDer);
    }
    return subraiz;
}

template <typename Type>
void ArbolAVL<Type>::Agregar(Type valor) {
    Agregar(valor, raiz);
}

template <typename Type>
void ArbolAVL<Type>::Agregar(Type valor, Nodo *&subraiz) {
    if(subraiz == nullptr) {
        subraiz = new Nodo(valor);
        ++numNodos;
    }else if(valor == subraiz->valor) return;
    else if(valor < subraiz->valor) Agregar(valor, subraiz->hijoIzq);
    else Agregar(valor, subraiz->hijoDer);

    if(subraiz != nullptr){
        subraiz = Balancear(subraiz);
    }
}

template <typename Type>
void ArbolAVL<Type>::Eliminar(Type valor) {
    Eliminar(valor, raiz);
}

template <typename Type>
void ArbolAVL<Type>::Eliminar(Type valor, Nodo *&subraiz) {
    if(subraiz == nullptr) return;
    
    if(valor < subraiz->valor){
        Eliminar(valor, subraiz->hijoIzq);
    } else if(valor > subraiz->valor) {
        Eliminar(valor, subraiz->hijoDer);
    }
    else {
        // Caso 1: El nodo a eliminar es una hoja (sin hijos)
        if(subraiz->hijoIzq == nullptr && subraiz ->hijoDer == nullptr){
            delete subraiz;
            subraiz = nullptr;
            --numNodos;
        }
        // Caso 2: El nodo a eliminar tiene un solo hijo
        else if(subraiz->hijoIzq == nullptr) {
            Nodo* temp = subraiz;
            subraiz = subraiz->hijoDer;
            delete temp;
            --numNodos;
        }
        else if(subraiz->hijoDer == nullptr) {
            Nodo* temp = subraiz;
            subraiz = subraiz->hijoIzq;
            delete temp;
            --numNodos;
        }
        // Caso 3: 
        else {
            // Buscamos el sucesor in-orden (el nodo más pequeño en el subárbolderecho)
            Nodo* sucesor = BuscarSucesor(subraiz->hijoDer);
            // Remplazamos el valor del nodo a eliminar por el sucesor
            subraiz->valor = sucesor->valor;
            // Eliminamos el sucesor
            Eliminar(sucesor->valor, subraiz->hijoDer);
        }
    }

    if(subraiz != nullptr) {
        subraiz = Balancear(subraiz);
    }
}

// Método auxiliar para encontrar el sucesor in-order (el nodo más pequeño en el subárbol derecho)
template <typename Type>
typename ArbolAVL<Type>::Nodo* ArbolAVL<Type>::BuscarSucesor(Nodo* subraiz) const{
    while(subraiz != nullptr && subraiz->hijoIzq != nullptr){
        subraiz = subraiz->hijoIzq;
    }
    return subraiz;
}

template <typename Type>
bool ArbolAVL<Type>::Buscar(Type valor)const {
    Nodo* actual = raiz;
    while (actual != nullptr) {
        if (valor == actual->valor) return true;
        else if (valor < actual->valor) actual = actual->hijoIzq;
        else actual = actual->hijoDer;
    }
    return false;
}

template <typename Type>
int ArbolAVL<Type>::NumNodos() const {
    return numNodos;
}

template <typename Type>
Type ArbolAVL<Type>::ObtenerMayor() const {
    Nodo* actual = raiz;
    if(!actual) throw std::runtime_error("árbol vacío");
    while (actual->hijoDer) {
        actual = actual->hijoDer;
    }

    return actual->valor;
}

template <typename Type>
Type ArbolAVL<Type>::ObtenerMenor() const{
    Nodo* actual = raiz;
    if(!raiz) throw std::runtime_error("árbol vacío");
    while (actual->hijoIzq) {
        actual = actual->hijoIzq;       
    }
    return actual->valor;
}

template <typename Type>
int ArbolAVL<Type>::AlturaArbol() const {
    return AlturaArbol(raiz);
}

// Función auxiliar revursiva
template <typename Type>
int ArbolAVL<Type>::AlturaArbol(Nodo* subraiz) const{
    if(subraiz == nullptr) return 0;

    int alturaIzq = AlturaArbol(subraiz->hijoIzq);
    int alturaOer = AlturaArbol(subraiz->hijoDer);

    return 1 + std::max(alturaIzq, alturaOer);
}

template <typename Type>
void ArbolAVL<Type>::ImprimirAsc() const {
   ImprimirAsc(raiz); 
}

template <typename Type>
void ArbolAVL<Type>::ImprimirAsc(Nodo* subraiz) const {
    if(subraiz != nullptr) {
        ImprimirAsc(subraiz->hijoIzq);
        std::cout << subraiz->valor << " ";
        ImprimirAsc(subraiz->hijoDer);
    }
}

template <typename Type>
void ArbolAVL<Type>::ImprimirDec() const {
    ImprimirDec(raiz);
}

template <typename Type>
void ArbolAVL<Type>::ImprimirDec(Nodo* subraiz) const {
    if(subraiz == nullptr) return;
    ImprimirDec(subraiz->hijoDer);
    std::cout << subraiz->valor << " ";
    ImprimirDec(subraiz->hijoIzq);
}

template <typename Type>
void ArbolAVL<Type>::ImprimirNiveles() const {
    if(raiz == nullptr) return;

    Queue<Nodo*> cola;
    cola.Enqueue(raiz);

    while(!cola.IsEmpty()) {
        Nodo* actual = cola.Front();
        cola.Dequeue();

        std::cout << actual->valor << " ";

        if(actual->hijoIzq != nullptr)
            cola.Enqueue(actual->hijoIzq);
        if(actual->hijoDer != nullptr)
            cola.Enqueue(actual->hijoDer);
    }
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::Balancear(Nodo *&subraiz) {
    if(FactorBalance(subraiz) == 2 && FactorBalance(subraiz->hijoDer) == 1) return RSI(subraiz);
    if(FactorBalance(subraiz) == 2 && FactorBalance(subraiz->hijoDer) == 0) return RSI(subraiz);
    if(FactorBalance(subraiz) == 2 && FactorBalance(subraiz->hijoDer) == -1) return RDI(subraiz);
    if(FactorBalance(subraiz) == -2 && FactorBalance(subraiz->hijoIzq) == -1) return RSD(subraiz);
    if(FactorBalance(subraiz) == -2 && FactorBalance(subraiz->hijoIzq) == 0) return RSD(subraiz);
    if(FactorBalance(subraiz) == -2 && FactorBalance(subraiz->hijoIzq) == 1) return RDD(subraiz); 

    return subraiz;
}

template <typename Type>
int ArbolAVL<Type>::FactorBalance(Nodo *subraiz) {
    if(subraiz == nullptr) return 0;
    return AlturaArbol(subraiz->hijoDer)-AlturaArbol(subraiz->hijoIzq);
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::RSI(Nodo *&x) {
    Nodo *y = x->hijoDer;
    Nodo *b = y->hijoIzq;
    x->hijoDer = b;
    y->hijoIzq = x;
    x = y;

    return x;
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::RSD(Nodo *&x) {
    Nodo *y = x->hijoIzq;
    Nodo *b = y->hijoDer;
    x->hijoIzq = b;
    y->hijoDer = x;
    x = y;

    return x;
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::RDI(Nodo *&x) {
    RSD(x->hijoDer);
    return RSI(x);
}

template <typename Type>
typename ArbolAVL<Type>::Nodo *& ArbolAVL<Type>::RDD(Nodo *&x) {
    RSI(x->hijoIzq);
    return RSD(x);
}


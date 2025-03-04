#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept> // Para manejar excepciones

template <typename T>
class ListaDoblementeEnlazada {
public:
    //  Constructores y destructor
    //  Constructor
    ListaDoblementeEnlazada();
    //  Constructor de copias
    ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra);
    //  Destructor
    ~ListaDoblementeEnlazada();
    //  Sobrecarga del operador =
    ListaDoblementeEnlazada& operator=(const ListaDoblementeEnlazada& otra);


    //  Métodos de inserción
    void insertarInicio(T valor);
    void insertarFinal(T valor);
    void insertarPosicion(T valor, size_t pos);


    // Métodos de eliminación
    void eliminarInicio();
    void eliminarFinal();
    void eliminarPosicion(size_t pos);
    void eliminarValor(T valor);
    void eliminarTodasOcurrencias(T valor); 
    void eliminarPorCondicion(bool (*condicion)(T));
    void eliminarElementosRepetidos(); 


    // Método de búsqueda
    bool buscar(T valor) const; 


    // Métodos para obtener datos
    bool estaVacia() const;
    T obtenerPrimero() const;
    T obtenerUltimo() const;
    T obtenerEnPosicion(size_t posicion) const;
    int obtenerIndice(const T& valor) const;

    // Métodos para modificar
    void modificarEnPosicion(size_t posicion, T nuevoValor);


    // Métodos para el tamaño de la lista
    size_t obtenerTamaño() const;
    void vaciar();


    // Métodos de impresión
    void imprimir() const;
    void imprimirReversa() const;


    // Operadores sobrecargados
    T& operator[](size_t index);
    const T& operator[](size_t index) const;


    // Métodos adicionales
    void ordenarAscendente();
    void intercambiar(ListaDoblementeEnlazada<T>& otra);
    void transferirElementos(ListaDoblementeEnlazada<T>& otra, size_t inicio, size_t fin);
    void transferirDesdeIndice(ListaDoblementeEnlazada<T>& otra, size_t indice); 
    void transferirTodos(ListaDoblementeEnlazada<T>& otra);

private:
    struct Nodo {
        //  dato del nodo
        T dato;
        //  puntero al nodo anterior
        Nodo* anterior;
        //  puntero al nodo siguiente
        Nodo* siguiente;
        // constructor de la estructura nodo 
        Nodo(T valor) : dato(valor), anterior(nullptr), siguiente(nullptr) {}
    };
    //  Puntero al primer nodo
    Nodo* primero;
    //  Puntero al ultimo nodo
    Nodo* ultimo;
    //  Tamaño de la lista
    size_t tamaño; 
};

// Implementación de métodos en el archivo .tpp
#include "../Templates/ListaDoblementeEnlazada.tpp"

#endif // LINKEDLIST_HPP


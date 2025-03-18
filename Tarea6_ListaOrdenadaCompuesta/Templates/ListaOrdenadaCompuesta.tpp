#include "../Headers/ListaOrdenadaCompuesta.hpp"
#include <iostream>

// Constructor por defecto
template <typename T>
ListaOrdenadaCompuesta<T>::ListaOrdenadaCompuesta() {
    // Inicialización de la lista interna
}

// Destructor
template <typename T>
ListaOrdenadaCompuesta<T>::~ListaOrdenadaCompuesta() {
    // Vaciamos la lista para liberar la memoria
    vaciar();
}

// Constructor de copias
template <typename T>
ListaOrdenadaCompuesta<T>::ListaOrdenadaCompuesta(const ListaOrdenadaCompuesta<T>& otra) {
    // Copiamos los elementos de la otra lista a la lista interna
    size_t size = otra.lista.obtenerTamaño();
    for (size_t i = 0; i < size; i++) {
        this->insertar(otra.lista.obtenerEnPosicion(i));  // Usamos el método insertar para agregar elementos en orden
    }
}

// Sobrecarga del operador =
template <typename T>
ListaOrdenadaCompuesta<T>& ListaOrdenadaCompuesta<T>::operator=(const ListaOrdenadaCompuesta<T>& otra) {
    if (this != &otra) {  // Evitar la autoasignación
        // Primero vaciamos la lista actual
        vaciar();
        // Luego copiamos los elementos de la otra lista a la lista interna
        size_t size = otra.lista.obtenerTamaño();
        for (size_t i = 0; i < size; i++) {
            this->insertar(otra.lista.obtenerEnPosicion(i));  // Usamos el método insertar para agregar elementos en orden
        }
    }
    return *this;  // Devolvemos la referencia al objeto actual
}

// Método para insertar un valor de forma ordenada
template <typename T>
void ListaOrdenadaCompuesta<T>::insertar(T valor) {
    size_t size = lista.obtenerTamaño();
    if (size == 0) {
        lista.insertarInicio(valor); // Si la lista está vacía, insertamos al inicio
    } else {
        size_t i = 0;
        while (i < size && valor > lista.obtenerEnPosicion(i)) {
            i++; // Encontramos la posición correcta para insertar el valor
        }
        lista.insertarPosicion(valor, i); // Insertamos el valor en la posición encontrada
    }
}

// Método para eliminar la primera ocurrencia de un valor
template <typename T>
void ListaOrdenadaCompuesta<T>::eliminar(T valor) {
    int indice = lista.obtenerIndice(valor); // Buscamos la primera ocurrencia
    if (indice != -1) {
        lista.eliminarPosicion(indice); // Eliminamos el valor en el índice encontrado
    }
}

// Método para buscar un valor en la lista
template <typename T>
bool ListaOrdenadaCompuesta<T>::buscar(T valor) {
    return lista.buscar(valor); // Usamos el método de búsqueda de la lista interna
}

// Método para vaciar la lista
template <typename T>
void ListaOrdenadaCompuesta<T>::vaciar() {
    while (!estaVacia()) {
        lista.eliminarInicio(); // Eliminamos el primer nodo hasta que la lista esté vacía
    }
}

// Método para verificar si la lista está vacía
template <typename T>
bool ListaOrdenadaCompuesta<T>::estaVacia() const {
    return lista.obtenerTamaño() == 0; // Verificamos si el tamaño de la lista es 0
}

// Método para obtener el tamaño de la lista
template <typename T>
size_t ListaOrdenadaCompuesta<T>::tamaño() const {
    return lista.obtenerTamaño(); // Devolvemos el tamaño de la lista interna
}

// Método para imprimir la lista en orden
template <typename T>
void ListaOrdenadaCompuesta<T>::imprimir() const {
    lista.imprimir(); // Usamos el método de impresión de la lista interna
}

// Método para imprimir la lista en orden inverso
template <typename T>
void ListaOrdenadaCompuesta<T>::imprimirReversa() const {
    lista.imprimirReversa(); // Usamos el método de impresión en reversa de la lista interna
}

// Método para mezclar dos listas ordenadas
template <typename T>
ListaOrdenadaCompuesta<T> ListaOrdenadaCompuesta<T>::mezclar(const ListaOrdenadaCompuesta<T>& otra) {
    ListaOrdenadaCompuesta<T> resultado;
    size_t i = 0, j = 0;
    size_t size1 = this->lista.obtenerTamaño();
    size_t size2 = otra.lista.obtenerTamaño();
    
    while (i < size1 && j < size2) {
        if (this->lista.obtenerEnPosicion(i) < otra.lista.obtenerEnPosicion(j)) {
            resultado.insertar(this->lista.obtenerEnPosicion(i));
            i++;
        } else {
            resultado.insertar(otra.lista.obtenerEnPosicion(j));
            j++;
        }
    }
    
    while (i < size1) {
        resultado.insertar(this->lista.obtenerEnPosicion(i));
        i++;
    }
    
    while (j < size2) {
        resultado.insertar(otra.lista.obtenerEnPosicion(j));
        j++;
    }
    
    return resultado;
}

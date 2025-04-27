#ifndef VECTORREDIM_TPP
#define VECTORREDIM_TPP

#include <algorithm>  // Para std::copy

template <typename T>
vectorRedim<T>::vectorRedim() : tamanoActual(0), capacidadActual(2) {
    // Inicializar el arreglo dinámico con capacidad 2 (inicial)
    datos = new T[capacidadActual];
}

template <typename T>
vectorRedim<T>::~vectorRedim() {
    delete[] datos;  // Liberar la memoria cuando el objeto sea destruido
}

template <typename T>
void vectorRedim<T>::insertar(const T& valor) {
    // Si el vector está lleno, redimensionamos
    if (tamanoActual == capacidadActual) {
        redimensionar();
    }

    // Insertar el valor al final
    datos[tamanoActual++] = valor;
}

template <typename T>
T& vectorRedim<T>::operator[](size_t index) {
    if (index >= tamanoActual) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return datos[index];
}

template <typename T>
const T& vectorRedim<T>::operator[](size_t index) const {
    if (index >= tamanoActual) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return datos[index];
}

template <typename T>
int vectorRedim<T>::tamano() const {
    return tamanoActual;
}

template <typename T>
int vectorRedim<T>::capacidad() const {
    return capacidadActual;
}

template <typename T>
bool vectorRedim<T>::vacio() const {
    return tamanoActual == 0;
}

template <typename T>
void vectorRedim<T>::redimensionar() {
    // Duplicamos la capacidad actual
    capacidadActual *= 2;

    // Creamos un nuevo arreglo con la nueva capacidad
    Type* nuevoDatos = new Type[capacidadActual];

    // Copiamos los datos actuales al nuevo arreglo
    std::copy(datos, datos + tamanoActual, nuevoDatos); //crear operador =

    // Liberamos la memoria del arreglo antiguo
    delete[] datos;

    // Apuntamos a la nueva área de memoria
    datos = nuevoDatos;
}

#endif // VECTORREDIM_TPP


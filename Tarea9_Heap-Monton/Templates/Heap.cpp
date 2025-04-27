#include <iostream>

/**
 * @brief Constructor por defecto de la clase Heap.
 * 
 * Crea un heap con una capacidad inicial de 31 elementos.
 */
template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::Heap() : cantElem(0), capacidad(31), tope(-1) {
    elemento = new Type[capacidad];
}

/**
 * @brief Constructor de copia de la clase Heap.
 * 
 * @param c Heap a copiar.
 */
template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::Heap(const Heap<Type, MaxOMin>& c) {
    *this = c;
}

/**
 * @brief Destructor de la clase Heap.
 * 
 * Libera la memoria utilizada por el heap.
 */
template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::~Heap() {
    Vaciar();
}

/**
 * @brief Sobrecarga del operador de asignación.
 * 
 * @param c Heap a asignar.
 * @return Referencia al objeto actual.
 */
template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>& Heap<Type, MaxOMin>::operator=(const Heap<Type, MaxOMin>& c) {
    if (this == &c) return *this; // Evitar autoasignación

    Vaciar();

    capacidad = c.capacidad;
    cantElem = c.cantElem;
    elemento = new Type[capacidad];

    for (int i = 0; i < cantElem; ++i) {
        elemento[i] = c.elemento[i];
    }

    return *this;
}

/**
 * @brief Agrega un elemento al heap.
 * 
 * @param valor Valor a agregar.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Agregar(Type valor) {
    if (cantElem >= capacidad) {
        Redimensionar();
    }

    elemento[cantElem] = valor;
    cantElem++;

    int i = cantElem - 1;
    EmpujarArriba(i);
}

/**
 * @brief Elimina el elemento raíz del heap.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Eliminar() {
    if (EstaVacia()) {
        std::cout << "El heap está vacío, no se puede eliminar." << std::endl;
        return;
    }

    elemento[0] = elemento[cantElem - 1];
    cantElem--;
    EmpujarAbajo(0);
}

/**
 * @brief Obtiene el elemento raíz del heap.
 * 
 * @return Elemento en la raíz del heap.
 * @throws std::out_of_range si el heap está vacío.
 */
template <typename Type, bool MaxOMin>
Type Heap<Type, MaxOMin>::ObtenerFrente() const {
    if (EstaVacia()) {
        std::cerr << "El heap está vacío, no se puede obtener el frente." << std::endl;
        throw std::out_of_range("El heap está vacío");
    }
    return elemento[0];
}

/**
 * @brief Verifica si el heap está vacío.
 * 
 * @return true si el heap no tiene elementos, false en caso contrario.
 */
template <typename Type, bool MaxOMin>
bool Heap<Type, MaxOMin>::EstaVacia() const {
    return cantElem == 0;
}

/**
 * @brief Vacía el heap, liberando la memoria.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Vaciar() {
    delete[] elemento;
    elemento = nullptr;
    cantElem = 0;
    capacidad = 0;
}

/**
 * @brief Devuelve la cantidad de elementos en el heap.
 * 
 * @return Cantidad de elementos.
 */
template <typename Type, bool MaxOMin>
int Heap<Type, MaxOMin>::CantElem() const {
    return cantElem;
}

/**
 * @brief Devuelve la capacidad máxima del heap.
 * 
 * @return Capacidad actual del arreglo interno.
 */
template <typename Type, bool MaxOMin>
int Heap<Type, MaxOMin>::CapMont() const {
    return capacidad;
}

/**
 * @brief Imprime todos los elementos actuales del heap.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::ImprimirElem() const {
    if (EstaVacia()) {
        std::cout << "El heap está vacío." << std::endl;
        return;
    }

    std::cout << "Elementos en el heap: ";
    for (int i = 0; i < cantElem; ++i) {
        std::cout << elemento[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Duplica la capacidad del heap cuando se llena.
 * 
 * @return Nueva capacidad del heap.
 */
template <typename Type, bool MaxOMin>
int Heap<Type, MaxOMin>::Redimensionar() {
    int nuevaCapacidad = capacidad * 2;
    Type* nuevoElemento = new Type[nuevaCapacidad];

    for (int i = 0; i < cantElem; ++i) {
        nuevoElemento[i] = elemento[i];
    }

    delete[] elemento;
    elemento = nuevoElemento;
    capacidad = nuevaCapacidad;

    return capacidad;
}

/**
 * @brief Ajusta el heap moviendo un elemento hacia arriba para mantener la propiedad del heap.
 * 
 * @param indice Índice del elemento que se debe mover hacia arriba.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::EmpujarArriba(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;

        if constexpr (MaxOMin) { // Max-Heap
            if (elemento[indice] > elemento[padre]) {
                std::swap(elemento[indice], elemento[padre]);
                indice = padre;
            } else {
                break;
            }
        } else { // Min-Heap
            if (elemento[indice] < elemento[padre]) {
                std::swap(elemento[indice], elemento[padre]);
                indice = padre;
            } else {
                break;
            }
        }
    }
}

/**
 * @brief Ajusta el heap moviendo un elemento hacia abajo para mantener la propiedad del heap.
 * 
 * @param indice Índice del elemento que se debe mover hacia abajo.
 */
template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::EmpujarAbajo(int indice) {
    while (true) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int mejorHijo = indice;

        if constexpr (MaxOMin) { // Max-Heap
            if (hijoIzq < cantElem && elemento[hijoIzq] > elemento[mejorHijo]) {
                mejorHijo = hijoIzq;
            }
            if (hijoDer < cantElem && elemento[hijoDer] > elemento[mejorHijo]) {
                mejorHijo = hijoDer;
            }
        } else { // Min-Heap
            if (hijoIzq < cantElem && elemento[hijoIzq] < elemento[mejorHijo]) {
                mejorHijo = hijoIzq;
            }
            if (hijoDer < cantElem && elemento[hijoDer] < elemento[mejorHijo]) {
                mejorHijo = hijoDer;
            }
        }

        if (mejorHijo != indice) {
            std::swap(elemento[indice], elemento[mejorHijo]);
            indice = mejorHijo;
        } else {
            break;
        }
    }
}


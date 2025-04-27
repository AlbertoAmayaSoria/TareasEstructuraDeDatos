#include <iostream>

template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::Heap() : cantElem(0), capacidad(31), tope(-1) {
    elemento = new Type[capacidad]; // Creamos un arreglo dinámico
}

template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::Heap(const Heap<Type, MaxOMin>& c) {
    *this = c; //falta el operador =
}

template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>::~Heap() {
    Vaciar(); //Falta el metodo vaciar
}

template <typename Type, bool MaxOMin>
Heap<Type, MaxOMin>& Heap<Type, MaxOMin>::operator=(const Heap<Type, MaxOMin>& c) {
    if (this == &c) return *this; // 1. Evitar autoasignación

    Vaciar(); // 2. Liberar la memoria actual (suponiendo que Vaciar() hace delete[] y pone cantElem = 0)

    capacidad = c.capacidad; // 3. Copiar capacidad
    cantElem = c.cantElem;   // 4. Copiar cantidad de elementos
    
    elemento = new Type[capacidad]; // 5. Crear nuevo arreglo dinámico

    for (int i = 0; i < cantElem; ++i) { // 6. Copiar los elementos
        elemento[i] = c.elemento[i];
    }

    return *this; // 7. Devolver *this
}

template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Agregar(Type valor) {
    if (cantElem == capacidad) { // Si está lleno
        Redimensionar(); // Aumentar capacidad
    }

    elemento[cantElem] = valor; // Agregar el nuevo valor al final
    EmpujarArriba(cantElem);    // Reordenar hacia arriba
    cantElem++;                 // Aumentar el contador de elementos
}

template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Eliminar() {
    if (EstaVacia()) {
        std::cout << "El heap está vacío, no se puede eliminar." << std::endl;
        return;
    }

    // Paso 1: Mover el último elemento a la raíz
    elemento[0] = elemento[cantElem - 1];

    // Paso 2: Disminuir la cantidad de elementos
    cantElem--;

    // Paso 3: Llamar a EmpujarAbajo(0) para restaurar el orden del heap
    EmpujarAbajo(0);
}

template <typename Type, bool MaxOMin>
Type Heap<Type, MaxOMin>::ObtenerFrente() const {
    if (EstaVacia()) {
        std::cerr << "El heap está vacío, no se puede obtener el frente." << std::endl;
        throw std::out_of_range("El heap está vacío");
    }
    return elemento[0];
}

template <typename Type, bool MaxOMin>
bool Heap<Type, MaxOMin>::EstaVacia() const {
    return cantElem == 0;
}

template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::Vaciar() {
    delete[] elemento;   // Liberar la memoria que ocupaba el arreglo
    elemento = nullptr;   // Poner el puntero a nullptr para evitar acceso a memoria liberada
    cantElem = 0;         // No hay elementos en el heap
    capacidad = 0;        // Opcional, dependiendo de cómo prefieras manejar la capacidad
}

template <typename Type, bool MaxOMin>
int Heap<Type, MaxOMin>::CantElem() const {
    return cantElem;
}

template <typename Type, bool MaxOMin>
int Heap<Type, MaxOMin>::CapMont() const {
    return capacidad;
}

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


template <typename Type, bool MaxOMin>
void Heap<Type, MaxOMin>::EmpujarArriba(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;

        if constexpr (MaxOMin) { // Si es Max-Heap
            if (elemento[indice] > elemento[padre]) {
                std::swap(elemento[indice], elemento[padre]);
                indice = padre;
            } else {
                break;
            }
        } else { // Si es Min-Heap
            if (elemento[indice] < elemento[padre]) {
                std::swap(elemento[indice], elemento[padre]);
                indice = padre;
            } else {
                break;
            }
        }
    }
}

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


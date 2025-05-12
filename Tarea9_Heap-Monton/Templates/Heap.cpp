// Constructor
template <typename Type>
Heap<Type>::Heap(bool (*cmp)(const Type&, const Type&))
    : capacidad(31), ultimo(-1), comparador(cmp) {
    elementos = new Type[capacidad];
}

// Constructor copia
template <typename Type>
Heap<Type>::Heap(const Heap<Type>& c) {
    *this = c;
}

// Destructor
template <typename Type>
Heap<Type>::~Heap() {
    Vaciar();
}

// Operador asignación
template <typename Type>
Heap<Type>& Heap<Type>::operator=(const Heap<Type>& c) {
    if (this == &c) return *this;

    Vaciar();

    capacidad = c.capacidad;
    ultimo = c.ultimo;
    comparador = c.comparador;
    elementos = new Type[capacidad];

    for (int i = 0; i <= ultimo; ++i) {
        elementos[i] = c.elementos[i];
    }

    return *this;
}

// Agregar
template <typename Type>
void Heap<Type>::Agregar(Type valor) {
    if (ultimo + 1 >= capacidad) {
        Redimensionar();
    }
    elementos[++ultimo] = valor;
    EmpujarArriba(ultimo);
}

// Eliminar
template <typename Type>
void Heap<Type>::Eliminar() {
    if (EstaVacio()) {
        std::cout << "El heap está vacío." << std::endl;
        return;
    }
    elementos[0] = elementos[ultimo--];
    EmpujarAbajo(0);
}

// Obtener frente
template <typename Type>
Type Heap<Type>::ObtenerFrente() const {
    if (EstaVacio()) {
        std::cerr << "El heap está vacío." << std::endl;
        throw std::out_of_range("El heap está vacío");
    }
    return elementos[0];
}

// Verificar vacío
template <typename Type>
bool Heap<Type>::EstaVacio() const {
    return ultimo == -1;
}

// Vaciar
template <typename Type>
void Heap<Type>::Vaciar() {
    delete[] elementos;
    elementos = nullptr;
    capacidad = 0;
    ultimo = -1;
}

// Número de elementos
template <typename Type>
int Heap<Type>::NumElem() const {
    return ultimo + 1;
}

// Capacidad actual
template <typename Type>
int Heap<Type>::CapacidadHeap() const {
    return capacidad;
}

// Imprimir
template <typename Type>
void Heap<Type>::Imprimir() const {
    if (EstaVacio()) {
        std::cout << "El heap está vacío." << std::endl;
        return;
    }
    std::cout << "Elementos: ";
    for (int i = 0; i <= ultimo; ++i) {
        std::cout << elementos[i] << " ";
    }
    std::cout << std::endl;
}

// Redimensionar
template <typename Type>
void Heap<Type>::Redimensionar() {
    int nuevaCapacidad = capacidad * 2;
    Type* nuevoElemento = new Type[nuevaCapacidad];

    for (int i = 0; i <= ultimo; ++i) {
        nuevoElemento[i] = elementos[i];
    }

    delete[] elementos;
    elementos = nuevoElemento;
    capacidad = nuevaCapacidad;
}

// Empujar arriba
template <typename Type>
void Heap<Type>::EmpujarArriba(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (comparador(elementos[indice], elementos[padre])) {
            std::swap(elementos[indice], elementos[padre]);
            indice = padre;
        } else {
            break;
        }
    }
}

// Empujar abajo
template <typename Type>
void Heap<Type>::EmpujarAbajo(int indice) {
    while (true) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int mejor = indice;

        if (hijoIzq <= ultimo && comparador(elementos[hijoIzq], elementos[mejor])) {
            mejor = hijoIzq;
        }
        if (hijoDer <= ultimo && comparador(elementos[hijoDer], elementos[mejor])) {
            mejor = hijoDer;
        }

        if (mejor != indice) {
            std::swap(elementos[indice], elementos[mejor]);
            indice = mejor;
        } else {
            break;
        }
    }
}

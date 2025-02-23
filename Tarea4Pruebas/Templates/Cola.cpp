#include <iostream>

/**
 * @brief Constructor por defecto. Inicializa la cola como vacía.
 */
template <typename Tipo>
Cola<Tipo>::Cola() : numElem(0), ultimo(nullptr) {}

/**
 * @brief Constructor de copia. Copia los elementos de otra cola.
 * @param c Cola a copiar.
 */
template <typename Tipo>
Cola<Tipo>::Cola(const Cola<Tipo>& c) {
    *this = c;
}

/**
 * @brief Destructor. Libera la memoria ocupada por la cola.
 */
template <typename Tipo>
Cola<Tipo>::~Cola() {
    Vaciar();
}

/**
 * @brief Agrega un elemento a la cola.
 * @param valor Valor a agregar.
 */
template <typename Tipo>
void Cola<Tipo>::Encolar(Tipo valor) {
    Elemento* nuevo = new Elemento;
    nuevo->valor = valor;
    if (EstaVacia()) {
        nuevo->siguiente = nuevo; // La cola es circular, apunta a sí mismo
        ultimo = nuevo;
    } else {
        nuevo->siguiente = ultimo->siguiente; // Nuevo apunta al primer elemento
        ultimo->siguiente = nuevo; // El anterior último ahora apunta al nuevo
        ultimo = nuevo; // Nuevo se convierte en el último
    }
    ++numElem;
}

/**
 * @brief Elimina el primer elemento de la cola.
 * @throws Excepción si la cola está vacía.
 */
template <typename Tipo>
void Cola<Tipo>::Desencolar() {
    if (EstaVacia()) throw "Cola vacía...\n";
    
    Elemento* porBorrar = ultimo->siguiente; // Primer elemento
    
    if (numElem == 1) {
        ultimo = nullptr; // La cola queda vacía
    } else {
        ultimo->siguiente = porBorrar->siguiente; // Saltar el primer elemento
    }
    
    delete porBorrar;
    --numElem;
}

/**
 * @brief Devuelve el primer elemento de la cola sin eliminarlo.
 * @return Valor del primer elemento.
 * @throws Excepción si la cola está vacía.
 */
template <typename Tipo>
Tipo Cola<Tipo>::ConocerPrim() const {
    if (EstaVacia()) throw "Cola vacía...\n";
    return ultimo->siguiente->valor; // `ultimo->siguiente` es el primero
}

/**
 * @brief Devuelve el último elemento de la cola sin eliminarlo.
 * @return Valor del último elemento.
 * @throws Excepción si la cola está vacía.
 */
template <typename Tipo>
Tipo Cola<Tipo>::ConocerUlt() const {
    if (EstaVacia()) throw "Cola vacía...\n";
    return ultimo->valor;
}

/**
 * @brief Verifica si la cola está vacía.
 * @return true si la cola está vacía, false en caso contrario.
 */
template <typename Tipo>
bool Cola<Tipo>::EstaVacia() const {
    return numElem == 0;
}

/**
 * @brief Elimina todos los elementos de la cola.
 */
template <typename Tipo>
void Cola<Tipo>::Vaciar() {
    while (!EstaVacia()) {
        Desencolar();
    }
}

/**
 * @brief Devuelve la cantidad de elementos en la cola.
 * @return Número de elementos en la cola.
 */
template <typename Tipo>
int Cola<Tipo>::ObtenerCantElem() const {
    return numElem;
}

/**
 * @brief Imprime los elementos de la cola en orden.
 */
template <typename Tipo>
void Cola<Tipo>::Imprimir() const {
    if (EstaVacia()) {
        std::cout << "La cola está vacía.\n";
        return;
    }

    Elemento* porImprimir = ultimo->siguiente; // Primer elemento
    //std::cout << "Primero -> ";
    for (int i = 0; i < numElem; ++i) {
        std::cout << porImprimir->valor << std::endl;
        porImprimir = porImprimir->siguiente;
    }
    //std::cout << "\b\b <- Último\n";
}

/**
 * @brief Operador de asignación para copiar una cola en otra.
 * @param c Cola a copiar.
 * @return Referencia a la cola actual con los elementos copiados.
 */
template <typename Tipo>
Cola<Tipo>& Cola<Tipo>::operator=(const Cola<Tipo>& c) {
    if (this == &c) return *this;
    this->Vaciar();

    Elemento* copia = c.ultimo->siguiente; // Primer elemento
    for (int i = 0; i < c.numElem; ++i) {
        Encolar(copia->valor);
        copia = copia->siguiente;
    }

    return *this;
    }

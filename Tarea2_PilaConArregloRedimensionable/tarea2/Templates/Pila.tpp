/**
 * @file Pila.tpp
 * @brief Implementación de la clase plantilla Pila (LIFO).
 */

#include <iostream>

/**
 * @brief Constructor por defecto de la pila.
 *
 * Inicializa una pila vacía con una capacidad predeterminada.
 */
template <typename Tipo>
Pila<Tipo>::Pila() : tope(-1), capacidad(5) {
    elemento = new Tipo[capacidad];
}

/**
 * @brief Constructor de copia.
 * @param p Pila a copiar.
 *
 * Crea una nueva pila como copia exacta de otra, duplicando sus elementos y capacidad.
 */
template <typename Tipo>
Pila<Tipo>::Pila(const Pila &p) : tope(p.tope), capacidad(p.capacidad) {
    elemento = new Tipo[capacidad];
    for (int i = 0; i <= tope; ++i) {
        elemento[i] = p.elemento[i];
    }
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param p Pila a asignar.
 * @return Referencia a la pila actual tras la asignación.
 *
 * Libera la memoria existente, asigna nueva memoria si es necesario y copia los elementos.
 */
template <typename Tipo>
Pila<Tipo>& Pila<Tipo>::operator=(const Pila<Tipo>& p) {
    if (this == &p) return *this;

    // Liberar memoria previa
    delete[] elemento;

    // Asignar nueva memoria si es necesario
    capacidad = p.capacidad;
    elemento = new Tipo[capacidad];

    // Copiar elementos y actualizar tope
    tope = p.tope;
    for (int i = 0; i <= tope; ++i) {
        elemento[i] = p.elemento[i];
    }

    return *this;
}

/**
 * @brief Destructor de la pila.
 *
 * Libera la memoria asignada dinámicamente.
 */
template <typename Tipo>
Pila<Tipo>::~Pila() {
    delete[] elemento;
}

/**
 * @brief Agrega un elemento a la pila.
 * @param valor Elemento a agregar.
 *
 * Si la pila está llena, se redimensiona automáticamente.
 */
template <typename Tipo>
void Pila<Tipo>::Apilar(Tipo valor) {
    if (EstaLlena()) {
        Redimensionar();
    }
    elemento[++tope] = valor;
}

/**
 * @brief Elimina el elemento en el tope de la pila.
 * @throw const char* Excepción si la pila está vacía.
 */
template <typename Tipo>
void Pila<Tipo>::Desapilar() {
    if (EstaVacia()) throw "Pila vac\242a...";
    --tope;
}

/**
 * @brief Obtiene el elemento en el tope de la pila.
 * @return Elemento en el tope.
 * @throw const char* Excepción si la pila está vacía.
 */
template <typename Tipo>
Tipo Pila<Tipo>::ObtenerTope() const {
    if (EstaVacia()) throw "Pila vac\242a...";
    return elemento[tope];
}

/**
 * @brief Verifica si la pila está vacía.
 * @return true si está vacía, false en caso contrario.
 */
template <typename Tipo>
bool Pila<Tipo>::EstaVacia() const {
    return tope == -1;
}

/**
 * @brief Vacía la pila eliminando todos los elementos.
 */
template <typename Tipo>
void Pila<Tipo>::Vaciar() {
    tope = -1;
}

/**
 * @brief Obtiene la cantidad de elementos en la pila.
 * @return Número de elementos en la pila.
 */
template <typename Tipo>
int Pila<Tipo>::ElementosPila() const {
    return tope + 1;
}

/**
 * @brief Obtiene la capacidad actual de la pila.
 * @return Capacidad máxima de la pila.
 */
template <typename Tipo>
int Pila<Tipo>::CapacidadPila() const {
    return capacidad;
}

/**
 * @brief Imprime los elementos de la pila.
 *
 * Muestra los elementos de la pila desde el fondo hasta el tope.
 */
template <typename Tipo>
void Pila<Tipo>::Imprimir() const {
    for (int i = 0; i <= tope; ++i) {
        std::cout << elemento[i];
        if (i < tope) std::cout << ", ";
    }
    std::cout << " <- TOPE\n";
}

/**
 * @brief Redimensiona la pila al duplicar su capacidad.
 *
 * Se llama automáticamente cuando la pila se llena.
 */
template <typename Tipo>
void Pila<Tipo>::Redimensionar() {
    capacidad *= 2;
    Tipo* nuevoElemento = new Tipo[capacidad];

    // Copiar elementos existentes
    for (int i = 0; i <= tope; ++i) {
        nuevoElemento[i] = elemento[i];
    }

    // Liberar memoria antigua y actualizar puntero
    delete[] elemento;
    elemento = nuevoElemento;
}

/**
 * @brief Verifica si la pila está llena.
 * @return true si está llena, false en caso contrario.
 */
template <typename Tipo>
bool Pila<Tipo>::EstaLlena() const {
    return tope + 1 == capacidad;
}


/**
 * @file ListaDobleCircular.tpp
 * @brief Implementación de los métodos de la clase ListaDobleCircular.
 */

// Constructor por defecto
template <typename T>
ListaDobleCircular<T>::ListaDobleCircular() : cabeza(nullptr), tamaño(0) {
    // Inicializamos la lista vacía, por lo que cabeza es nullptr y el tamaño es 0.
}

/**
 * @brief Constructor de copia.
 * @param otra Lista a copiar.
 */
template <typename T>
ListaDobleCircular<T>::ListaDobleCircular(const ListaDobleCircular& otra) : cabeza(nullptr), tamaño(0) {
    // Llamamos al operador de asignación para copiar el contenido de la otra lista.
    *this = otra;
}

/**
 * @brief Destructor.
 * Libera la memoria utilizada por la lista.
 */
template <typename T>
ListaDobleCircular<T>::~ListaDobleCircular() {
    // Llamamos a vaciar() para eliminar todos los nodos y evitar fugas de memoria.
    vaciar();
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param otra Lista a copiar.
 * @return Referencia a la lista actual.
 */
template <typename T>
ListaDobleCircular<T>& ListaDobleCircular<T>::operator=(const ListaDobleCircular& otra) {
    // Si la lista es la misma, no necesitamos hacer nada.
    if (this == &otra) return *this;

    // Primero, vaciamos la lista actual para evitar fugas de memoria.
    vaciar();

    // Si la lista "otra" está vacía, simplemente retornamos.
    if (!otra.cabeza) {
        return *this;
    }

    // Creamos el primer nodo de la lista a partir del primer nodo de "otra".
    cabeza = new Nodo(otra.cabeza->dato);

    Nodo* actual = cabeza;
    Nodo* otraActual = otra.cabeza->siguiente;

    // Copiamos el resto de los nodos de "otra" a la nueva lista.
    while (otraActual != otra.cabeza) {
        Nodo* nuevoNodo = new Nodo(otraActual->dato);
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
        actual = nuevoNodo;
        otraActual = otraActual->siguiente;
    }

    // Al final, cerramos el círculo enlazando el último nodo con la cabeza.
    actual->siguiente = cabeza;
    cabeza->anterior = actual;

    return *this;
}

/**
 * @brief Inserta un elemento en la cabeza de la lista.
 * @param valor Valor a insertar.
 */
template <typename T>
void ListaDobleCircular<T>::insertar(T valor)
{
    // Creamos un nuevo nodo con el valor proporcionado.
    Nodo* nuevo = new Nodo(valor);

    // Si la lista está vacía, el nuevo nodo será el único nodo y se apuntará a sí mismo.
    if (tamaño == 0) {
        cabeza = nuevo;
        nuevo->siguiente = nuevo;  // El siguiente apunta a sí mismo
        nuevo->anterior = nuevo;   // El anterior también apunta a sí mismo
    } else {
        // Si la lista no está vacía, insertamos el nuevo nodo al principio.
        nuevo->siguiente = cabeza;  // El nuevo nodo apunta a la cabeza actual
        nuevo->anterior = cabeza->anterior; // El nuevo nodo apunta al último nodo
        cabeza->anterior->siguiente = nuevo; // El último nodo apunta al nuevo nodo
        cabeza->anterior = nuevo;  // La cabeza ahora apunta al nuevo nodo como anterior
        cabeza = nuevo;           // Ahora el nuevo nodo es la cabeza de la lista
    }

    // Incrementamos el tamaño de la lista.
    tamaño++;
}

/**
 * @brief Elimina el elemento en cabeza de la lista.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
void ListaDobleCircular<T>::eliminar() {
    if (tamaño == 0) {
        throw std::out_of_range("No se puede eliminar de una lista vacía.");
    }

    // Si hay solo un nodo, simplemente eliminamos el nodo único.
    if (tamaño == 1) {
        delete cabeza;
        cabeza = nullptr;
    } else {
        // Si hay más de un nodo, removemos la cabeza.
        Nodo* temp = cabeza;
        cabeza->anterior->siguiente = cabeza->siguiente;
        cabeza->siguiente->anterior = cabeza->anterior;
        cabeza = cabeza->siguiente;
        delete temp;
    }

    // Decrementamos el tamaño de la lista.
    tamaño--;
}

/**
 * @brief Buscar un valor en la lista.
 * @param valor Valor a buscar.
 * @return true si el valor está en la lista, false en caso contrario.
 */
template <typename T>
bool ListaDobleCircular<T>::buscar(T valor) const {
    if (tamaño == 0) return false;

    Nodo* actual = cabeza;
    do {
        // Comprobamos si el nodo actual contiene el valor buscado.
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    // Si no encontramos el valor, retornamos false.
    return false;
}

/**
 * @brief Avanza en uno la posición de la cabeza.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
void ListaDobleCircular<T>::avanzarCabeza() {
    if (tamaño == 0) {
        throw std::out_of_range("La lista está vacía.");
    }

    cabeza = cabeza->siguiente;
}

/**
 * @brief Retrocede en uno la posición de la cabeza.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
void ListaDobleCircular<T>::retrocederCabeza() {
    if (tamaño == 0) {
        throw std::out_of_range("La lista está vacía.");
    }

    cabeza = cabeza->anterior;
}

/**
 * @brief Conocer el número de elementos en la lista.
 * @return Número de elementos.
 */
template <typename T>
size_t ListaDobleCircular<T>::obtenerTamaño() {
    return tamaño;
}

/**
 * @brief Verifica si la lista está vacía.
 * @return true si está vacía, false en caso contrario.
 */
template <typename T>
bool ListaDobleCircular<T>::estaVacia() {
    return tamaño == 0;
}

/**
 * @brief Vacía la lista.
 */
template <typename T>
void ListaDobleCircular<T>::vaciar() {
    // Mientras haya elementos, eliminamos el primero.
    while (tamaño > 0) {
        eliminar();
    }
}

/**
 * @brief Imprime la lista hacia adelante.
 */
template <typename T>
void ListaDobleCircular<T>::imprimirAdelante() {
    if (tamaño == 0) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* actual = cabeza;
    do {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << std::endl;
}

/**
 * @brief Imprime la lista hacia atrás.
 */
template <typename T>
void ListaDobleCircular<T>::imprimirReversa() {
    if (tamaño == 0) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* actual = cabeza->anterior;
    do {
        std::cout << actual->dato << " ";
        actual = actual->anterior;
    } while (actual != cabeza->anterior);
    std::cout << std::endl;
}


// Constructor
template <typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada() : primero(nullptr), ultimo(nullptr), tamaño(0) {}

// Constructor de copia
template <typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra) : primero(nullptr), ultimo(nullptr), tamaño(0) {
    *this = otra;
}

// Destructor
template <typename T>
ListaDoblementeEnlazada<T>::~ListaDoblementeEnlazada() {
    vaciar();
}

// Sobrecarga del operador =
template <typename T>
ListaDoblementeEnlazada<T>& ListaDoblementeEnlazada<T>::operator=(const ListaDoblementeEnlazada& otra) {
    if (this == &otra) return *this;
    vaciar();  // Usar la función vaciar en lugar de duplicar código

    if (!otra.primero) {
        return *this;
    }

    primero = new Nodo(otra.primero->dato);
    Nodo* actual = primero;
    Nodo* otraActual = otra.primero->siguiente;

    while (otraActual) {
        actual->siguiente = new Nodo(otraActual->dato);
        actual->siguiente->anterior = actual;
        actual = actual->siguiente;
        otraActual = otraActual->siguiente;
    }

    ultimo = actual;
    tamaño = otra.tamaño;
    return *this;
}

// Insertar al inicio
template <typename T>
void ListaDoblementeEnlazada<T>::insertarInicio(T valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!primero) {
        primero = ultimo = nuevo;
    } else {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
    }
    tamaño++;
}

// Insertar al final
template <typename T>
void ListaDoblementeEnlazada<T>::insertarFinal(T valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!primero) {
        primero = ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    tamaño++;
}

// Insertar en una posición específica
template <typename T>
void ListaDoblementeEnlazada<T>::insertarPosicion(T valor, size_t posicion) {
    if (posicion > tamaño) {
        throw std::out_of_range("Posición inválida");
    }

    if (posicion == 0) {
        insertarInicio(valor);
        return;
    }

    if (posicion == tamaño) {
        insertarFinal(valor);
        return;
    }

    Nodo* actual = primero;
    for (size_t i = 0; i < posicion - 2; ++i) {
        actual = actual->siguiente;
    }

    Nodo* nuevo = new Nodo(valor);
    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;
    actual->siguiente->anterior = nuevo;
    actual->siguiente = nuevo;
    tamaño++;
}

// Eliminar el primer nodo
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarInicio() {
    if (!primero) return;

    Nodo* temp = primero;
    primero = primero->siguiente;

    if (primero) {
        primero->anterior = nullptr;
    } else {
        ultimo = nullptr;
    }

    delete temp;
    tamaño--;
}

// Eliminar el último nodo
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarFinal() {
    if (!primero || !ultimo) {
        return;  // Lista vacía
    }

    if (primero == ultimo) {  // Solo un elemento
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
        tamaño--;
        return;
    }

    // Para múltiples elementos
    Nodo* temp = ultimo;
    ultimo = ultimo->anterior;  // Mover el puntero último al penúltimo nodo
    ultimo->siguiente = nullptr;  // El nuevo último nodo no debe tener siguiente
    temp->anterior = nullptr;  // Desconectar el nodo a eliminar
    delete temp;  // Liberar la memoria
    tamaño--;
}

// Eliminar por posición
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPosicion(size_t pos) {
    if (pos >= tamaño) {
        throw std::out_of_range("Posición inválida");
    }

    if (pos == 0) {
        eliminarInicio();
        return;
    }

    if (pos == tamaño - 1) {
        eliminarFinal();
        return;
    }

    Nodo* actual = primero;
    for (size_t i = 0; i < pos; ++i) {
        actual = actual->siguiente;
    }

    actual->anterior->siguiente = actual->siguiente;
    actual->siguiente->anterior = actual->anterior;
    delete actual;
    tamaño--;
}

// Eliminar por valor
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarValor(T valor) {
    if (!primero) return;

    if (primero->dato == valor) {
        eliminarInicio();
        return;
    }

    Nodo* actual = primero->siguiente;
    while (actual) {
        if (actual->dato == valor) {
            if (actual == ultimo) {
                eliminarFinal();
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                Nodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
                tamaño--;
            }
            return;
        }
        actual = actual->siguiente;
    }
}

// Eliminar todas las ocurrencias
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarTodasOcurrencias(T valor) {
    while (primero && primero->dato == valor) {
        eliminarInicio();
    }

    if (!primero) return;

    Nodo* actual = primero;
    while (actual) {
        if (actual->dato == valor) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            if (temp == ultimo) {
                eliminarFinal();
            } else {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
                delete temp;
                tamaño--;
            }
        } else {
            actual = actual->siguiente;
        }
    }
}

// Eliminar por condición
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPorCondicion(bool (*condicion)(T)) {
    while (primero && condicion(primero->dato)) {
        eliminarInicio();
    }

    if (!primero) return;

    Nodo* actual = primero;
    while (actual) {
        if (condicion(actual->dato)) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            if (temp == ultimo) {
                eliminarFinal();
            } else {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
                delete temp;
                tamaño--;
            }
        } else {
            actual = actual->siguiente;
        }
    }
}

// Eliminar elementos repetidos
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarElementosRepetidos() {
    if (!primero || !primero->siguiente) return;

    Nodo* actual = primero;
    while (actual) {
        Nodo* comparador = actual->siguiente;
        while (comparador) {
            if (actual->dato == comparador->dato) {
                Nodo* temp = comparador;
                comparador = comparador->siguiente;
                if (temp == ultimo) {
                    eliminarFinal();
                } else {
                    temp->anterior->siguiente = temp->siguiente;
                    temp->siguiente->anterior = temp->anterior;
                    delete temp;
                    tamaño--;
                }
            } else {
                comparador = comparador->siguiente;
            }
        }
        actual = actual->siguiente;
    }
}

// Buscar un elemento
template <typename T>
bool ListaDoblementeEnlazada<T>::buscar(T valor) const {
    Nodo* temp = primero;
    while (temp) {
        if (temp->dato == valor) return true;
        temp = temp->siguiente;
    }
    return false;
}

// Está vacía
template <typename T>
bool ListaDoblementeEnlazada<T>::estaVacia() const {
    return tamaño == 0;
}

// Obtener el primer elemento
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerPrimero() const {
    if (!primero) {
        throw std::out_of_range("La lista está vacía.");
    }
    return primero->dato;
}

// Obtener el último elemento
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerUltimo() const {
    if (!ultimo) {
        throw std::out_of_range("La lista está vacía.");
    }
    return ultimo->dato;
}

// Obtener elemento en posición
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerEnPosicion(size_t posicion) const {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    Nodo* actual = primero;
    for (size_t i = 0; i < posicion; ++i) {
        actual = actual->siguiente;
    }

    return actual->dato;
}

// Obtener índice
template <typename T>
int ListaDoblementeEnlazada<T>::obtenerIndice(const T& valor) const {
    Nodo* actual = primero;
    int indice = 0;

    while (actual) {
        if (actual->dato == valor) {
            return indice;
        }
        actual = actual->siguiente;
        indice++;
    }

    return -1;
}

// Modificar en posición
template <typename T>
void ListaDoblementeEnlazada<T>::modificarEnPosicion(size_t posicion, T nuevoValor) {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    Nodo* temp = primero;
    for (size_t i = 0; i < posicion - 1; ++i) {
        temp = temp->siguiente;
    }

    temp->dato = nuevoValor;
}

// Obtener tamaño
template <typename T>
size_t ListaDoblementeEnlazada<T>::obtenerTamaño() const {
    return tamaño;
}

// Vaciar la lista
template <typename T>
void ListaDoblementeEnlazada<T>::vaciar() {
    while (primero) {
        Nodo* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
    ultimo = nullptr;
    tamaño = 0;
}

// Imprimir lista
template <typename T>
void ListaDoblementeEnlazada<T>::imprimir() const {
    Nodo* temp = primero;
    if (!temp) {
        std::cout << "La lista está vacía.\n";
        return;
    }

    while (temp) {
        std::cout << temp->dato;
        if (temp->siguiente) {
            std::cout << " <-> ";
        }
        temp = temp->siguiente;
    }
    std::cout << " <-> NULL\n";
}

// Imprimir lista en reversa
template <typename T>
void ListaDoblementeEnlazada<T>::imprimirReversa() const {
    Nodo* temp = ultimo;
    while (temp) {
        std::cout << temp->dato << " <-> ";
        temp = temp->anterior;
    }
    std::cout << "NULL\n";
}

// Operador[] no constante
template <typename T>
T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango");
    }

    Nodo* actual;
    if (posicion < tamaño / 2) {
        actual = primero;
        for (size_t i = 0; i < posicion; ++i) {
            actual = actual->siguiente;
        }
    } else {
        actual = ultimo;
        for (size_t i = tamaño - 1; i > posicion; --i) {
            actual = actual->anterior;
        }
    }

    return actual->dato;
}

// Operador[] constante
template <typename T>
const T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) const {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    Nodo* temp = primero;
    for (size_t i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
    }

    return temp->dato;
}

// Ordenar ascendente
template <typename T>
void ListaDoblementeEnlazada<T>::ordenarAscendente() {
    if (tamaño <= 1) return;

    bool intercambio;
    do {
        intercambio = false;
        Nodo* actual = primero;
        while (actual->siguiente != nullptr) {
            if (actual->dato > actual->siguiente->dato) {
                // Intercambiar datos
                T temp = actual->dato;
                actual->dato = actual->siguiente->dato;
                actual->siguiente->dato = temp;
                intercambio = true;
            }
            actual = actual->siguiente;
        }
    } while (intercambio);
}

// Intercambio de listas
template <typename T>
void ListaDoblementeEnlazada<T>::intercambiar(ListaDoblementeEnlazada<T>& otra) {
    // Intercambiamos los punteros 'primero' y 'ultimo' de ambas listas
    Nodo* tempPrimero = primero;
    Nodo* tempUltimo = ultimo;
    primero = otra.primero;
    ultimo = otra.ultimo;
    otra.primero = tempPrimero;
    otra.ultimo = tempUltimo;

    // Intercambiamos los tamaños de ambas listas
    int tempTamaño = tamaño;
    tamaño = otra.tamaño;
    otra.tamaño = tempTamaño;

    // Después de este intercambio, las dos listas deben tener sus elementos intercambiados
}


// Transferir los elementos de una lista a otra dentro de un rango de elementos, considerando los elementos de una manera mas natural comenzando la lista desde 1
template <typename T>
void ListaDoblementeEnlazada<T>::transferirElementos(ListaDoblementeEnlazada<T>& otra, size_t inicio, size_t fin) {
    // Validar que los índices están dentro del rango válido de la lista
    if (inicio < 1 || fin < 1 || inicio > fin || fin > tamaño) {
        std::cout << "Índices inválidos." << std::endl;
        return;
    }

    // Ajustar los índices de inicio y fin para que sean basados en 0
    size_t indiceInicio = inicio - 1;  // Convertir el índice a base 0
    size_t indiceFin = fin - 1;        // Convertir el índice a base 0

    Nodo* nodoActual = primero;
    size_t indice = 0;

    // Mover el nodo actual al índice de inicio (basado en 0)
    while (nodoActual && indice < indiceInicio) {
        nodoActual = nodoActual->siguiente;
        indice++;
    }

    // Verificar si se encontró el nodo de inicio
    if (!nodoActual) {
        std::cout << "Índice de inicio fuera de rango." << std::endl;
        return;
    }

    // Transferir los elementos desde 'inicio' hasta 'fin'
    while (nodoActual && indice <= indiceFin) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Eliminar el nodo actual de la lista original
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;  // Si es el primer nodo
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;  // Si es el último nodo
        }

        // Insertar el nodo al final de la lista de destino
        otra.insertarFinal(nodoActual->dato);

        // Avanzar al siguiente nodo
        nodoActual = siguienteNodo;
        indice++;
    }

    // Actualizar los tamaños de las listas
    tamaño -= (indiceFin - indiceInicio + 1);
    otra.tamaño += (indiceFin - indiceInicio + 1);
}


// se transfieren los elementos desde un elemento en delante, considerando los elementos de una manera mas natural comenzando la lista desde 1
template <typename T>
void ListaDoblementeEnlazada<T>::transferirDesdeIndice(ListaDoblementeEnlazada<T>& otra, size_t indice) {
    // Validar que el índice esté dentro del rango de la lista original
    if (indice < 1 || indice > tamaño) {
        std::cout << "Índice fuera de rango." << std::endl;
        return;
    }

    // Convertimos el índice basado en 1 a un índice basado en 0 para la lista
    size_t indiceInterno = indice - 1;  // Ajustamos el índice para hacerlo basado en 0

    Nodo* nodoActual = primero;
    size_t contador = 0;

    // Mover al nodo en el índice especificado (ajustado para índice basado en 0)
    while (nodoActual && contador < indiceInterno) {
        nodoActual = nodoActual->siguiente;
        contador++;
    }

    // Si no encontramos el nodo en el índice (esto no debería ocurrir si el índice es válido)
    if (!nodoActual) {
        std::cout << "Índice fuera de rango." << std::endl;
        return;
    }

    // Transferir los elementos desde el índice especificado hasta el final de la lista
    while (nodoActual) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Eliminar el nodo actual de la lista original
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;  // Si es el primer nodo
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;  // Si es el último nodo
        }

        // Insertar el nodo al final de la lista de destino
        otra.insertarFinal(nodoActual->dato);

        // Avanzar al siguiente nodo
        nodoActual = siguienteNodo;
    }

    // Actualizar el tamaño de la lista original y la lista de destino
    tamaño -= (contador + 1);  // Elementos transferidos
    otra.tamaño += (contador + 1);  // Elementos agregados
}


// transferimos todos los elementos de una lista a otra
template <typename T>
void ListaDoblementeEnlazada<T>::transferirTodos(ListaDoblementeEnlazada<T>& otra) {
    // Comenzamos con el primer nodo de la lista original
    Nodo* nodoActual = primero;

    // Mientras haya nodos en la lista original
    while (nodoActual) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Eliminar el nodo actual de la lista original
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;  // Si es el primer nodo
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;  // Si es el último nodo
        }

        // Insertar el nodo al final de la lista de destino
        otra.insertarFinal(nodoActual->dato);

        // Avanzar al siguiente nodo
        nodoActual = siguienteNodo;
    }

    // Actualizamos el tamaño de la lista original y la lista de destino
    tamaño = 0;  // La lista original ahora está vacía
    otra.tamaño += tamaño;  // La lista de destino tiene todos los elementos
}


/**
 * @file ListaDoblementeEnlazada.tpp
 * @brief Implementación de los métodos de la clase ListaDoblementeEnlazada.
 */

// Constructor por defecto
template <typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada() : primero(nullptr), ultimo(nullptr), tamaño(0) {
    // Inicializamos los punteros a nullptr y el tamaño a 0 porque la lista está vacía.
}

/**
 * @brief Constructor de copia.
 * @param otra Lista a copiar.
 */
template <typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra) : primero(nullptr), ultimo(nullptr), tamaño(0) {
    // Usamos el operador de asignación para copiar los elementos de la lista "otra".
    *this = otra;
}

/**
 * @brief Destructor.
 * Libera la memoria utilizada por la lista.
 */
template <typename T>
ListaDoblementeEnlazada<T>::~ListaDoblementeEnlazada() {
    // Llamamos a la función vaciar() para liberar todos los nodos de la lista.
    vaciar();
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param otra Lista a copiar.
 * @return Referencia a la lista actual.
 */
template <typename T>
ListaDoblementeEnlazada<T>& ListaDoblementeEnlazada<T>::operator=(const ListaDoblementeEnlazada& otra) {
    // Si la lista a copiar es la misma, no hacemos nada.
    if (this == &otra) return *this;

    // Vaciamos la lista actual para evitar fugas de memoria.
    vaciar();

    // Si la lista "otra" está vacía, terminamos aquí.
    if (!otra.primero) {
        return *this;
    }

    // Copiamos el primer nodo de "otra" a la lista actual.
    primero = new Nodo(otra.primero->dato);
    Nodo* actual = primero;
    Nodo* otraActual = otra.primero->siguiente;

    // Recorremos la lista "otra" y copiamos cada nodo.
    while (otraActual) {
        actual->siguiente = new Nodo(otraActual->dato);
        actual->siguiente->anterior = actual;
        actual = actual->siguiente;
        otraActual = otraActual->siguiente;
    }

    // Actualizamos el puntero al último nodo y el tamaño de la lista.
    ultimo = actual;
    tamaño = otra.tamaño;
    return *this;
}

/**
 * @brief Inserta un elemento al inicio de la lista.
 * @param valor Valor a insertar.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::insertarInicio(T valor) {
    // Creamos un nuevo nodo con el valor proporcionado.
    Nodo* nuevo = new Nodo(valor);

    // Si la lista está vacía, el nuevo nodo será el primero y el último.
    if (!primero) {
        primero = ultimo = nuevo;
    } else {
        // Si no está vacía, el nuevo nodo se convierte en el primero.
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
    }
    // Incrementamos el tamaño de la lista.
    tamaño++;
}

/**
 * @brief Inserta un elemento al final de la lista.
 * @param valor Valor a insertar.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::insertarFinal(T valor) {
    // Creamos un nuevo nodo con el valor proporcionado.
    Nodo* nuevo = new Nodo(valor);

    // Si la lista está vacía, el nuevo nodo será el primero y el último.
    if (!primero) {
        primero = ultimo = nuevo;
    } else {
        // Si no está vacía, el nuevo nodo se convierte en el último.
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    // Incrementamos el tamaño de la lista.
    tamaño++;
}

/**
 * @brief Inserta un elemento en una posición específica.
 * @param valor Valor a insertar.
 * @param posicion Posición en la que se insertará el valor.
 * @throw std::out_of_range Si la posición es inválida.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::insertarPosicion(T valor, size_t posicion) {
    // Verificamos si la posición es válida.
    if (posicion > tamaño) {
        throw std::out_of_range("Posición inválida");
    }

    // Si la posición es 0, insertamos al inicio.
    if (posicion == 0) {
        insertarInicio(valor);
        return;
    }

    // Si la posición es igual al tamaño, insertamos al final.
    if (posicion == tamaño) {
        insertarFinal(valor);
        return;
    }

    // Recorremos la lista hasta la posición anterior a la deseada.
    Nodo* actual = primero;
    for (size_t i = 0; i < posicion - 2; ++i) {
        actual = actual->siguiente;
    }

    // Creamos el nuevo nodo y lo enlazamos con los nodos adyacentes.
    Nodo* nuevo = new Nodo(valor);
    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;
    actual->siguiente->anterior = nuevo;
    actual->siguiente = nuevo;

    // Incrementamos el tamaño de la lista.
    tamaño++;
}

/**
 * @brief Elimina el primer elemento de la lista.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarInicio() {
    // Si la lista está vacía, no hacemos nada.
    if (!primero) return;

    // Guardamos el nodo a eliminar.
    Nodo* temp = primero;

    // Movemos el puntero "primero" al siguiente nodo.
    primero = primero->siguiente;

    // Si la lista no está vacía después de eliminar, actualizamos el puntero "anterior" del nuevo primer nodo.
    if (primero) {
        primero->anterior = nullptr;
    } else {
        // Si la lista quedó vacía, actualizamos el puntero "ultimo".
        ultimo = nullptr;
    }

    // Liberamos la memoria del nodo eliminado.
    delete temp;

    // Decrementamos el tamaño de la lista.
    tamaño--;
}

/**
 * @brief Elimina el último elemento de la lista.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarFinal() {
    // Si la lista está vacía, no hacemos nada.
    if (!primero || !ultimo) {
        return;
    }

    // Si solo hay un nodo en la lista, lo eliminamos.
    if (primero == ultimo) {
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
        tamaño--;
        return;
    }

    // Guardamos el nodo a eliminar.
    Nodo* temp = ultimo;

    // Movemos el puntero "ultimo" al nodo anterior.
    ultimo = ultimo->anterior;

    // Desconectamos el nodo eliminado de la lista.
    ultimo->siguiente = nullptr;
    temp->anterior = nullptr;

    // Liberamos la memoria del nodo eliminado.
    delete temp;

    // Decrementamos el tamaño de la lista.
    tamaño--;
}

/**
 * @brief Elimina un elemento en una posición específica.
 * @param pos Posición del elemento a eliminar.
 * @throw std::out_of_range Si la posición es inválida.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPosicion(size_t pos) {
    // Verificamos si la posición es válida.
    if (pos >= tamaño) {
        throw std::out_of_range("Posición inválida");
    }

    // Si la posición es 0, eliminamos el primer nodo.
    if (pos == 0) {
        eliminarInicio();
        return;
    }

    // Si la posición es la última, eliminamos el último nodo.
    if (pos == tamaño - 1) {
        eliminarFinal();
        return;
    }

    // Recorremos la lista hasta el nodo en la posición deseada.
    Nodo* actual = primero;
    for (size_t i = 0; i < pos; ++i) {
        actual = actual->siguiente;
    }

    // Desconectamos el nodo de la lista.
    actual->anterior->siguiente = actual->siguiente;
    actual->siguiente->anterior = actual->anterior;

    // Liberamos la memoria del nodo eliminado.
    delete actual;

    // Decrementamos el tamaño de la lista.
    tamaño--;
}

/**
 * @brief Elimina la primera ocurrencia de un valor en la lista.
 * @param valor Valor a eliminar.
 * @return true si el valor fue eliminado, false si no se encontró.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarValor(T valor) {
    // Si la lista está vacía, no hacemos nada.
    if (!primero) return;

    // Si el valor está en el primer nodo, lo eliminamos.
    if (primero->dato == valor) {
        eliminarInicio();
        return;
    }

    // Recorremos la lista buscando el valor.
    Nodo* actual = primero->siguiente;
    while (actual) {
        if (actual->dato == valor) {
            // Si el valor está en el último nodo, lo eliminamos.
            if (actual == ultimo) {
                eliminarFinal();
            } else {
                // Desconectamos el nodo de la lista.
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;

                // Guardamos el nodo a eliminar.
                Nodo* temp = actual;
                actual = actual->siguiente;

                // Liberamos la memoria del nodo eliminado.
                delete temp;

                // Decrementamos el tamaño de la lista.
                tamaño--;
            }
            return;
        }
        actual = actual->siguiente;
    }
}

/**
 * @brief Elimina todas las ocurrencias de un valor en la lista.
 * @param valor Valor a eliminar.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarTodasOcurrencias(T valor) {
    // Eliminamos todas las ocurrencias del valor al inicio de la lista.
    while (primero && primero->dato == valor) {
        eliminarInicio();
    }

    // Si la lista está vacía, terminamos.
    if (!primero) return;

    // Recorremos la lista buscando y eliminando el valor.
    Nodo* actual = primero;
    while (actual) {
        if (actual->dato == valor) {
            // Guardamos el nodo a eliminar.
            Nodo* temp = actual;
            actual = actual->siguiente;

            // Si el nodo es el último, lo eliminamos.
            if (temp == ultimo) {
                eliminarFinal();
            } else {
                // Desconectamos el nodo de la lista.
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;

                // Liberamos la memoria del nodo eliminado.
                delete temp;

                // Decrementamos el tamaño de la lista.
                tamaño--;
            }
        } else {
            actual = actual->siguiente;
        }
    }
}

/**
 * @brief Elimina elementos que cumplen una condición.
 * @param condicion Función que define la condición de eliminación.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPorCondicion(bool (*condicion)(T)) {
    // Eliminamos todos los nodos al inicio que cumplan la condición.
    while (primero && condicion(primero->dato)) {
        eliminarInicio();
    }

    // Si la lista está vacía, terminamos.
    if (!primero) return;

    // Recorremos la lista buscando y eliminando nodos que cumplan la condición.
    Nodo* actual = primero;
    while (actual) {
        if (condicion(actual->dato)) {
            // Guardamos el nodo a eliminar.
            Nodo* temp = actual;
            actual = actual->siguiente;

            // Si el nodo es el último, lo eliminamos.
            if (temp == ultimo) {
                eliminarFinal();
            } else {
                // Desconectamos el nodo de la lista.
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;

                // Liberamos la memoria del nodo eliminado.
                delete temp;

                // Decrementamos el tamaño de la lista.
                tamaño--;
            }
        } else {
            actual = actual->siguiente;
        }
    }
}

/**
 * @brief Elimina elementos duplicados de la lista.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarElementosRepetidos() {
    // Si la lista está vacía o tiene un solo nodo, no hay duplicados.
    if (!primero || !primero->siguiente) return;

    // Recorremos la lista comparando cada nodo con los siguientes.
    Nodo* actual = primero;
    while (actual) {
        Nodo* comparador = actual->siguiente;
        while (comparador) {
            if (actual->dato == comparador->dato) {
                // Guardamos el nodo a eliminar.
                Nodo* temp = comparador;
                comparador = comparador->siguiente;

                // Si el nodo es el último, lo eliminamos.
                if (temp == ultimo) {
                    eliminarFinal();
                } else {
                    // Desconectamos el nodo de la lista.
                    temp->anterior->siguiente = temp->siguiente;
                    temp->siguiente->anterior = temp->anterior;

                    // Liberamos la memoria del nodo eliminado.
                    delete temp;

                    // Decrementamos el tamaño de la lista.
                    tamaño--;
                }
            } else {
                comparador = comparador->siguiente;
            }
        }
        actual = actual->siguiente;
    }
}

/**
 * @brief Busca un valor en la lista.
 * @param valor Valor a buscar.
 * @return true si el valor está en la lista, false en caso contrario.
 */
template <typename T>
bool ListaDoblementeEnlazada<T>::buscar(T valor) const {
    // Recorremos la lista buscando el valor.
    Nodo* temp = primero;
    while (temp) {
        if (temp->dato == valor) return true;
        temp = temp->siguiente;
    }
    return false;
}

/**
 * @brief Verifica si la lista está vacía.
 * @return true si la lista está vacía, false en caso contrario.
 */
template <typename T>
bool ListaDoblementeEnlazada<T>::estaVacia() const {
    // La lista está vacía si el tamaño es 0.
    return tamaño == 0;
}

/**
 * @brief Obtiene el primer elemento de la lista.
 * @return El primer elemento de la lista.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerPrimero() const {
    // Si la lista está vacía, lanzamos una excepción.
    if (!primero) {
        throw std::out_of_range("La lista está vacía.");
    }
    return primero->dato;
}

/**
 * @brief Obtiene el último elemento de la lista.
 * @return El último elemento de la lista.
 * @throw std::out_of_range Si la lista está vacía.
 */
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerUltimo() const {
    // Si la lista está vacía, lanzamos una excepción.
    if (!ultimo) {
        throw std::out_of_range("La lista está vacía.");
    }
    return ultimo->dato;
}

/**
 * @brief Obtiene un elemento en una posición específica.
 * @param posicion Posición del elemento a obtener.
 * @return El elemento en la posición especificada.
 * @throw std::out_of_range Si la posición es inválida.
 */
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerEnPosicion(size_t posicion) const {
    // Verificamos si la posición es válida.
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    // Recorremos la lista hasta la posición deseada.
    Nodo* actual = primero;
    for (size_t i = 0; i < posicion; ++i) {
        actual = actual->siguiente;
    }

    // Retornamos el valor del nodo en la posición especificada.
    return actual->dato;
}

/**
 * @brief Obtiene el índice de un valor en la lista.
 * @param valor Valor a buscar.
 * @return El índice del valor, o -1 si no se encuentra.
 */
template <typename T>
int ListaDoblementeEnlazada<T>::obtenerIndice(const T& valor) const {
    // Recorremos la lista buscando el valor.
    Nodo* actual = primero;
    int indice = 0;

    while (actual) {
        if (actual->dato == valor) {
            return indice;
        }
        actual = actual->siguiente;
        indice++;
    }

    // Si no se encuentra el valor, retornamos -1.
    return -1;
}

/**
 * @brief Modifica un valor en una posición específica.
 * @param posicion Posición del valor a modificar.
 * @param nuevoValor Nuevo valor a asignar.
 * @throw std::out_of_range Si la posición es inválida.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::modificarEnPosicion(size_t posicion, T nuevoValor) {
    // Verificamos si la posición es válida.
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    // Recorremos la lista hasta la posición deseada.
    Nodo* temp = primero;
    for (size_t i = 0; i < posicion - 1; ++i) {
        temp = temp->siguiente;
    }

    // Modificamos el valor del nodo en la posición especificada.
    temp->dato = nuevoValor;
}

/**
 * @brief Obtiene el tamaño de la lista.
 * @return El tamaño de la lista.
 */
template <typename T>
size_t ListaDoblementeEnlazada<T>::obtenerTamaño() const {
    // Retornamos el tamaño de la lista.
    return tamaño;
}

/**
 * @brief Vacía la lista.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::vaciar() {
    // Eliminamos todos los nodos de la lista.
    while (primero) {
        Nodo* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
    // Reiniciamos los punteros y el tamaño.
    ultimo = nullptr;
    tamaño = 0;
}

/**
 * @brief Imprime la lista en orden normal.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::imprimir() const {
    // Recorremos la lista e imprimimos cada valor.
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

/**
 * @brief Imprime la lista en orden inverso.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::imprimirReversa() const {
    // Recorremos la lista desde el último nodo e imprimimos cada valor.
    Nodo* temp = ultimo;
    while (temp) {
        std::cout << temp->dato << " <-> ";
        temp = temp->anterior;
    }
    std::cout << "NULL\n";
}

/**
 * @brief Sobrecarga del operador [] para acceder a elementos por índice.
 * @param posicion Índice del elemento a acceder.
 * @return Referencia al elemento en la posición especificada.
 * @throw std::out_of_range Si el índice es inválido.
 */
template <typename T>
T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) {
    // Verificamos si el índice es válido.
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango");
    }

    // Recorremos la lista desde el inicio o el final, dependiendo de la posición.
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

    // Retornamos el valor del nodo en la posición especificada.
    return actual->dato;
}

/**
 * @brief Sobrecarga del operador [] para acceso constante.
 * @param posicion Índice del elemento a acceder.
 * @return Referencia constante al elemento en la posición especificada.
 * @throw std::out_of_range Si el índice es inválido.
 */
template <typename T>
const T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) const {
    // Verificamos si el índice es válido.
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    // Recorremos la lista hasta la posición deseada.
    Nodo* temp = primero;
    for (size_t i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
    }

    // Retornamos el valor del nodo en la posición especificada.
    return temp->dato;
}

/**
 * @brief Ordena la lista en orden ascendente.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::ordenarAscendente() {
    // Si la lista tiene 0 o 1 elementos, ya está ordenada.
    if (tamaño <= 1) return;

    // Usamos el algoritmo de burbuja para ordenar la lista.
    bool intercambio;
    do {
        intercambio = false;
        Nodo* actual = primero;
        while (actual->siguiente != nullptr) {
            if (actual->dato > actual->siguiente->dato) {
                // Intercambiamos los valores de los nodos.
                T temp = actual->dato;
                actual->dato = actual->siguiente->dato;
                actual->siguiente->dato = temp;
                intercambio = true;
            }
            actual = actual->siguiente;
        }
    } while (intercambio);
}

/**
 * @brief Intercambia los elementos de la lista con otra.
 * @param otra Lista con la que se intercambiarán los elementos.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::intercambiar(ListaDoblementeEnlazada<T>& otra) {
    // Intercambiamos los punteros "primero" y "ultimo" de ambas listas.
    Nodo* tempPrimero = primero;
    Nodo* tempUltimo = ultimo;
    primero = otra.primero;
    ultimo = otra.ultimo;
    otra.primero = tempPrimero;
    otra.ultimo = tempUltimo;

    // Intercambiamos los tamaños de ambas listas.
    int tempTamaño = tamaño;
    tamaño = otra.tamaño;
    otra.tamaño = tempTamaño;
}

/**
 * @brief Transfiere los elementos de una lista a otra dentro de un rango de elementos.
 * @param otra Lista a la que se transferirán los elementos.
 * @param inicio Índice de inicio del rango de elementos a transferir.
 * @param fin Índice de fin del rango de elementos a transferir.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::transferirElementos(ListaDoblementeEnlazada<T>& otra, size_t inicio, size_t fin) {
    // Verificamos si los índices son válidos.
    if (inicio < 1 || fin < 1 || inicio > fin || fin > tamaño) {
        std::cout << "Índices inválidos." << std::endl;
        return;
    }

    // Convertimos los índices a base 0.
    size_t indiceInicio = inicio - 1;
    size_t indiceFin = fin - 1;

    // Recorremos la lista hasta el nodo de inicio.
    Nodo* nodoActual = primero;
    size_t indice = 0;
    while (nodoActual && indice < indiceInicio) {
        nodoActual = nodoActual->siguiente;
        indice++;
    }

    // Si no encontramos el nodo de inicio, terminamos.
    if (!nodoActual) {
        std::cout << "Índice de inicio fuera de rango." << std::endl;
        return;
    }

    // Transferimos los elementos desde el nodo de inicio hasta el nodo de fin.
    while (nodoActual && indice <= indiceFin) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Desconectamos el nodo de la lista original.
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;
        }

        // Insertamos el nodo al final de la lista de destino.
        otra.insertarFinal(nodoActual->dato);

        // Avanzamos al siguiente nodo.
        nodoActual = siguienteNodo;
        indice++;
    }

    // Actualizamos los tamaños de ambas listas.
    tamaño -= (indiceFin - indiceInicio + 1);
    otra.tamaño += (indiceFin - indiceInicio + 1);
}

/**
 * @brief Transfiere los elementos desde un índice específico a otra lista.
 * @param otra Lista a la que se transferirán los elementos.
 * @param indice Índice desde el cual se transferirán los elementos.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::transferirDesdeIndice(ListaDoblementeEnlazada<T>& otra, size_t indice) {
    // Verificamos si el índice es válido.
    if (indice < 1 || indice > tamaño) {
        std::cout << "Índice fuera de rango." << std::endl;
        return;
    }

    // Convertimos el índice a base 0.
    size_t indiceInterno = indice - 1;

    // Recorremos la lista hasta el nodo en el índice especificado.
    Nodo* nodoActual = primero;
    size_t contador = 0;
    while (nodoActual && contador < indiceInterno) {
        nodoActual = nodoActual->siguiente;
        contador++;
    }

    // Si no encontramos el nodo, terminamos.
    if (!nodoActual) {
        std::cout << "Índice fuera de rango." << std::endl;
        return;
    }

    // Transferimos los elementos desde el nodo especificado hasta el final.
    while (nodoActual) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Desconectamos el nodo de la lista original.
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;
        }

        // Insertamos el nodo al final de la lista de destino.
        otra.insertarFinal(nodoActual->dato);

        // Avanzamos al siguiente nodo.
        nodoActual = siguienteNodo;
    }

    // Actualizamos los tamaños de ambas listas.
    tamaño -= (contador + 1);
    otra.tamaño += (contador + 1);
}

/**
 * @brief Transfiere todos los elementos de una lista a otra.
 * @param otra Lista a la que se transferirán los elementos.
 */
template <typename T>
void ListaDoblementeEnlazada<T>::transferirTodos(ListaDoblementeEnlazada<T>& otra) {
    // Recorremos la lista y transferimos cada nodo a la lista de destino.
    Nodo* nodoActual = primero;
    while (nodoActual) {
        Nodo* siguienteNodo = nodoActual->siguiente;

        // Desconectamos el nodo de la lista original.
        if (nodoActual->anterior) {
            nodoActual->anterior->siguiente = nodoActual->siguiente;
        } else {
            primero = nodoActual->siguiente;
        }

        if (nodoActual->siguiente) {
            nodoActual->siguiente->anterior = nodoActual->anterior;
        } else {
            ultimo = nodoActual->anterior;
        }

        // Insertamos el nodo al final de la lista de destino.
        otra.insertarFinal(nodoActual->dato);

        // Avanzamos al siguiente nodo.
        nodoActual = siguienteNodo;
    }

    // Actualizamos los tamaños de ambas listas.
    tamaño = 0;
    otra.tamaño += tamaño;
}

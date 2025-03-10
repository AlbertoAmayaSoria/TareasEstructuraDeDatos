// Constructor
template <typename T>
ListaDoblementeEnlazadaOrdenada<T>::ListaDoblementeEnlazadaOrdenada() : primero(nullptr), ultimo(nullptr), tamaño(0) {}
// Inicializa la lista vacía. 'primero' y 'ultimo' son punteros a nullptr (sin nodos), y el tamaño es 0.


// Constructor de copia
template <typename T>
ListaDoblementeEnlazadaOrdenada<T>::ListaDoblementeEnlazadaOrdenada(const ListaDoblementeEnlazadaOrdenada& otra) : primero(nullptr), ultimo(nullptr), tamaño(0) {
    // Copia los nodos de otra lista
    *this = otra;  // Usamos la sobrecarga del operador = para copiar la lista
}


// Destructor
template <typename T>
ListaDoblementeEnlazadaOrdenada<T>::~ListaDoblementeEnlazadaOrdenada() {
    // Liberar memoria de todos los nodos
    while (primero) {
        Nodo* temp = primero; // Guardamos el nodo actual
        primero = primero->siguiente; // Movemos el puntero 'primero' al siguiente nodo
        delete temp; // Eliminamos el nodo guardado
    }
    tamaño = 0; // Resetear el tamaño de la lista a 0
}


// Sobrecarga del operador =
template <typename T>
ListaDoblementeEnlazadaOrdenada<T>& ListaDoblementeEnlazadaOrdenada<T>::operator=(const ListaDoblementeEnlazadaOrdenada& otra) {
    if (this == &otra) return *this; // Evitar autoasignación, si la lista es igual a sí misma, no hacer nada

    // Liberamos la memoria de la lista actual
    while (primero) {
        Nodo* temp = primero; // Guardamos el primer nodo
        primero = primero->siguiente; // Avanzamos el puntero 'primero' al siguiente nodo
        delete temp; // Eliminamos el nodo guardado
    }
    tamaño = 0; // Reiniciamos el tamaño

    // Si la lista "otra" está vacía, no hacemos nada
    if (!otra.primero) {
        primero = nullptr;
        ultimo = nullptr;
        return *this;
    }

    // Copiar los nodos de la lista "otra"
    primero = new Nodo(otra.primero->dato); // Creamos el primer nodo con el dato de 'otra'
    Nodo* actual = primero; // Nodo temporal que recorre la lista copiada
    Nodo* otraActual = otra.primero->siguiente; // Nodo temporal para recorrer la lista "otra"

    // Copiar todos los nodos de la lista "otra"
    while (otraActual) {
        actual->siguiente = new Nodo(otraActual->dato); // Creamos el siguiente nodo
        actual->siguiente->anterior = actual; // Enlazamos el nodo siguiente al nodo actual
        actual = actual->siguiente; // Avanzamos al siguiente nodo
        otraActual = otraActual->siguiente; // Avanzamos en la lista "otra"
    }

    // Asignar el último nodo y el tamaño
    ultimo = actual;
    tamaño = otra.tamaño;

    return *this; // Devolvemos la lista copiada
}

//*************************************************************************************************


// Insertar elemento
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::insertar(T valor) {
    Nodo* visitado = primero;

    // Encontrar la posición correcta para insertar
    while (visitado && valor > visitado->dato) {  
        visitado = visitado->siguiente;
    }

    // Crear el nuevo nodo (usando solo el constructor con un valor)
    Nodo* nuevo = new Nodo(valor);  

    // Caso 1: Lista vacía
    if (!primero) {
        primero = ultimo = nuevo;  // Si la lista está vacía, el nuevo nodo es el primero y el último
    }
    // Caso 2: Insertar al inicio
    else if (visitado == primero) {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;  // Colocamos el nuevo nodo al inicio
    }
    // Caso 3: Insertar al final
    else if (!visitado) {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;  // Colocamos el nuevo nodo al final
    }
    // Caso 4: Insertar en medio
    else {
        nuevo->siguiente = visitado;
        nuevo->anterior = visitado->anterior;
        visitado->anterior->siguiente = nuevo;
        visitado->anterior = nuevo;  // Colocamos el nuevo nodo en medio de otros nodos
    }

    ++tamaño;  // Incrementamos el tamaño de la lista
}

// Eliminar valor
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::eliminarValor(T valor) {
    if (!primero) {
        throw std::out_of_range("La lista está vacía.");  // Si la lista está vacía, no podemos eliminar nada
    }

    Nodo* visitado = primero;
    while (visitado) {
        if (visitado->dato == valor) {  // Si encontramos el valor en el nodo actual
            // Caso 1: Si el nodo es el primero
            if (visitado == primero) {
                primero = primero->siguiente;
                if (primero) {
                    primero->anterior = nullptr;  // El siguiente nodo ahora es el primero
                }
            }
            // Caso 2: Si el nodo es el último
            else if (visitado == ultimo) {
                ultimo = ultimo->anterior;
                if (ultimo) {
                    ultimo->siguiente = nullptr;  // El nodo anterior ahora es el último
                }
            }
            // Caso 3: Si el nodo está en el medio
            else {
                visitado->anterior->siguiente = visitado->siguiente;
                visitado->siguiente->anterior = visitado->anterior;
            }

            delete visitado;  // Eliminamos el nodo
            --tamaño;  // Reducimos el tamaño de la lista
            return;
        }
        visitado = visitado->siguiente;  // Continuamos con el siguiente nodo
    }

    throw std::out_of_range("Valor no encontrado en la lista.");  // Si no encontramos el valor
}

// Buscar valor
template <typename T>
bool ListaDoblementeEnlazadaOrdenada<T>::buscar(T valor) {
    Nodo* visitado = primero;
    while (visitado) {
        if (visitado->dato == valor) {
            return true;  // Si encontramos el valor, retornamos true
        }
        visitado = visitado->siguiente;  // Continuamos con el siguiente nodo
    }
    return false;  // Si no encontramos el valor, retornamos false
}

// Obtener tamaño de la lista
template <typename T>
size_t ListaDoblementeEnlazadaOrdenada<T>::obtenerTamaño() const {
    return tamaño;  // Retornamos el tamaño actual de la lista
}

// Verificar si la lista está vacía
template <typename T>
bool ListaDoblementeEnlazadaOrdenada<T>::estaVacia() const {
    return tamaño == 0;  // Si el tamaño es 0, la lista está vacía
}

// Vaciar la lista
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::vaciar() {
    while (primero) {
        Nodo* temp = primero;
        primero = primero->siguiente;
        delete temp;  // Eliminamos cada nodo
    }
    ultimo = nullptr;  // El último nodo también se establece a nullptr
    tamaño = 0;  // El tamaño de la lista es 0
}

// Imprimir lista en orden
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::imprimir() const {
    if (estaVacia()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* visitado = primero;
    while (visitado) {
        std::cout << visitado->dato << " ";  // Imprimimos el valor del nodo
        visitado = visitado->siguiente;  // Continuamos con el siguiente nodo
    }
    std::cout << std::endl;
}

// Imprimir lista en reversa
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::imprimirReversa() const {
    if (estaVacia()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* visitado = ultimo;
    while (visitado) {
        std::cout << visitado->dato << " ";  // Imprimimos el valor del nodo
        visitado = visitado->anterior;  // Retrocedemos al nodo anterior
    }
    std::cout << std::endl;
}


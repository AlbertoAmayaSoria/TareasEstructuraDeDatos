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
        primero = ultimo = nuevo;
    }
    // Caso 2: Insertar al inicio
    else if (visitado == primero) {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
    }
    // Caso 3: Insertar al final
    else if (!visitado) {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    // Caso 4: Insertar en medio
    else {
        nuevo->siguiente = visitado;
        nuevo->anterior = visitado->anterior;
        visitado->anterior->siguiente = nuevo;
        visitado->anterior = nuevo;
    }

    ++tamaño;
}




//************************************************************************************************


/*
// Eliminar el primer nodo
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::eliminarInicio() {
    if (!primero) return; // Si la lista está vacía, no hacemos nada

    Nodo* temp = primero; // Guardamos el primer nodo
    primero = primero->siguiente; // Movemos el puntero 'primero' al siguiente nodo
    if (primero) {
        primero->anterior = nullptr; // Si la lista no está vacía después de la eliminación, eliminamos la referencia al nodo anterior
    } else {
        ultimo = nullptr; // Si la lista queda vacía, 'ultimo' también es nullptr
    }

    delete temp; // Eliminamos el nodo guardado
    tamaño--; // Decrementamos el tamaño
}


// Eliminar el último nodo
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::eliminarFinal() {
    if (!primero) return; // Si la lista está vacía, no hacemos nada

    if (!primero->siguiente) { // Si hay un solo nodo en la lista
        delete primero; // Eliminamos ese nodo
        primero = nullptr;
        ultimo = nullptr;
    } else {
        Nodo* temp = ultimo; // Guardamos el último nodo
        ultimo = ultimo->anterior; // Movemos el puntero 'ultimo' al nodo anterior
        ultimo->siguiente = nullptr; // Eliminamos la referencia al nodo siguiente
        delete temp; // Eliminamos el nodo guardado
    }

    tamaño--; // Decrementamos el tamaño
}


// Eliminar por posición
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::eliminarPosicion(size_t pos) {
    if (pos >= tamaño) { // Verificamos si la posición es válida
        std::cerr << "Posición inválida\n";
        return;
    }

    if (pos == 0) { // Si la posición es 0, eliminamos el primer nodo
        eliminarInicio();
        return;
    }

    if (pos == tamaño - 1) { // Si la posición es el último nodo, eliminamos el último nodo
        eliminarFinal();
        return;
    }

    Nodo* temp = primero; // Usamos un puntero temporal para recorrer la lista
    for (size_t i = 0; i < pos; ++i) {
        temp = temp->siguiente;
    }

    Nodo* nodoAEliminar = temp; // Guardamos el nodo a eliminar
    temp->anterior->siguiente = temp->siguiente; // El nodo anterior apunta al siguiente
    if (temp->siguiente) {
        temp->siguiente->anterior = temp->anterior; // El nodo siguiente apunta al anterior
    }

    delete nodoAEliminar; // Eliminamos el nodo
    tamaño--; // Decrementamos el tamaño
}


// Eliminar por valor
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::eliminarValor(T valor) {
    if (!primero) return; // Si la lista está vacía, no hacemos nada

    if (primero->dato == valor) { // Si el primer nodo tiene el valor, lo eliminamos
        eliminarInicio();
        return;
    }

    Nodo* temp = primero; // Usamos un puntero temporal para recorrer la lista
    while (temp && temp->dato != valor) {
        temp = temp->siguiente; // Buscamos el nodo con el valor
    }

    if (temp) { // Si encontramos el nodo
        if (temp->siguiente) {
            temp->siguiente->anterior = temp->anterior; // El nodo siguiente apunta al anterior
        }
        if (temp->anterior) {
            temp->anterior->siguiente = temp->siguiente; // El nodo anterior apunta al siguiente
        }
        delete temp; // Eliminamos el nodo
        tamaño--; // Decrementamos el tamaño
    }
}


// Buscar un elemento
template <typename T>
bool ListaDoblementeEnlazadaOrdenada<T>::buscar(T valor) {
    Nodo* temp = primero; // Usamos un puntero para recorrer la lista
    while (temp) {
        if (temp->dato == valor) return true; // Si encontramos el valor, devolvemos true
        temp = temp->siguiente; // Avanzamos al siguiente nodo
    }
    return false; // Si no encontramos el valor, devolvemos false
}


// Obtener el primer elemento de la lista
template <typename T>
T ListaDoblementeEnlazadaOrdenada<T>::obtenerPrimero() const {
    if (!primero) {
        throw std::out_of_range("La lista está vacía."); // Lanzamos una excepción si la lista está vacía
    }
    return primero->dato; // Devolvemos el dato del primer nodo
}


// Obtener el último elemento de la lista
template <typename T>
T ListaDoblementeEnlazadaOrdenada<T>::obtenerUltimo() const {
    if (!ultimo) {
        throw std::out_of_range("La lista está vacía."); // Lanzamos una excepción si la lista está vacía
    }
    return ultimo->dato; // Devolvemos el dato del último nodo
}


// Obtener un elemento en una posición específica
template <typename T>
T ListaDoblementeEnlazadaOrdenada<T>::obtenerEnPosicion(size_t posicion) const {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango."); // Lanzamos una excepción si el índice es inválido
    }

    Nodo* actual = primero; // Usamos un puntero para recorrer la lista
        for (size_t i = 0; i < posicion - 1 ; ++i) {
        actual = actual->siguiente; // Avanzamos al siguiente nodo
    }

    return actual->dato; // Devolvemos el dato del nodo en la posición
}


// Obtener el índice de un elemento en la lista
template <typename T>
int ListaDoblementeEnlazadaOrdenada<T>::obtenerIndice(const T& valor) const {
    Nodo* actual = primero; // Usamos un puntero para recorrer la lista
    int indice = 0;

    while (actual) {
        if (actual->dato == valor) { // Si encontramos el valor
            return indice; // Devolvemos el índice
        }
        actual = actual->siguiente; // Avanzamos al siguiente nodo
        indice++; // Incrementamos el índice
    }

    return -1; // Si no encontramos el valor, devolvemos -1
}*/


// Obtener tamaño
template <typename T>
size_t ListaDoblementeEnlazadaOrdenada<T>::obtenerTamaño() const {
    return tamaño; // Devolvemos el tamaño de la lista
}


// Imprimir lista
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::imprimir() const {
    Nodo* temp = primero; // Usamos un puntero para recorrer la lista
    while (temp) {
        std::cout << temp->dato << " <-> "; // Imprimimos el dato y el enlace
        temp = temp->siguiente; // Avanzamos al siguiente nodo
    }
    std::cout << "NULL\n"; // Imprimimos NULL al final para indicar el fin de la lista
}


// Imprimir lista en reversa
template <typename T>
void ListaDoblementeEnlazadaOrdenada<T>::imprimirReversa() const {
    Nodo* temp = ultimo; // Usamos un puntero para recorrer la lista desde el final
    while (temp) {
        std::cout << temp->dato << " <-> "; // Imprimimos el dato y el enlace
        temp = temp->anterior; // Avanzamos al nodo anterior
    }
    std::cout << "NULL\n"; // Imprimimos NULL al final para indicar el fin de la lista
}


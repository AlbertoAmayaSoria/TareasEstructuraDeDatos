// Constructor
#include <chrono>
#include <cstddef>
#include <thread>

// Inicializa la lista vacía. 'primero' y 'ultimo' son punteros a nullptr (sin nodos), y el tamaño es 0.
template <typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada() : primero(nullptr), ultimo(nullptr), tamaño(0) {}

// Constructor de copia
template <typename T>
// Crea una nueva lista a partir de otra lista existente. Copia todos los nodos de la lista "otra".
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada(const ListaDoblementeEnlazada& otra) : primero(nullptr), ultimo(nullptr), tamaño(0) {
    *this = otra;  // Usamos la sobrecarga del operador = para copiar la lista
}

// Destructor
template <typename T>
// Libera la memoria de todos los nodos de la lista, eliminando cada nodo uno a uno.
ListaDoblementeEnlazada<T>::~ListaDoblementeEnlazada() {
    while (primero) {
        Nodo* temp = primero;  // Guardamos el nodo actual
        primero = primero->siguiente;  // Avanzamos el puntero 'primero' al siguiente nodo
        delete temp;  // Eliminamos el nodo guardado
    }
    tamaño = 0;  // Resetear el tamaño de la lista a 0
}

// Sobrecarga del operador =
template <typename T>
// Asigna el contenido de una lista a otra, copiando todos los nodos.
ListaDoblementeEnlazada<T>& ListaDoblementeEnlazada<T>::operator=(const ListaDoblementeEnlazada& otra) {
    if (this == &otra) return *this;  // Evitar la autoasignación, si la lista es igual a sí misma, no hacer nada

    // Liberamos la memoria de la lista actual
    while (primero) {
        Nodo* temp = primero;  // Guardamos el primer nodo
        primero = primero->siguiente;  // Avanzamos el puntero 'primero' al siguiente nodo
        delete temp;  // Eliminamos el nodo guardado
    }
    tamaño = 0;  // Reiniciamos el tamaño

    // Si la lista "otra" está vacía, no hacemos nada
    if (!otra.primero) {
        primero = nullptr;
        ultimo = nullptr;
        return *this;
    }

    // Copiar los nodos de la lista "otra"
    primero = new Nodo(otra.primero->dato);  // Creamos el primer nodo con el dato de 'otra'
    Nodo* actual = primero;  // Nodo temporal que recorre la lista copiada
    Nodo* otraActual = otra.primero->siguiente;  // Nodo temporal para recorrer la lista "otra"

    // Copiar todos los nodos de la lista "otra"
    while (otraActual) {
        actual->siguiente = new Nodo(otraActual->dato);  // Creamos el siguiente nodo
        actual->siguiente->anterior = actual;  // Enlazamos el nodo siguiente al nodo actual
        actual = actual->siguiente;  // Avanzamos al siguiente nodo
        otraActual = otraActual->siguiente;  // Avanzamos en la lista "otra"
    }

    // Asignar el último nodo y el tamaño
    ultimo = actual;
    tamaño = otra.tamaño;

    return *this;  // Devolvemos la lista copiada
}

//******************************************************************************************************************************************

// Insertar al inicio
template <typename T>
void ListaDoblementeEnlazada<T>::insertarInicio(T valor) {
    Nodo* nuevo = new Nodo(valor); // Creamos un nuevo nodo con el valor proporcionado
    nuevo->siguiente = primero; // El nuevo nodo apunta al primer nodo
    if (primero) {
        primero->anterior = nuevo; // Si la lista no está vacía, el primer nodo apunta al nuevo nodo
    }
    primero = nuevo; // Actualizamos el puntero 'primero' para que apunte al nuevo nodo

    if (!ultimo) {
        ultimo = nuevo; // Si la lista estaba vacía, el nuevo nodo es también el último nodo
    }

    tamaño++; // Incrementamos el tamaño de la lista
}

// Insertar al final
template <typename T>
void ListaDoblementeEnlazada<T>::insertarFinal(T valor) {
    Nodo* nuevo = new Nodo(valor); // Creamos un nuevo nodo con el valor proporcionado
    if (!primero) {
        primero = nuevo; // Si la lista está vacía, el nuevo nodo es tanto el primero como el último
        ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo; // El último nodo actual apunta al nuevo nodo
        nuevo->anterior = ultimo; // El nuevo nodo apunta hacia atrás al último nodo
        ultimo = nuevo; // Actualizamos el puntero 'ultimo' para que apunte al nuevo nodo
    }
    tamaño++; // Incrementamos el tamaño de la lista
}

// Insertar en una posición específica
template <typename T>
void ListaDoblementeEnlazada<T>::insertarPosicion(T valor, size_t posicion) {
    // Verificar si la posición es válida
    if (posicion > tamaño) {
        std::cout << "Posición inválida." << std::endl;
        return;
    }

    Nodo* nuevoNodo = new Nodo(valor);

    // Si la lista está vacía o la posición es 0, insertar al inicio
    if (posicion == 0) {
        insertarInicio(valor);
        return;
    }

    Nodo* actual = primero;  // Usar 'primero' en lugar de 'cabeza'
    for (size_t i = 0; i < posicion - 2; ++i) {
        actual = actual->siguiente;
    }

    // Insertar el nuevo nodo
    nuevoNodo->siguiente = actual->siguiente;
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = nuevoNodo;
    }
    actual->siguiente = nuevoNodo;
    nuevoNodo->anterior = actual;

    // Si se insertó al final, actualizar 'ultimo'
    if (nuevoNodo->siguiente == nullptr) {
        ultimo = nuevoNodo;
    }

    // Aumentar tamaño de la lista
    tamaño++;
}


//******************************************************************************************************************************************

// Eliminar el primer nodo
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarInicio() {
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
void ListaDoblementeEnlazada<T>::eliminarFinal() {
    if (!primero) {  // Si la lista está vacía, no hacemos nada
        return;
    }

    if (primero == ultimo) {  // Si hay un solo nodo en la lista
        delete primero;  // Eliminamos ese nodo
        primero = nullptr;  // La lista queda vacía
        ultimo = nullptr;
    } else {
        Nodo* temp = ultimo;  // Guardamos el último nodo
        ultimo = ultimo->anterior;  // Movemos el puntero 'ultimo' al nodo anterior
        ultimo->siguiente = nullptr;  // El nuevo último nodo no debe apuntar a nada
        delete temp;  // Eliminamos el nodo que estaba al final
    }

    tamaño--;  // Decrementamos el tamaño de la lista
}



// Eliminar por posición
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPosicion(size_t pos) {
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
void ListaDoblementeEnlazada<T>::eliminarValor(T valor) {
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


// Eliminar ocurrencias
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarTodasOcurrencias(T valor) {
    if (!primero) return; // Si la lista está vacía, no hacemos nada

    Nodo* actual = primero; // Puntero auxiliar

    while (actual) {
        Nodo* siguiente = actual->siguiente; // Guardamos el siguiente nodo antes de eliminarlo

        if (actual->dato == valor) {
            // Ajustamos punteros de los nodos adyacentes
            if (actual->anterior) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                primero = actual->siguiente; // Si es el primer nodo, actualizar el puntero primero
            }

            if (actual->siguiente) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                ultimo = actual->anterior; // Si es el último nodo, actualizar el puntero ultimo
            }

            delete actual; // Liberamos la memoria del nodo eliminado
            --tamaño;
        }

        actual = siguiente; // Avanzamos al siguiente nodo antes de eliminar el actual
    }

    // Si la lista quedó vacía, aseguramos que los punteros sean nullptr
    if (tamaño == 0) {
        primero = nullptr;
        ultimo = nullptr;
    }
}


// Eliminar por condición
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarPorCondicion(bool (*condicion)(T)) {
    if (!primero) return; // Si la lista está vacía, no hacemos nada

    Nodo* actual = primero;

    while (actual) {
        Nodo* siguiente = actual->siguiente; // Guardamos el siguiente nodo antes de eliminar el actual

        if (condicion(actual->dato)) { // Evaluamos la condición
            // Ajustamos punteros de los nodos adyacentes
            if (actual->anterior) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                primero = actual->siguiente; // Si es el primer nodo, actualizar el puntero 'primero'
            }

            if (actual->siguiente) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                ultimo = actual->anterior; // Si es el último nodo, actualizar el puntero 'ultimo'
            }

            delete actual; // Liberamos la memoria del nodo eliminado
            --tamaño;
        }

        actual = siguiente; // Avanzamos al siguiente nodo
    }

    // Si la lista quedó vacía, aseguramos que los punteros sean nullptr
    if (tamaño == 0) {
        primero = nullptr;
        ultimo = nullptr;
    }
}


// Eliminar elementos repetidos
template <typename T>
void ListaDoblementeEnlazada<T>::eliminarElementosRepetidos() {
    if (!primero || !primero->siguiente) return; // Si la lista está vacía o tiene un solo elemento, no hacemos nada.

    Nodo* actual = primero; // Puntero para recorrer la lista.

    while (actual) {
        Nodo* comparador = actual->siguiente; // Puntero para buscar duplicados.
        
        while (comparador) {
            Nodo* siguienteComparador = comparador->siguiente; // Guardamos el siguiente nodo antes de eliminar el actual.

            if (actual->dato == comparador->dato) { // Si encontramos un duplicado.
                // Ajustamos los punteros de los nodos adyacentes.
                if (comparador->anterior) {
                    comparador->anterior->siguiente = comparador->siguiente;
                }
                if (comparador->siguiente) {
                    comparador->siguiente->anterior = comparador->anterior;
                }
                if (comparador == ultimo) {
                    ultimo = comparador->anterior; // Si eliminamos el último nodo, actualizamos el puntero 'ultimo'.
                }

                delete comparador; // Eliminamos el nodo duplicado.
                --tamaño;
            }

            comparador = siguienteComparador; // Avanzamos al siguiente nodo.
        }

        actual = actual->siguiente; // Pasamos al siguiente nodo de la lista.
    }
}

//******************************************************************************************************************************************

// Buscar un elemento
template <typename T>
bool ListaDoblementeEnlazada<T>::buscar(T valor) const {
    Nodo* temp = primero; // Usamos un puntero para recorrer la lista
    while (temp) {
        if (temp->dato == valor) return true; // Si encontramos el valor, devolvemos true
        temp = temp->siguiente; // Avanzamos al siguiente nodo
    }
    return false; // Si no encontramos el valor, devolvemos false
}

//******************************************************************************************************************************************

//Método para saber si la lista está vacía
template <typename T>
bool ListaDoblementeEnlazada<T>::estaVacia() const{
    return tamaño == 0;
}


// Obtener el primer elemento de la lista
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerPrimero() const {
    if (!primero) {
        throw std::out_of_range("La lista está vacía."); // Lanzamos una excepción si la lista está vacía
    }
    return primero->dato; // Devolvemos el dato del primer nodo
}


// Obtener el último elemento de la lista
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerUltimo() const {
    if (!ultimo) {
        throw std::out_of_range("La lista está vacía."); // Lanzamos una excepción si la lista está vacía
    }
    return ultimo->dato; // Devolvemos el dato del último nodo
}


// Obtener un elemento en una posición específica
template <typename T>
T ListaDoblementeEnlazada<T>::obtenerEnPosicion(size_t posicion) const {
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
int ListaDoblementeEnlazada<T>::obtenerIndice(const T& valor) const {
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
}

//******************************************************************************************************************************************

// Modificar un elemento en una posición específica
template <typename T>
void ListaDoblementeEnlazada<T>::modificarEnPosicion(size_t posicion, T nuevoValor) {
    if (posicion >= tamaño) {  // Verificamos si la posición es válida
        std::cerr << "Índice fuera de rango.\n";
        return;
    }

    Nodo* temp = primero;  // Usamos un puntero para recorrer la lista
    for (size_t i = 0; i < posicion - 1; ++i) {
        temp = temp->siguiente;  // Avanzamos al siguiente nodo
    }

    temp->dato = nuevoValor;  // Modificamos el valor del nodo en la posición
}


//******************************************************************************************************************************************

// Obtener tamaño
template <typename T>
size_t ListaDoblementeEnlazada<T>::obtenerTamaño() const {
    return tamaño; // Devolvemos el tamaño de la lista
}


// vaciar la lista
template <typename T>
void ListaDoblementeEnlazada<T>::vaciar() {
    Nodo* actual = primero;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;  // Guardamos el siguiente nodo
        delete actual;  // Eliminamos el nodo actual
        actual = siguiente;  // Avanzamos al siguiente nodo
    }
    primero = nullptr;  // La lista está vacía, por lo tanto, el primero es nullptr
    ultimo = nullptr;   // Y el último también debe ser nullptr
    tamaño = 0;         // El tamaño de la lista es 0
}


//******************************************************************************************************************************************

// Imprimir lista
template <typename T>
void ListaDoblementeEnlazada<T>::imprimir() const {
    Nodo* temp = primero;  // Usamos un puntero para recorrer la lista
    if (!temp) {  // Si la lista está vacía, imprimimos un mensaje
        std::cout << "La lista está vacía.\n";
        return;
    }

    while (temp) {  // Recorremos la lista
        std::cout << temp->dato;  // Imprimimos el dato
        if (temp->siguiente) {  // Si hay un siguiente nodo, imprimimos el enlace
            std::cout << " <-> ";
        }
        temp = temp->siguiente;  // Avanzamos al siguiente nodo
    }
    std::cout << " <-> NULL\n";  // Imprimimos NULL al final para indicar el fin de la lista
}



// Imprimir lista en reversa
template <typename T>
void ListaDoblementeEnlazada<T>::imprimirReversa() const {
    Nodo* temp = ultimo; // Usamos un puntero para recorrer la lista desde el final
    while (temp) {
        std::cout << temp->dato << " <-> "; // Imprimimos el dato y el enlace
        temp = temp->anterior; // Avanzamos al nodo anterior
    }
    std::cout << "NULL\n"; // Imprimimos NULL al final para indicar el fin de la lista
}


//******************************************************************************************************************************************


// Operadores sobrecargados

// Versión no constante: Permite modificar el valor de un nodo en una posición específica
template <typename T>
T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango");
    }

    Nodo* actual;

    // Si el índice está en la primera mitad de la lista, recorremos desde el principio.
    // Si está en la segunda mitad, recorremos desde el final.
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

    return actual->dato;  // Devolvemos la referencia del dato para poder modificarlo
}

// Versión constante: Permite acceder a un nodo en una posición específica sin modificarlo
template <typename T>
const T& ListaDoblementeEnlazada<T>::operator[](size_t posicion) const {
    if (posicion >= tamaño) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    Nodo* temp = primero;
    for (size_t i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
    }

    return temp->dato;  // Devolvemos una referencia constante para no permitir modificación
}


//******************************************************************************************************************************************

// Método para ordenar la lista de menor a mayor con el método de inserción
template <typename T>
void ListaDoblementeEnlazada<T>::ordenarAscendente() {
    // Si la lista está vacía o tiene solo un elemento, no es necesario ordenarla
    if (tamaño <= 1) return;

    Nodo* actual = primero->siguiente;  // Comenzamos con el segundo nodo (el primero ya está ordenado)

    // Recorremos la lista desde el segundo nodo
    while (actual) {
        Nodo* siguienteNodo = actual->siguiente;  // Guardamos el siguiente nodo
        Nodo* temp = actual;  // Nodo actual que se va a insertar en la lista ordenada

        // Recorremos hacia atrás para encontrar la posición correcta del nodo actual
        Nodo* anterior = actual->anterior;
        while (anterior && anterior->dato > temp->dato) {
            anterior = anterior->anterior;
        }

        // Si el nodo actual no está en su posición correcta
        if (anterior != actual->anterior) {
            // Desconectamos el nodo actual de su posición
            if (temp->siguiente) {
                temp->siguiente->anterior = temp->anterior;
            }
            if (temp->anterior) {
                temp->anterior->siguiente = temp->siguiente;
            }

            // Insertamos el nodo en la nueva posición
            if (anterior) {
                temp->siguiente = anterior->siguiente;
                if (anterior->siguiente) {
                    anterior->siguiente->anterior = temp;
                }
                anterior->siguiente = temp;
                temp->anterior = anterior;
            } else {  // Si es el primer nodo
                temp->siguiente = primero;
                if (primero) {
                    primero->anterior = temp;
                }
                primero = temp;
                temp->anterior = nullptr;
            }
        }

        actual = siguienteNodo;  // Avanzamos al siguiente nodo
    }
}




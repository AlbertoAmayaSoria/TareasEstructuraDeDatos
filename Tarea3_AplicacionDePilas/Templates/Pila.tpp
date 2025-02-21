#include <iostream>

/**
 * @brief Constructor por defecto de la clase Pila.
 * 
 * Inicializa una pila vacía, estableciendo el número de elementos en 0
 * y el puntero `tope` en NULL.
 */
template <typename Tipo>
Pila<Tipo>::Pila() : numElem(0), tope(NULL) {}

//************************************************************************************************
/**
 * @brief Constructor de copia.
 * 
 * Crea una nueva pila copiando los elementos de otra pila dada.
 * Se inicializa `tope` en NULL y luego se usa el operador de asignación.
 * 
 * @param p Pila de la que se copiarán los elementos.
 */
template <typename Tipo>
Pila<Tipo>::Pila(const Pila<Tipo>& p) : numElem(0), tope(NULL) {
    *this = p;
}

//************************************************************************************************
/**
 * @brief Destructor de la pila.
 * 
 * Elimina todos los elementos de la pila llamando a `Vaciar()`.
 */
template <typename Tipo>
Pila<Tipo>::~Pila() {
    Vaciar();
}

//************************************************************************************************
/**
 * @brief Agrega un nuevo elemento a la pila.
 * 
 * Crea un nuevo nodo `Elemento`, almacena el valor y lo enlaza al tope de la pila.
 * 
 * @param valor Valor a agregar en la pila.
 */
template <typename Tipo>
void Pila<Tipo>::Apilar(Tipo valor) {
    Elemento *nuevo = new Elemento;
    nuevo->valor = valor;
    nuevo->siguiente = tope;
    tope = nuevo;
    ++numElem;
}

//************************************************************************************************
/**
 * @brief Elimina el elemento superior de la pila.
 * 
 * Si la pila está vacía, lanza una excepción.
 */
template <typename Tipo>
void Pila<Tipo>::Desapilar() {
    if(EstaVacia()) throw "Pila vac\241a...\n";
    Elemento *porBorrar = tope;
    tope = tope->siguiente;
    delete porBorrar;
    --numElem;
}

//************************************************************************************************
/**
 * @brief Obtiene el valor del elemento en el tope de la pila.
 * 
 * @return Valor del tope de la pila.
 * @throws Excepción si la pila está vacía.
 */
template <typename Tipo>
Tipo Pila<Tipo>::ObtenerTope() const {
    if(EstaVacia()) throw "Pila vac\241a...";
    return tope->valor;
}

//************************************************************************************************
/**
 * @brief Verifica si la pila está vacía.
 * 
 * @return true si la pila no tiene elementos, false en caso contrario.
 */
template <typename Tipo>
bool Pila<Tipo>::EstaVacia() const {
    return numElem == 0;
}

//************************************************************************************************
/**
 * @brief Vacía la pila eliminando todos sus elementos.
 */
template <typename Tipo>
void Pila<Tipo>::Vaciar() {
    while(!EstaVacia()) Desapilar();
}

//************************************************************************************************
/**
 * @brief Obtiene la cantidad de elementos en la pila.
 * 
 * @return Número de elementos en la pila.
 */
template <typename Tipo>
int Pila<Tipo>::ObtenerCantElem() const {
    return numElem;
}

//************************************************************************************************
/**
 * @brief Imprime el contenido de la pila en consola.
 */
template <typename Tipo>
void Pila<Tipo>::Imprimir() const {
    Elemento *porImprimir = tope;
    std::cout << "TOPE -> ";
    for(int i = 0; i < numElem; ++i) {
        std::cout << porImprimir->valor << ", ";
        porImprimir = porImprimir->siguiente;
    }
    std::cout << "\b\b \n"; // Borra la última coma y espacio extra
}

//************************************************************************************************
/**
 * @brief Sobrecarga del operador de asignación.
 * 
 * Permite asignar una pila a otra, copiando todos sus elementos.
 * 
 * @param p Pila a copiar.
 * @return Referencia a la pila actual (*this).
 */
template <typename Tipo>
Pila<Tipo>& Pila<Tipo>::operator=(const Pila<Tipo>& p) {
    if (this == &p) return *this; // Evita autoasignación
    
    this->Vaciar(); // Vacía la pila actual antes de copiar
    
    Elemento *copia = p.tope; // Puntero auxiliar para recorrer la pila original
    Elemento *arr[p.numElem]; // Arreglo temporal para almacenar los elementos de la pila original
    
    // Copia los elementos en un arreglo temporal en orden inverso
    for(int i = p.numElem - 1; i >= 0; --i) {
        arr[i] = copia;
        copia = copia->siguiente;
    }
    
    // Restaura la pila con los elementos en el orden correcto
    for(int i = 0; i < p.numElem; ++i) Apilar(arr[i]->valor);
    
    return *this;
}

//************************************************************************************************

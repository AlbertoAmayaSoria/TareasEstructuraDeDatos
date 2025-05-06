#include <iostream>
#include <queue>

// Constructor por defecto: inicializa la raíz como nula y la cantidad de elementos en cero
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB() : cantElem(0), raiz(nullptr) /*, cantElem(0)*/ {}

// Constructor de copia: copia el árbol de otro objeto ArbolB
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB(const ArbolB &c) : raiz(CopiarArbol(c.raiz)), cantElem(c.cantElem) {}

// Operador de asignación: permite asignar un árbol a otro
template <typename Type, int grado>
ArbolB<Type, grado>& ArbolB<Type, grado>::operator=(const ArbolB &c) {
    if(this != &c) {
        Vaciar(); // Vacía el árbol actual
        raiz = CopiarArbol(c.raiz); // Copia el árbol de c
        cantElem = c.cantElem; // Copia la cantidad de elementos
    }
    return *this;
}

// Destructor: libera la memoria ocupada por el árbol
template <typename Type, int grado>
ArbolB<Type, grado>::~ArbolB() {
    Vaciar(); // Elimina todos los nodos del árbol
}

// Método para copiar el árbol (recursivo)
template <typename Type, int grado>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::CopiarArbol(Nodo* subraiz) {
    if(subraiz == nullptr) return nullptr; // Si el nodo es nulo, no hay nada que copiar
    
    Nodo* nuevoNodo = new Nodo(); // Crea un nuevo nodo
    nuevoNodo->elemNodo = subraiz->elemNodo; // Copia el número de elementos
    
    // Copia las claves del nodo
    for(int i = 0; i < subraiz->elemNodo; ++i) {
        nuevoNodo->claves[i] = subraiz->claves[i];
    }
    
    // Copia los hijos del nodo de manera recursiva
    for(int i = 0; i <= subraiz->elemNodo; ++i) {
        nuevoNodo->hijo[i] = CopiarArbol(subraiz->hijo[i]);
    }
    
    return nuevoNodo; // Devuelve el nuevo nodo copiado
}

// Método público para agregar un elemento al árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if(raiz == nullptr) {
        raiz = new Nodo(); // Si el árbol está vacío, crea un nodo raíz
        raiz->claves[0] = valor; // Asigna el valor al primer espacio del nodo raíz
        raiz->elemNodo = 1; // El nodo raíz tiene un elemento
        ++cantElem; // Aumenta la cantidad de elementos
    } else {
        Agregar(valor, raiz); // Si ya hay elementos, insertamos el elemento en el nodo raíz
        
        // Si la raíz está llena, se divide en dos
        if(raiz->elemNodo == grado) {
            Nodo* nuevaRaiz = new Nodo(); // Crea una nueva raíz
            nuevaRaiz->hijo[0] = raiz; // El hijo de la nueva raíz es la vieja raíz
            dividirNodo(nuevaRaiz, 0); // Divide el nodo raíz
            raiz = nuevaRaiz; // La nueva raíz se convierte en la raíz del árbol
        }
    }
}

// Método privado para agregar un elemento en un nodo específico
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    int i = subraiz->elemNodo - 1; // Empieza en el último elemento del nodo
    
    if(EsHoja(subraiz)) { // Si el nodo es hoja
        // Mueve las claves mayores para hacer espacio
        while(i >= 0 && valor < subraiz->claves[i]) {
            subraiz->claves[i+1] = subraiz->claves[i];
            --i;
        }
        
        // Inserta la nueva clave
        subraiz->claves[i+1] = valor;
        subraiz->elemNodo++; // Aumenta el número de elementos en el nodo
        ++cantElem; // Aumenta el contador de elementos
    } else {
        // Si no es hoja, encontramos el hijo adecuado para insertar el valor
        while(i >= 0 && valor < subraiz->claves[i]) {
            --i;
        }
        ++i;
        
        if(subraiz->hijo[i] == nullptr) {
            subraiz->hijo[i] = new Nodo(); // Si no existe el hijo, lo creamos
        }
        
        Agregar(valor, subraiz->hijo[i]); // Llama recursivamente para agregar el valor al hijo
        
        // Si el hijo se llenó, se debe dividir
        if(subraiz->hijo[i]->elemNodo == grado) {
            dividirNodo(subraiz, i); // Divide el hijo
        }
    }
}

// Método para dividir un nodo cuando está lleno
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo]; // Nodo hijo que se va a dividir
    Nodo* nuevoNodo = new Nodo(); // Crea un nuevo nodo
    int medio = grado / 2; // Calcula la mitad del grado
    
    nuevoNodo->elemNodo = medio; // El nuevo nodo tendrá la mitad de los elementos del nodo original
    
    // Copia las claves al nuevo nodo
    for(int i = 0; i < medio; ++i) {
        nuevoNodo->claves[i] = hijo->claves[medio + 1 + i];
    }
    
    // Si no es hoja, copia también los hijos
    if(!EsHoja(hijo)) {
        for(int i = 0; i <= medio; ++i) {
            nuevoNodo->hijo[i] = hijo->hijo[medio + 1 + i];
        }
    }
    
    hijo->elemNodo = medio; // El nodo original tiene ahora la mitad de los elementos
    
    // Mueve las claves y los hijos en el padre para hacer espacio
    for(int i = padre->elemNodo; i > indiceHijo; --i) {
        padre->claves[i] = padre->claves[i-1];
        padre->hijo[i+1] = padre->hijo[i];
    }
    
    // Inserta la clave media en el padre
    padre->claves[indiceHijo] = hijo->claves[medio];
    padre->hijo[indiceHijo+1] = nuevoNodo;
    padre->elemNodo++; // Aumenta el número de elementos del padre
}

// Método para verificar si un nodo es hoja
template <typename Type, int grado>
bool ArbolB<Type, grado>::EsHoja(Nodo* nodo) const {
    if(nodo == nullptr) return true; // Si el nodo es nulo, es considerado hoja
    for(int i = 0; i <= nodo->elemNodo; ++i) {
        if(nodo->hijo[i] != nullptr) {
            return false; // Si tiene algún hijo, no es hoja
        }
    }
    return true; // Si no tiene hijos, es hoja
}

// Método para buscar un elemento en el árbol
template <typename Type, int grado>
bool ArbolB<Type, grado>::Buscar(Type valor) const {
    return Buscar(valor, raiz);
}

// Método privado recursivo para buscar un elemento en un subárbol
template <typename Type, int grado>
bool ArbolB<Type, grado>::Buscar(Type valor, Nodo* subraiz) const {
    if(subraiz == nullptr) return false;
    
    int i = 0;
    while(i < subraiz->elemNodo && valor > subraiz->claves[i]) {
        ++i;
    }
    
    if(i < subraiz->elemNodo && valor == subraiz->claves[i]) {
        return true;
    }
    
    return Buscar(valor, subraiz->hijo[i]);
}

// Métodos de eliminación (aún no implementados)
template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor) {
    // Eliminación del valor (pendiente de implementación)
}

template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor, Nodo* subraiz) {
    // Eliminación recursiva (pendiente de implementación)
}

// Métodos auxiliares para la eliminación (pendientes)
template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerPredecesor(Nodo* subraiz) {
    // Obtención del predecesor (pendiente de implementación)
}

template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerSucesor(Nodo* subraiz) {
    // Obtención del sucesor (pendiente de implementación)
}

template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoIzq(Nodo* padre, int indiceHijo) {
    // Prestarse del hermano izquierdo (pendiente de implementación)
}

template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoDer(Nodo* padre, int indiceHijo) {
    // Prestarse del hermano derecho (pendiente de implementación)
}

template <typename Type, int grado>
void ArbolB<Type, grado>::FusionarHijos(Nodo* padre, int indiceHijo) {
    // Fusionar hijos (pendiente de implementación)
}

// Métodos para vaciar el árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar() {
    Vaciar(raiz); // Llama al método recursivo para vaciar el árbol
    raiz = nullptr; // La raíz queda como nula
    cantElem = 0; // La cantidad de elementos se establece en cero
}

template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar(Nodo* nodo) {
    if(nodo == nullptr) return; // Si el nodo es nulo, no hace nada
    
    if(!EsHoja(nodo)) { // Si no es hoja, vacía los hijos primero
        for(int i = 0; i <= nodo->elemNodo; ++i) {
            Vaciar(nodo->hijo[i]);
        }
    }
    
    delete nodo; // Libera la memoria del nodo
}

// Métodos para imprimir el árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc() const {
    ImprimirAsc(raiz); // Llama al método recursivo para imprimir en orden ascendente
    std::cout << std::endl;
}

// Método recursivo para imprimir en orden ascendente
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc(Nodo* nodo) const {
    if(nodo == nullptr) return; // Si el nodo es nulo, no hace nada
    
    for(int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i]); // Imprime los hijos primero
        std::cout << nodo->claves[i] << " "; // Luego imprime la clave
    }
    ImprimirAsc(nodo->hijo[nodo->elemNodo]); // Imprime el último hijo
}

// Método para imprimir en orden descendente
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes() const {
    ImprimirDes(raiz); // Llama al método recursivo para imprimir en orden descendente
    std::cout << std::endl;
}

// Método recursivo para imprimir en orden descendente
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes(Nodo* nodo) const {
    if(nodo == nullptr) return; // Si el nodo es nulo, no hace nada
    
    ImprimirDes(nodo->hijo[nodo->elemNodo]); // Imprime el último hijo
    for(int i = nodo->elemNodo-1; i >= 0; --i) {
        std::cout << nodo->claves[i] << " "; // Luego imprime las claves en orden inverso
        ImprimirDes(nodo->hijo[i]); // Finalmente imprime los hijos
    }
}

// Método para imprimir los niveles del árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirNiveles() const {
    if(raiz == nullptr) return; // Si el árbol está vacío, no hace nada
    
    std::queue<Nodo*> cola;
    cola.push(raiz); // Empuja la raíz a la cola
    
    // Procesa cada nivel del árbol
    while(!cola.empty()) {
        int tamanoNivel = cola.size(); // Número de nodos en el nivel actual
        
        for(int i = 0; i < tamanoNivel; ++i) {
            Nodo* actual = cola.front(); // Toma el primer nodo de la cola
            cola.pop();
            
            std::cout << "[";
            for(int j = 0; j < actual->elemNodo; ++j) {
                std::cout << actual->claves[j];
                if(j < actual->elemNodo-1) std::cout << " ";
            }
            std::cout << "] ";
            
            // Si no es hoja, agrega sus hijos a la cola
            if(!EsHoja(actual)) {
                for(int j = 0; j <= actual->elemNodo; ++j) {
                    if(actual->hijo[j] != nullptr) {
                        cola.push(actual->hijo[j]);
                    }
                }
            }
        }
        std::cout << std::endl; // Salto de línea después de cada nivel
    }
}

// Método para obtener la cantidad de elementos en el árbol
template <typename Type, int grado>
int ArbolB<Type, grado>::CantElem() const {
    return cantElem; // Devuelve la cantidad de elementos
}


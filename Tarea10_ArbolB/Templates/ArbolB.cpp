#include "../Headers/ArbolB.hpp"
#include <iostream>
#include <stdexcept>

//comentariop

// Constructor por defecto
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB() : cantElem(0), raiz(nullptr) {}

// Constructor de copia
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB(const ArbolB<Type, grado>& c) {
    *this = c;
}

// Destructor
template <typename Type, int grado>
ArbolB<Type, grado>::~ArbolB() {
    Vaciar();
}

// Operador de asignación
template <typename Type, int grado>
ArbolB<Type, grado>& ArbolB<Type, grado>::operator=(const ArbolB<Type, grado>& c) {
    if (this == &c) return *this;

    Vaciar();
    if (c.raiz != nullptr) {
        raiz = CopiarArbol(c.raiz);
        cantElem = c.cantElem;
    }

    return *this;
}

// Método CopiarArbol
template <typename Type, int grado>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::CopiarArbol(Nodo* subraiz) {
    if (subraiz == nullptr)
        return nullptr;

    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->elemNodo = subraiz->elemNodo;

    // Copiar las claves
    for (int i = 0; i < subraiz->elemNodo; ++i) {
        nuevoNodo->claves[i] = subraiz->claves[i];
    }

    // Copiar los hijos si no es hoja
    for (int i = 0; i <= subraiz->elemNodo; ++i) {
        nuevoNodo->hijo[i] = CopiarArbol(subraiz->hijo[i]);
    }

    return nuevoNodo;
}


template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if (raiz == nullptr) {  // Si el árbol está vacío
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        ++cantElem;
        std::cout << " insertando elemento raiz" << std::endl;
        for (int i = 0; i < grado; ++i) {
            raiz->hijo[i] = nullptr; // Asegurarnos de que los hijos se inicialicen correctamente
            std::cout << "Hijo nulo" << std::endl;
        }
    } else {
        Agregar(valor, raiz); // Llamada recursiva para agregar el valor en la raíz
    }
}

// Método recursivo para agregar el valor en el árbol B
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    if(EsHoja(subraiz) && subraiz->elemNodo <= grado){
        //Si es hoja y el nodo tiene espacio 
        int i = subraiz->elemNodo - 1;
        //Mover claves mayores hacia adelante para hacer espacio
        while(i >= 0 && valor < subraiz->claves[i]){
            subraiz->claves[i + 1] = subraiz->claves[i];
            --i;
        }
        //Insertar el valor
        subraiz->claves[i + 1] = valor;
        //Aumentar el contador de elementos
        subraiz->elemNodo++;

    if(subraiz->elemNodo == grado) dividirNodo(subraiz, (grado/2) -1 );
    } else {
        // Encontrar el hijo adecuado
        int i = 0;
        while (i < subraiz->elemNodo && valor > subraiz->claves[i]) {
            i++;
        }

        // Si el hijo está lleno, se divide
        if (subraiz->hijo[i] != nullptr && subraiz->hijo[i]->elemNodo == grado - 1) {
            dividirNodo(subraiz, i);

            // Después de la división, puede que tengamos que insertar en el hijo derecho
            if (valor > subraiz->claves[i]) {
                i++;
            }
        }

        // Recursión: insertamos en el hijo correspondiente
        if (subraiz->hijo[i] != nullptr) {
            Agregar(valor, subraiz->hijo[i]);
        }
    }

    /*if (EsHoja(subraiz) && subraiz->elemNodo < grado - 1) {
        // Si es hoja y el nodo tiene espacio
        int i = subraiz->elemNodo - 1;
        // Mover claves mayores hacia adelante para hacer espacio
        while (i >= 0 && valor < subraiz->claves[i]) {
            subraiz->claves[i + 1] = subraiz->claves[i];
            i--;
        }
        subraiz->claves[i + 1] = valor; // Insertar el valor
        subraiz->elemNodo++; // Incrementar el contador de elementos
        ++cantElem;
    } else {
        // Encontrar el hijo adecuado
        int i = 0;
        while (i < subraiz->elemNodo && valor > subraiz->claves[i]) {
            i++;
        }

        // Si el hijo está lleno, se divide
        if (subraiz->hijo[i] != nullptr && subraiz->hijo[i]->elemNodo == grado - 1) {
            dividirNodo(subraiz, i);

            // Después de la división, puede que tengamos que insertar en el hijo derecho
            if (valor > subraiz->claves[i]) {
                i++;
            }
        }

        // Recursión: insertamos en el hijo correspondiente
        if (subraiz->hijo[i] != nullptr) {
            Agregar(valor, subraiz->hijo[i]);
        }
    }*/
}

// Método para verificar si un nodo es hoja
template <typename Type, int grado>
bool ArbolB<Type, grado>::EsHoja(Nodo* nodo) {
    for (int i = 0; i < grado; ++i) { // Verifica hasta grado - 1
        if (nodo->hijo[i] != nullptr)
            return false;
    }
    return true;
}



// Método para dividir un nodo lleno
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* subraiz, int indiceHijo) {
    Nodo* hijoIzquierdo = subraiz->hijo[indiceHijo];
    
    if (hijoIzquierdo == nullptr) {
        std::cerr << "Error: Nodo hijo izquierdo es nulo durante la división." << std::endl;
        return;
    }

    Nodo* hijoDerecho = new Nodo();
    int mitad = grado / 2;

    // Asegurarse de que la división sea posible
    if (hijoIzquierdo->elemNodo < grado) {
        std::cerr << "Error: Nodo hijo izquierdo no está lleno, no se puede dividir." << std::endl;
        return;
    }

    // El nodo hijo izquierdo tiene 'grado - 1' elementos
    // Necesitamos dividirlo en dos: una mitad va al nodo padre (subraiz)
    // y la otra mitad va al nuevo nodo hijo derecho.
    
    // Transferir las claves y los hijos a los nodos izquierdo y derecho
    hijoDerecho->elemNodo = grado - 1 - mitad;
    for (int i = 0; i < hijoDerecho->elemNodo; ++i) {
        hijoDerecho->claves[i] = hijoIzquierdo->claves[i + mitad + 1];
    }

    // Transferir los hijos a hijoDerecho
    if (!EsHoja(hijoIzquierdo)) {
        for (int i = 0; i <= hijoDerecho->elemNodo; ++i) {
            hijoDerecho->hijo[i] = hijoIzquierdo->hijo[i + mitad + 1];
        }
    }

    hijoIzquierdo->elemNodo = mitad; // El hijo izquierdo se queda con la mitad de las claves

    // Ahora necesitamos mover la clave central del nodo hijo al nodo padre
    for (int i = subraiz->elemNodo; i > indiceHijo; --i) {
        subraiz->claves[i] = subraiz->claves[i - 1];
        subraiz->hijo[i + 1] = subraiz->hijo[i];
    }

    subraiz->claves[indiceHijo] = hijoIzquierdo->claves[mitad]; // Promover la clave central
    subraiz->hijo[indiceHijo + 1] = hijoDerecho; // El nuevo hijo derecho
    subraiz->elemNodo++; // Incrementar el número de elementos del nodo padre
}





//
template <typename Type, int grado>
int ArbolB<Type, grado>::CantElem() const{
    return cantElem;
}

// Método para vaciar el árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar() {
    // Llamada recursiva para liberar memoria de los nodos
    Vaciar(raiz);
    raiz = nullptr;
    cantElem = 0;
}

// Método recursivo privado para vaciar los nodos
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar(Nodo* nodo) {
    if (nodo == nullptr) return;

    // Recorrer todos los hijos del nodo
    for (int i = 0; i <= nodo->elemNodo; ++i) {
        Vaciar(nodo->hijo[i]);  // Llamada recursiva para liberar los hijos
    }

    // Liberar el nodo
    delete nodo;
}

// Método de impresión ascendente
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc() const {
    ImprimirAsc(raiz, 0);
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc(Nodo* nodo, int nivel) const {
    if (nodo == nullptr) {
        std::cout << "Nodo nulo." << std::endl;
        return;
    }

    std::cout << "Nivel: " << nivel << " - Nodo con " << nodo->elemNodo << " elementos." << std::endl;

    // Imprimir todas las claves de este nodo
    for (int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i], nivel + 1); // Imprimir subnodos
        std::cout << nodo->claves[i] << " ";   // Imprimir claves
    }

    // Imprimir el último hijo si existe
    if (nodo->hijo[nodo->elemNodo] != nullptr) {
        ImprimirAsc(nodo->hijo[nodo->elemNodo], nivel + 1);
    }
}


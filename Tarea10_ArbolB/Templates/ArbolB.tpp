#include "../Headers/ArbolB.hpp"
#include <iostream>
#include <stdexcept>

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

// Método para agregar un valor
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if (raiz == nullptr) {  // Si el árbol está vacío
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        for (int i = 0; i <= grado; ++i) {
            raiz->hijo[i] = nullptr;
        }
    } else {
        Agregar(valor, raiz);
    }
}

// Método recursivo para agregar
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    // Si es hoja, insertar ahí
    if (EsHoja(subraiz)) {
        int i = subraiz->elemNodo - 1;
        // Mover claves mayores hacia adelante
        while (i >= 0 && valor < subraiz->claves[i]) {
            subraiz->claves[i + 1] = subraiz->claves[i];
            i--;
        }
        subraiz->claves[i + 1] = valor;
        subraiz->elemNodo++;
    } else {
        // Encontrar el hijo adecuado
        int i = 0;
        while (i < subraiz->elemNodo && valor > subraiz->claves[i])
            i++;

        // Verificar si el hijo está lleno
        if (subraiz->hijo[i] != nullptr && subraiz->hijo[i]->elemNodo == grado - 1) {
            dividirNodo(subraiz, i);

            // Después de la división, puede que tengamos que insertar en el hijo derecho
            if (valor > subraiz->claves[i])
                i++;
        }

        // Recursivamente agregar en el hijo correspondiente
        Agregar(valor, subraiz->hijo[i]);
    }
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

// Método para dividir un nodo
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* padre, int i) {
    Nodo* hijoY = padre->hijo[i];
    Nodo* hijoZ = new Nodo();

    int t = (grado - 1) / 2;  // punto medio

    // Copiar claves a hijoZ
    hijoZ->elemNodo = grado - 1 - t;
    for (int j = 0; j < hijoZ->elemNodo; ++j) {
        hijoZ->claves[j] = hijoY->claves[j + t + 1];
    }

    // Copiar los hijos si no es hoja
    if (!EsHoja(hijoY)) {
        for (int j = 0; j <= hijoZ->elemNodo; ++j) {
            hijoZ->hijo[j] = hijoY->hijo[j + t + 1];
        }
    }

    hijoY->elemNodo = t;

    // Mover hijos del padre
    for (int j = padre->elemNodo; j >= i + 1; --j) {
        padre->hijo[j + 1] = padre->hijo[j];
    }
    padre->hijo[i + 1] = hijoZ;

    // Mover claves del padre
    for (int j = padre->elemNodo - 1; j >= i; --j) {
        padre->claves[j + 1] = padre->claves[j];
    }
    padre->claves[i] = hijoY->claves[t];

    padre->elemNodo++;
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


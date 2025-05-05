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


// Método principal para agregar un valor
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if (raiz == nullptr) {  // Si el árbol está vacío
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        ++cantElem;
        std::cout << "Insertando elemento raíz" << std::endl;
        for (int i = 0; i < grado; ++i) {
            raiz->hijo[i] = nullptr;
            std::cout << "Hijo nulo" << std::endl;
        }
    } else {
        Agregar(valor, raiz);  // Llamar a la versión recursiva
    }
}





template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    int i = 0;

    // Si el nodo es hoja y tiene espacio, simplemente inserta el valor
    if (EsHoja(subraiz) && subraiz->elemNodo < grado) {
        // Mover claves mayores hacia adelante para hacer espacio
        while (i < subraiz->elemNodo && valor > subraiz->claves[i]) {
            i++;
        }

        // Insertar el valor
        for (int j = subraiz->elemNodo - 1; j >= i; --j) {
            subraiz->claves[j + 1] = subraiz->claves[j];
        }
        subraiz->claves[i] = valor;
        subraiz->elemNodo++;
        ++cantElem;
        std::cout << "Insertando elemento" << std::endl;

        // Si el nodo está lleno, dividirlo
        if (subraiz->elemNodo == grado) {
            dividirNodo(subraiz, i);
        }
    } else {
        // Si no es hoja, encontrar el hijo adecuado y asegurarse de que existe
        while (i < subraiz->elemNodo && valor > subraiz->claves[i]) {
            i++;
        }

        // Si el hijo correspondiente no existe, créalo.
        if (subraiz->hijo[i] == nullptr) {
            subraiz->hijo[i] = new Nodo();
            for (int j = 0; j < grado; ++j) {
                subraiz->hijo[i]->hijo[j] = nullptr;
            }
        }

        // Llamar recursivamente para agregar el valor al hijo adecuado
        Agregar(valor, subraiz->hijo[i]);
    }
}

// Método para verificar si un nodo es hoja
template <typename Type, int grado>
bool ArbolB<Type, grado>::EsHoja(Nodo* nodo) {
    for (int i = 0; i <= nodo->elemNodo; ++i) {
        if (nodo->hijo[i] != nullptr) {
            return false;  // Si encontramos un hijo no nulo, no es hoja
        }
    }
    return true;  // Si todos los hijos son nulos, es una hoja
}



// Generalizar el metodo 
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* subraiz, int indiceHijo) {
    //Nodo* hijoIzquierdo = subraiz->hijo[indiceHijo];
    Nodo* hijoIzquierdo = new Nodo(); // Nuevo nodo izquierdo
    Nodo* hijoDerecho = new Nodo();  // Nuevo nodo derecho

    int t = grado / 2;  // Tamaño de la mitad (número de claves que se moverán)
   
    subraiz->hijo[indiceHijo] = hijoIzquierdo;
    subraiz->hijo[indiceHijo + 1] = hijoDerecho;

    // Transferir las claves a cada hijo
    for(int i = 0 ; i < t ; ++i){
        hijoIzquierdo->claves[i] = subraiz->claves[i];
        subraiz->claves[i] = Type(); // Limpiar las claves copiadas de la raiz
        hijoIzquierdo->elemNodo++;
        subraiz->elemNodo--;
    }
    subraiz->claves[indiceHijo] = subraiz->claves[t];
    
    for(int i = t + 1 ; i < grado ; ++i){
        hijoDerecho->claves[i - (t + 1)] = subraiz->claves[i];
        subraiz->claves[i] = Type(); // Limpiar las claves copiadas de la raiz
        hijoDerecho->elemNodo++;
        subraiz->elemNodo--;
    }


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

    //Imprimir todas las claves de este nodo
    for (int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i], nivel + 1); // Imprimir subnodos
        //std::cout << nodo->claves[i] << " ";   // Imprimir claves
    }

    // Imprimir el último hijo si existe
    if (nodo->hijo[nodo->elemNodo] != nullptr) {
        ImprimirAsc(nodo->hijo[nodo->elemNodo], nivel + 1);
    }
}


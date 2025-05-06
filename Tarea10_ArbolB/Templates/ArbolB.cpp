#include <iostream>
#include <queue>
#include <algorithm>

// Constructor por defecto
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB() : raiz(nullptr), cantElem(0) {}

// Constructor de copia
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB(const ArbolB &c) : raiz(CopiarArbol(c.raiz)), cantElem(c.cantElem) {}

// Operador de asignación
template <typename Type, int grado>
ArbolB<Type, grado>& ArbolB<Type, grado>::operator=(const ArbolB &c) {
    if(this != &c) {
        Vaciar();
        raiz = CopiarArbol(c.raiz);
        cantElem = c.cantElem;
    }
    return *this;
}

// Destructor
template <typename Type, int grado>
ArbolB<Type, grado>::~ArbolB() {
    Vaciar();
}

// Implementación de EsHoja
template <typename Type, int grado>
bool ArbolB<Type, grado>::EsHoja(Nodo* nodo) const {
    if(nodo == nullptr) return true;
    for(int i = 0; i <= nodo->elemNodo; ++i) {
        if(nodo->hijo[i] != nullptr) {
            return false;
        }
    }
    return true;
}

// Método auxiliar para limpiar claves
template <typename Type, int grado>
void ArbolB<Type, grado>::LimpiarClave(Nodo* nodo, int index) {
    if(index >= 0 && index < grado-1) {
        nodo->claves[index] = Type();
    }
}

// Método para copiar el árbol
template <typename Type, int grado>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::CopiarArbol(Nodo* subraiz) {
    if(!subraiz) return nullptr;
    
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->elemNodo = subraiz->elemNodo;
    
    for(int i = 0; i < subraiz->elemNodo; ++i) {
        nuevoNodo->claves[i] = subraiz->claves[i];
    }
    
    if(!EsHoja(subraiz)) {
        for(int i = 0; i <= subraiz->elemNodo; ++i) {
            nuevoNodo->hijo[i] = CopiarArbol(subraiz->hijo[i]);
        }
    }
    
    return nuevoNodo;
}

// Método público para agregar
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if(!raiz) {
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        ++cantElem;
        return;
    }

    if(raiz->elemNodo == grado-1) {
        Nodo* nuevaRaiz = new Nodo();
        nuevaRaiz->hijo[0] = raiz;
        dividirNodo(nuevaRaiz, 0);
        raiz = nuevaRaiz;
    }

    Agregar(valor, raiz);
}

// Método privado para agregar
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    int i = subraiz->elemNodo - 1;

    if(EsHoja(subraiz)) {
        while(i >= 0 && valor < subraiz->claves[i]) {
            subraiz->claves[i+1] = subraiz->claves[i];
            --i;
        }
        subraiz->claves[i+1] = valor;
        ++subraiz->elemNodo;
        ++cantElem;
    } else {
        while(i >= 0 && valor < subraiz->claves[i]) --i;
        ++i;

        if(!subraiz->hijo[i]) subraiz->hijo[i] = new Nodo();

        if(subraiz->hijo[i]->elemNodo == grado-1) {
            dividirNodo(subraiz, i);
            if(valor > subraiz->claves[i]) ++i;
        }

        Agregar(valor, subraiz->hijo[i]);
    }
}

// Método para dividir nodo
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* nuevoNodo = new Nodo();
    int medio = (grado-1)/2;
    
    nuevoNodo->elemNodo = (grado-1) - medio - 1;
    
    // Copiar la mitad derecha al nuevo nodo
    for(int i = 0; i < nuevoNodo->elemNodo; ++i) {
        nuevoNodo->claves[i] = hijo->claves[medio + 1 + i];
        LimpiarClave(hijo, medio + 1 + i);
    }
    
    if(!EsHoja(hijo)) {
        for(int i = 0; i <= nuevoNodo->elemNodo; ++i) {
            nuevoNodo->hijo[i] = hijo->hijo[medio + 1 + i];
            hijo->hijo[medio + 1 + i] = nullptr;
        }
    }
    
    hijo->elemNodo = medio;
    
    // Hacer espacio en el padre
    for(int i = padre->elemNodo; i > indiceHijo; --i) {
        padre->claves[i] = padre->claves[i-1];
        padre->hijo[i+1] = padre->hijo[i];
    }
    
    // Insertar la clave media en el padre
    padre->claves[indiceHijo] = hijo->claves[medio];
    LimpiarClave(hijo, medio);
    
    padre->hijo[indiceHijo+1] = nuevoNodo;
    padre->elemNodo++;
}

// Métodos de búsqueda
template <typename Type, int grado>
bool ArbolB<Type, grado>::Buscar(Type valor) const {
    return Buscar(valor, raiz);
}

template <typename Type, int grado>
bool ArbolB<Type, grado>::Buscar(Type valor, Nodo* subraiz) const {
    if(!subraiz) return false;

    int i = 0;
    while(i < subraiz->elemNodo && valor > subraiz->claves[i]) ++i;

    if(i < subraiz->elemNodo && valor == subraiz->claves[i]) return true;
    if(EsHoja(subraiz)) return false;

    return Buscar(valor, subraiz->hijo[i]);
}

// Métodos de eliminación
template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor) {
    if(!raiz) return;

    Eliminar(valor, raiz);

    if(raiz->elemNodo == 0 && !EsHoja(raiz)) {
        Nodo* temp = raiz;
        raiz = raiz->hijo[0];
        delete temp;
    }
}

template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor, Nodo* subraiz) {
    int i = 0;
    while(i < subraiz->elemNodo && valor > subraiz->claves[i]) ++i;

    if(i < subraiz->elemNodo && valor == subraiz->claves[i]) {
        if(EsHoja(subraiz)) {
            // Eliminar clave y limpiar posición
            for(int j = i; j < subraiz->elemNodo-1; ++j) {
                subraiz->claves[j] = subraiz->claves[j+1];
            }
            LimpiarClave(subraiz, subraiz->elemNodo-1);
            subraiz->elemNodo--;
            cantElem--;
        } else {
            if(subraiz->hijo[i]->elemNodo >= (grado)/2) {
                Type pred = ObtenerPredecesor(subraiz->hijo[i]);
                subraiz->claves[i] = pred;
                Eliminar(pred, subraiz->hijo[i]);
            } else if(subraiz->hijo[i+1]->elemNodo >= (grado)/2) {
                Type succ = ObtenerSucesor(subraiz->hijo[i+1]);
                subraiz->claves[i] = succ;
                Eliminar(succ, subraiz->hijo[i+1]);
            } else {
                FusionarHijos(subraiz, i);
                Eliminar(valor, subraiz->hijo[i]);
            }
        }
    } else {
        if(EsHoja(subraiz)) return;

        if(subraiz->hijo[i]->elemNodo < (grado)/2) {
            if(i != 0 && subraiz->hijo[i-1]->elemNodo >= (grado)/2) {
                PrestarseDeHermanoIzq(subraiz, i);
            } else if(i != subraiz->elemNodo && subraiz->hijo[i+1]->elemNodo >= (grado)/2) {
                PrestarseDeHermanoDer(subraiz, i);
            } else {
                if(i != subraiz->elemNodo) {
                    FusionarHijos(subraiz, i);
                } else {
                    FusionarHijos(subraiz, i-1);
                    i--;
                }
            }
        }

        Eliminar(valor, subraiz->hijo[i]);
    }
}

// Métodos auxiliares para eliminación
template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerPredecesor(Nodo* subraiz) {
    while(!EsHoja(subraiz))
        subraiz = subraiz->hijo[subraiz->elemNodo];
    return subraiz->claves[subraiz->elemNodo-1];
}

template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerSucesor(Nodo* subraiz) {
    while(!EsHoja(subraiz))
        subraiz = subraiz->hijo[0];
    return subraiz->claves[0];
}

template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoIzq(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* hermano = padre->hijo[indiceHijo-1];

    for(int i = hijo->elemNodo; i > 0; --i)
        hijo->claves[i] = hijo->claves[i-1];
    
    if(!EsHoja(hijo)) {
        for(int i = hijo->elemNodo+1; i > 0; --i)
            hijo->hijo[i] = hijo->hijo[i-1];
    }

    hijo->claves[0] = padre->claves[indiceHijo-1];
    
    if(!EsHoja(hijo))
        hijo->hijo[0] = hermano->hijo[hermano->elemNodo];

    padre->claves[indiceHijo-1] = hermano->claves[hermano->elemNodo-1];
    LimpiarClave(hermano, hermano->elemNodo-1);

    hijo->elemNodo++;
    hermano->elemNodo--;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoDer(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* hermano = padre->hijo[indiceHijo+1];

    hijo->claves[hijo->elemNodo] = padre->claves[indiceHijo];
    
    if(!EsHoja(hijo))
        hijo->hijo[hijo->elemNodo+1] = hermano->hijo[0];

    padre->claves[indiceHijo] = hermano->claves[0];
    
    for(int i = 1; i < hermano->elemNodo; ++i)
        hermano->claves[i-1] = hermano->claves[i];
    LimpiarClave(hermano, hermano->elemNodo-1);
    
    if(!EsHoja(hermano)) {
        for(int i = 1; i <= hermano->elemNodo; ++i)
            hermano->hijo[i-1] = hermano->hijo[i];
    }

    hijo->elemNodo++;
    hermano->elemNodo--;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::FusionarHijos(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* hermano = padre->hijo[indiceHijo+1];

    hijo->claves[hijo->elemNodo] = padre->claves[indiceHijo];
    hijo->elemNodo++;

    for(int i = 0; i < hermano->elemNodo; ++i) {
        hijo->claves[hijo->elemNodo + i] = hermano->claves[i];
    }
    
    if(!EsHoja(hijo)) {
        for(int i = 0; i <= hermano->elemNodo; ++i) {
            hijo->hijo[hijo->elemNodo + i] = hermano->hijo[i];
        }
    }

    hijo->elemNodo += hermano->elemNodo;

    for(int i = indiceHijo; i < padre->elemNodo-1; ++i) {
        padre->claves[i] = padre->claves[i+1];
        padre->hijo[i+1] = padre->hijo[i+2];
    }
    padre->elemNodo--;
    LimpiarClave(padre, padre->elemNodo);

    delete hermano;
}

// Métodos para vaciar el árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar() {
    Vaciar(raiz);
    raiz = nullptr;
    cantElem = 0;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar(Nodo* nodo) {
    if(!nodo) return;
    
    if(!EsHoja(nodo)) {
        for(int i = 0; i <= nodo->elemNodo; ++i) {
            Vaciar(nodo->hijo[i]);
        }
    }
    
    delete nodo;
}

// Métodos de impresión
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc() const {
    ImprimirAsc(raiz);
    std::cout << std::endl;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc(Nodo* nodo) const {
    if(!nodo) return;
    
    for(int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i]);
        if(nodo->claves[i] != Type()) {
            std::cout << nodo->claves[i] << " ";
        }
    }
    ImprimirAsc(nodo->hijo[nodo->elemNodo]);
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes() const {
    ImprimirDes(raiz);
    std::cout << std::endl;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes(Nodo* nodo) const {
    if(!nodo) return;
    
    ImprimirDes(nodo->hijo[nodo->elemNodo]);
    for(int i = nodo->elemNodo-1; i >= 0; --i) {
        if(nodo->claves[i] != Type()) {
            std::cout << nodo->claves[i] << " ";
        }
        ImprimirDes(nodo->hijo[i]);
    }
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirNiveles() const {
    if(!raiz) return;
    
    std::queue<Nodo*> cola;
    cola.push(raiz);
    
    while(!cola.empty()) {
        int tamanoNivel = cola.size();
        
        for(int i = 0; i < tamanoNivel; ++i) {
            Nodo* actual = cola.front();
            cola.pop();
            
            std::cout << "[";
            bool primero = true;
            for(int j = 0; j < actual->elemNodo; ++j) {
                if(actual->claves[j] != Type()) {
                    if(!primero) std::cout << " ";
                    std::cout << actual->claves[j];
                    primero = false;
                }
            }
            std::cout << "] ";
            
            if(!EsHoja(actual)) {
                for(int j = 0; j <= actual->elemNodo; ++j) {
                    if(actual->hijo[j]) {
                        cola.push(actual->hijo[j]);
                    }
                }
            }
        }
        std::cout << std::endl;
    }
}

// Método para obtener cantidad de elementos
template <typename Type, int grado>
int ArbolB<Type, grado>::CantElem() const {
    return cantElem;
}

#include <iostream>
#include <queue>
#include <stdexcept>

/**
 * @file ArbolB.hpp
 * @brief Implementación de un Árbol B genérico con operaciones básicas.
 * @tparam Type Tipo de datos almacenados.
 * @tparam grado Grado máximo del árbol (máximo de claves por nodo).
 */

/**
 * @brief Constructor por defecto del Árbol B.
 */
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB() : cantElem(0), raiz(nullptr) {}

/**
 * @brief Constructor por copia.
 * @param c Árbol B a copiar.
 */
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB(const ArbolB &c) : raiz(CopiarArbol(c.raiz)), cantElem(c.cantElem) {}

/**
 * @brief Operador de asignación.
 * @param c Árbol B a asignar.
 * @return Referencia al árbol actual.
 */
template <typename Type, int grado>
ArbolB<Type, grado>& ArbolB<Type, grado>::operator=(const ArbolB &c) {
    if(this != &c) {
        Vaciar();
        raiz = CopiarArbol(c.raiz);
        cantElem = c.cantElem;
    }
    return *this;
}

/**
 * @brief Destructor del Árbol B.
 */
template <typename Type, int grado>
ArbolB<Type, grado>::~ArbolB() {
    Vaciar();
}

/**
 * @brief Copia un subárbol.
 * @param subraiz Puntero al nodo raíz del subárbol a copiar.
 * @return Puntero al nuevo subárbol copiado.
 */
template <typename Type, int grado>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::CopiarArbol(Nodo* subraiz) {
    if(subraiz == nullptr) return nullptr;
    
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->elemNodo = subraiz->elemNodo;
    
    for(int i = 0; i < subraiz->elemNodo; ++i) {
        nuevoNodo->claves[i] = subraiz->claves[i];
    }
    
    for(int i = 0; i <= subraiz->elemNodo; ++i) {
        nuevoNodo->hijo[i] = CopiarArbol(subraiz->hijo[i]);
    }
    
    return nuevoNodo;
}

/**
 * @brief Agrega un elemento al árbol.
 * @param valor Valor a insertar.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if(raiz == nullptr) {
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        ++cantElem;
    } else {
        Agregar(valor, raiz);
        
        if(raiz->elemNodo == grado) {
            Nodo* nuevaRaiz = new Nodo();
            nuevaRaiz->hijo[0] = raiz;
            dividirNodo(nuevaRaiz, 0);
            raiz = nuevaRaiz;
        }
    }
}

/**
 * @brief Inserta recursivamente un valor en un subárbol.
 * @param valor Valor a insertar.
 * @param subraiz Nodo raíz del subárbol.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz) {
    int i = subraiz->elemNodo - 1;
    
    if(EsHoja(subraiz)) {
        while(i >= 0 && valor < subraiz->claves[i]) {
            subraiz->claves[i+1] = subraiz->claves[i];
            --i;
        }
        
        subraiz->claves[i+1] = valor;
        subraiz->elemNodo++;
        ++cantElem;
    } else {
        while(i >= 0 && valor < subraiz->claves[i]) {
            --i;
        }
        ++i;
        
        if(subraiz->hijo[i] == nullptr) {
            subraiz->hijo[i] = new Nodo();
        }
        
        Agregar(valor, subraiz->hijo[i]);
        
        if(subraiz->hijo[i]->elemNodo == grado) {
            dividirNodo(subraiz, i);
        }
    }
}

/**
 * @brief Divide un nodo hijo de un nodo padre.
 * @param padre Nodo padre.
 * @param indiceHijo Índice del hijo que se va a dividir.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::dividirNodo(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* nuevoNodo = new Nodo();
    
    int medio = (grado % 2 == 0) ? grado/2 - 1 : grado/2;
    nuevoNodo->elemNodo = grado - medio - 1;
    
    for(int i = 0; i < nuevoNodo->elemNodo; ++i) {
        nuevoNodo->claves[i] = hijo->claves[medio + 1 + i];
    }
    
    if(!EsHoja(hijo)) {
        for(int i = 0; i <= nuevoNodo->elemNodo; ++i) {
            nuevoNodo->hijo[i] = hijo->hijo[medio + 1 + i];
        }
    }
    
    hijo->elemNodo = medio;
    
    for(int i = padre->elemNodo; i > indiceHijo; --i) {
        padre->claves[i] = padre->claves[i-1];
        padre->hijo[i+1] = padre->hijo[i];
    }
    
    padre->claves[indiceHijo] = hijo->claves[medio];
    padre->hijo[indiceHijo+1] = nuevoNodo;
    padre->elemNodo++;
}

/**
 * @brief Verifica si un nodo es hoja.
 * @param nodo Nodo a verificar.
 * @return true si es hoja, false en caso contrario.
 */
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

/**
 * @brief Busca un elemento en el árbol.
 * @param valor Valor a buscar.
 * @return true si se encuentra, false en caso contrario.
 */
template <typename Type, int grado>
bool ArbolB<Type, grado>::Buscar(Type valor) const {
    return Buscar(valor, raiz);
}

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

/**
 * @brief Elimina un valor del árbol.
 * @param valor Valor a eliminar.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor) {
    if(raiz == nullptr) return;
    
    Eliminar(valor, raiz);
    
    if(raiz != nullptr && raiz->elemNodo == 0) {
        Nodo* temp = raiz;
        raiz = EsHoja(raiz) ? nullptr : raiz->hijo[0];
        delete temp;
    }
}

/**
 * @brief Elimina un valor recursivamente desde un nodo dado.
 * @param valor Valor a eliminar.
 * @param subraiz Nodo desde donde se inicia la eliminación.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Eliminar(Type valor, Nodo* subraiz) {
    int i = 0;
    while(i < subraiz->elemNodo && valor > subraiz->claves[i]) {
        ++i;
    }

    if(i < subraiz->elemNodo && valor == subraiz->claves[i]) {
        cantElem--;
        
        if(EsHoja(subraiz)) {
            EliminarDeHoja(subraiz, i);
            if(subraiz != raiz && subraiz->elemNodo < (grado-1)/2) {
                Nodo* padre = EncontrarPadre(raiz, nullptr, subraiz);
                int indice = ObtenerIndiceHijo(padre, subraiz);
                ManejarUnderflow(padre, indice);
            }
        } else {
            EliminarDeNodoInterno(subraiz, i);
        }
    } else {
        if(EsHoja(subraiz)) return;
        
        bool necesitaRebalanceo = (subraiz->hijo[i]->elemNodo <= (grado-1)/2);
        Eliminar(valor, subraiz->hijo[i]);
        
        if(necesitaRebalanceo && subraiz->hijo[i]->elemNodo < (grado-1)/2) {
            ManejarUnderflow(subraiz, i);
        }
    }
}

/**
 * @brief Elimina una clave de un nodo hoja.
 * @param nodo Nodo hoja.
 * @param indice Índice de la clave a eliminar.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::EliminarDeHoja(Nodo* nodo, int indice) {
    for(int j = indice+1; j < nodo->elemNodo; ++j) {
        nodo->claves[j-1] = nodo->claves[j];
    }
    nodo->elemNodo--;
}

/**
 * @brief Elimina una clave de un nodo interno.
 * @param nodo Nodo interno.
 * @param indice Índice de la clave.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::EliminarDeNodoInterno(Nodo* nodo, int indice) {
    Type clave = nodo->claves[indice];
    
    if(nodo->hijo[indice]->elemNodo > (grado-1)/2) {
        Type pred = ObtenerPredecesor(nodo->hijo[indice]);
        nodo->claves[indice] = pred;
        Eliminar(pred, nodo->hijo[indice]);
    } else if(nodo->hijo[indice+1]->elemNodo > (grado-1)/2) {
        Type succ = ObtenerSucesor(nodo->hijo[indice+1]);
        nodo->claves[indice] = succ;
        Eliminar(succ, nodo->hijo[indice+1]);
    } else {
        FusionarHijos(nodo, indice);
        Eliminar(clave, nodo->hijo[indice]);
    }
}

/**
 * @brief Maneja el underflow en un hijo de un nodo padre.
 * @param padre Nodo padre.
 * @param indiceHijo Índice del hijo con underflow.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ManejarUnderflow(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    
    if(hijo->elemNodo >= (grado-1)/2) return;
    
    // Intentar redistribución con hermano izquierdo
    if(indiceHijo > 0 && padre->hijo[indiceHijo-1]->elemNodo > (grado-1)/2) {
        PrestarseDeHermanoIzq(padre, indiceHijo);
        return;
    }
    
    // Intentar redistribución con hermano derecho
    if(indiceHijo < padre->elemNodo && padre->hijo[indiceHijo+1]->elemNodo > (grado-1)/2) {
        PrestarseDeHermanoDer(padre, indiceHijo);
        return;
    }
    
    // Si no se puede redistribuir, fusionar
    if(indiceHijo > 0) {
        FusionarHijos(padre, indiceHijo-1);
    } else {
        FusionarHijos(padre, indiceHijo);
    }
}

/**
 * @brief Redistribuye claves desde el hermano izquierdo.
 * @param padre Nodo padre.
 * @param indiceHijo Índice del hijo que recibe la clave.
 */

template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoIzq(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* hermano = padre->hijo[indiceHijo-1];
    
    for(int i = hijo->elemNodo; i > 0; i--) {
        hijo->claves[i] = hijo->claves[i-1];
    }
    
    if(!EsHoja(hijo)) {
        for(int i = hijo->elemNodo+1; i > 0; i--) {
            hijo->hijo[i] = hijo->hijo[i-1];
        }
    }
    
    hijo->claves[0] = padre->claves[indiceHijo-1];
    padre->claves[indiceHijo-1] = hermano->claves[hermano->elemNodo-1];
    
    if(!EsHoja(hermano)) {
        hijo->hijo[0] = hermano->hijo[hermano->elemNodo];
    }
    
    hijo->elemNodo++;
    hermano->elemNodo--;
}

/**
 * @brief Redistribuye claves desde el hermano derecho.
 * @param padre Nodo padre.
 * @param indiceHijo Índice del hijo que recibe la clave.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::PrestarseDeHermanoDer(Nodo* padre, int indiceHijo) {
    Nodo* hijo = padre->hijo[indiceHijo];
    Nodo* hermano = padre->hijo[indiceHijo+1];
    
    hijo->claves[hijo->elemNodo] = padre->claves[indiceHijo];
    padre->claves[indiceHijo] = hermano->claves[0];
    
    if(!EsHoja(hermano)) {
        hijo->hijo[hijo->elemNodo+1] = hermano->hijo[0];
    }
    
    for(int i = 1; i < hermano->elemNodo; i++) {
        hermano->claves[i-1] = hermano->claves[i];
    }
    
    if(!EsHoja(hermano)) {
        for(int i = 1; i <= hermano->elemNodo; i++) {
            hermano->hijo[i-1] = hermano->hijo[i];
        }
    }
    
    hijo->elemNodo++;
    hermano->elemNodo--;
}

/**
 * @brief Fusiona dos hijos de un nodo padre.
 * @param padre Nodo padre.
 * @param indiceHijo Índice del hijo izquierdo.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::FusionarHijos(Nodo* padre, int indiceHijo) {
    Nodo* hijoIzq = padre->hijo[indiceHijo];
    Nodo* hijoDer = padre->hijo[indiceHijo+1];
    
    hijoIzq->claves[hijoIzq->elemNodo++] = padre->claves[indiceHijo];
    
    for(int i = 0; i < hijoDer->elemNodo; ++i) {
        hijoIzq->claves[hijoIzq->elemNodo++] = hijoDer->claves[i];
    }
    
    if(!EsHoja(hijoDer)) {
        for(int i = 0; i <= hijoDer->elemNodo; ++i) {
            hijoIzq->hijo[hijoIzq->elemNodo + i] = hijoDer->hijo[i];
        }
    }
    
    for(int i = indiceHijo+1; i < padre->elemNodo; ++i) {
        padre->claves[i-1] = padre->claves[i];
        padre->hijo[i] = padre->hijo[i+1];
    }
    padre->elemNodo--;
    
    delete hijoDer;
}

/**
 * @brief Obtiene el predecesor de una clave.
 * @param subraiz Subárbol desde el que buscar.
 * @return Clave predecesora.
 */
template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerPredecesor(Nodo* subraiz) {
    while(!EsHoja(subraiz)) {
        subraiz = subraiz->hijo[subraiz->elemNodo];
    }
    return subraiz->claves[subraiz->elemNodo-1];
}

/**
 * @brief Obtiene el sucesor de una clave.
 * @param subraiz Subárbol desde el que buscar.
 * @return Clave sucesora.
 */
template <typename Type, int grado>
Type ArbolB<Type, grado>::ObtenerSucesor(Nodo* subraiz) {
    while(!EsHoja(subraiz)) {
        subraiz = subraiz->hijo[0];
    }
    return subraiz->claves[0];
}

/**
 * @brief Encuentra el padre de un nodo dado.
 * @param actual Nodo actual.
 * @param padre Nodo padre del actual.
 * @param buscado Nodo a encontrar.
 * @return Nodo padre del buscado, o nullptr si no se encuentra.
 */
template <typename Type, int grado>
typename ArbolB<Type, grado>::Nodo* ArbolB<Type, grado>::EncontrarPadre(Nodo* actual, Nodo* padre, Nodo* buscado) {
    if(actual == buscado) return padre;
    if(EsHoja(actual)) return nullptr;
    
    for(int i = 0; i <= actual->elemNodo; i++) {
        Nodo* encontrado = EncontrarPadre(actual->hijo[i], actual, buscado);
        if(encontrado != nullptr) return encontrado;
    }
    return nullptr;
}

/**
 * @brief Obtiene el índice de un hijo en su nodo padre.
 * @param padre Nodo padre.
 * @param hijo Nodo hijo a localizar.
 * @return Índice del hijo en el arreglo del padre.
 */
template <typename Type, int grado>
int ArbolB<Type, grado>::ObtenerIndiceHijo(Nodo* padre, Nodo* hijo) {
    for(int i = 0; i <= padre->elemNodo; i++) {
        if(padre->hijo[i] == hijo) return i;
    }
    return -1;
}

/**
 * @brief Elimina todos los elementos del árbol.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar() {
    Vaciar(raiz);
    raiz = nullptr;
    cantElem = 0;
}


/**
 * @brief Elimina recursivamente los nodos desde uno dado.
 * @param nodo Nodo raíz del subárbol a eliminar.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar(Nodo* nodo) {
    if(nodo == nullptr) return;
    
    if(!EsHoja(nodo)) {
        for(int i = 0; i <= nodo->elemNodo; ++i) {
            Vaciar(nodo->hijo[i]);
        }
    }
    
    delete nodo;
}

/**
 * @brief Imprime los elementos del árbol en orden ascendente.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc() const {
    ImprimirAsc(raiz);
    std::cout << std::endl;
}

/**
 * @brief Imprime recursivamente en orden ascendente.
 * @param nodo Nodo desde donde imprimir.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc(Nodo* nodo) const {
    if(nodo == nullptr) return;
    
    for(int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i]);
        std::cout << nodo->claves[i] << " ";
    }
    ImprimirAsc(nodo->hijo[nodo->elemNodo]);
}

/**
 * @brief Imprime los elementos del árbol en orden descendente.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes() const {
    ImprimirDes(raiz);
    std::cout << std::endl;
}

/**
 * @brief Imprime recursivamente en orden descendente.
 * @param nodo Nodo desde donde imprimir.
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirDes(Nodo* nodo) const {
    if(nodo == nullptr) return;
    
    ImprimirDes(nodo->hijo[nodo->elemNodo]);
    for(int i = nodo->elemNodo-1; i >= 0; --i) {
        std::cout << nodo->claves[i] << " ";
        ImprimirDes(nodo->hijo[i]);
    }
}

/**
 * @brief Imprime el árbol por niveles (recorrido por amplitud).
 */
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirNiveles() const {
    if(raiz == nullptr) return;
    
    std::queue<Nodo*> cola;
    cola.push(raiz);
    
    while(!cola.empty()) {
        int tamanoNivel = cola.size();
        
        for(int i = 0; i < tamanoNivel; ++i) {
            Nodo* actual = cola.front();
            cola.pop();
            
            std::cout << "[";
            for(int j = 0; j < actual->elemNodo; ++j) {
                std::cout << actual->claves[j];
                if(j < actual->elemNodo-1) std::cout << " ";
            }
            std::cout << "] ";
            
            if(!EsHoja(actual)) {
                for(int j = 0; j <= actual->elemNodo; ++j) {
                    if(actual->hijo[j] != nullptr) {
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

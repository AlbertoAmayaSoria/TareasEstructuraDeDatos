#include <cmath>
#include <iostream>
#include <queue>
#include <stdexcept>

// Constructor por defecto
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB() : cantElem(0), raiz(nullptr) {}

// Constructor de copia
template <typename Type, int grado>
ArbolB<Type, grado>::ArbolB(const ArbolB &c) : raiz(CopiarArbol(c.raiz)), cantElem(c.cantElem) {}

// Operador asignación
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

// Método para copiar árbol
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

// Método público para agregar elemento
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor) {
    if(raiz == nullptr) raiz == new Nodo();

    Agregar(valor, raiz);

    /*if(raiz == nullptr) {
        raiz = new Nodo();
        raiz->claves[0] = valor;
        raiz->elemNodo = 1;
        ++cantElem;
    } else {
        Agregar(valor, raiz);
        
        if(raiz->elemNodo == grado) {
            Nodo* nuevaRaiz = new Nodo();
            nuevaRaiz->hijo[0] = raiz;
            //dividirNodo(nuevaRaiz, 0);
            //raiz = nuevaRaiz;
        }
    }*/
}

//***************************************************************************************************

// Método privado para agregar elemento
template <typename Type, int grado>
void ArbolB<Type, grado>::Agregar(Type valor, Nodo* subraiz){
    
    // Si es el primer elemento del nodo se agrega en la primera posición 
    if(subraiz->elemNodo == 0){
        subraiz->clave[0] = valor;
        subraiz->elemNodo++;
        ++cantElem;
    } else int i = subraiz->elemNodo - 1;

    // Preguntamos si el nodo es hoja
    if(EsHoja(subraiz)){
        // Si es hoja y la cantida de elementos es menor al grado
        if(subraiz->elemNodo < grado) {
            // Insertamos el elemento en su posición
            while (i >= 0 && subraiz->claves[i]) {
                subraiz->claves[i + 1] = subraiz->claves[i];
                --i;
            }
            
            subraiz->claves[i + 1] = valor;
            subraiz->elemNodo++;
            ++cantElem;
        }

    // Si despues de agregar el nodo se llena, mandamos a ordenar el árbol recursivamente desde la raiz
    if(subraiz->elemNodo == grado) OrdenarArbol(raiz);

    } else { // Si el nodo no es hoja, buscamos el hijo correcto para agregar
        while (i >= 0 && valor < subraiz->claves[i]) {
            --i;
        }
        ++i;

        if (subraiz->hijo[i] == nullptr) { // Si el hijo es nulo creamos un nuevo nodo para agregar la clave
            subraiz->hijo[i] = new Nodo();
            Agregar(valor, subraiz->hijo[i]) // Mandamos agregar el valor y la subraiz para agregar
        }

    }
}


















template <typename Type, int grado>
void ArbolB<Type, grado>::OrdenarArbol(Nodo* subraiz){
    std::cout << "El árbol se lleno!!" std::endl; 
}

template <typename Type, int grado>
bool ArbolB<Type, grado>::EsHoja(Nodo* subraiz) const{
    for(int i = 0 ; i < grado ; ++i){
        if(subraiz->hijo[i] != nullptr)
            return false;
    }
    return true;
}



















//***************************************************************************************************

// Métodos para vaciar el árbol
template <typename Type, int grado>
void ArbolB<Type, grado>::Vaciar() {
    Vaciar(raiz);
    raiz = nullptr;
    cantElem = 0;
}

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

// Métodos para imprimir
template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc() const {
    ImprimirAsc(raiz);
    std::cout << std::endl;
}

template <typename Type, int grado>
void ArbolB<Type, grado>::ImprimirAsc(Nodo* nodo) const {
    if(nodo == nullptr) return;
    
    for(int i = 0; i < nodo->elemNodo; ++i) {
        ImprimirAsc(nodo->hijo[i]);
        std::cout << nodo->claves[i] << " ";
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
    if(nodo == nullptr) return;
    
    ImprimirDes(nodo->hijo[nodo->elemNodo]);
    for(int i = nodo->elemNodo-1; i >= 0; --i) {
        std::cout << nodo->claves[i] << " ";
        ImprimirDes(nodo->hijo[i]);
    }
}

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

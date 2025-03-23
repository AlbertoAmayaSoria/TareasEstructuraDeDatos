#include <iostream>
#include "../Headers/Grafica.hpp"
#include "../Headers/Pila.hpp"
#include "../Headers/Cola.hpp"

//*************************************************
Grafica::Grafica(): primero(NULL), ultimo(NULL), numNodos(0), numAristas(0) {}
//*************************************************
Grafica::Grafica(const Grafica &g): primero(NULL), ultimo(NULL), numNodos(0), numAristas(0) {
    *this = g;
}
//*************************************************
Grafica::~Grafica() {
    Vaciar();
}
//*************************************************
Grafica & Grafica::operator=(const Grafica &g) {
    if (this == &g) return *this;
    Vaciar();
    Nodo *nodoVisitado = g.primero;
    while (nodoVisitado != NULL) {
        Agregar(nodoVisitado->nombre);
        nodoVisitado = nodoVisitado->siguiente;
    }
    nodoVisitado = g.primero;
    Arista *aristaVisitada;
    while (nodoVisitado != NULL) {
        aristaVisitada = nodoVisitado->primera;
        while (aristaVisitada != NULL) {
            if (!Buscar(nodoVisitado->nombre, aristaVisitada->adyacente->nombre)) {
                Agregar(nodoVisitado->nombre, aristaVisitada->adyacente->nombre);
            }
            aristaVisitada = aristaVisitada->siguiente;
        }
        nodoVisitado = nodoVisitado->siguiente;
    }
    return *this;
}
//*************************************************
void Grafica::Agregar(char nom) {
    Nodo *nuevo = new Nodo(nom);
    numNodos == 0 ? primero = nuevo : ultimo->siguiente = nuevo;
    ultimo = nuevo;
    ++numNodos;
}
//*************************************************
void Grafica::Agregar(char nomInicial, char nomFinal) {
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if (dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if (dirFinal == NULL) return;
    dirInicial->Agregar(dirFinal);
    dirFinal->Agregar(dirInicial);
    ++numAristas;
}
//*************************************************
void Grafica::Eliminar(char nom) {
    Nodo *ant, *porBorrar = BuscarDireccion(nom, &ant);
    if (porBorrar == NULL) return;
    numAristas -= porBorrar->Vaciar();
    if (ant == NULL) primero = primero->siguiente;
    else ant->siguiente = porBorrar->siguiente;
    if (primero == NULL) ultimo = NULL;
    delete porBorrar;
    --numNodos;
}
//*************************************************
void Grafica::Eliminar(char nomInicial, char nomFinal) {
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if (dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if (dirFinal == NULL) return;
    dirInicial->Eliminar(dirFinal);
    dirFinal->Eliminar(dirInicial);
    --numAristas;
}
//*************************************************
int Grafica::ObtenerNumNodos() const {
    return numNodos;
}
//*************************************************
int Grafica::ObtenerNumAristas() const {
    return numAristas;
}
//*************************************************
int Grafica::ObtenerGrado(char nom) const {
    Nodo *nodoBuscado = BuscarDireccion(nom);
    if (nodoBuscado == NULL) throw "Nodo inexistente";
    return nodoBuscado->grado;
}
//*************************************************
bool Grafica::Buscar(char nom) const {
    return BuscarDireccion(nom) != NULL;
}
//*************************************************
bool Grafica::Buscar(char nomInicial, char nomFinal) const {
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if (dirInicial == NULL) return false;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if (dirFinal == NULL) return false;
    return dirInicial->Buscar(dirFinal);
}
//*************************************************
void Grafica::Imprimir() const {
    Nodo *visitado = primero;
    while (visitado != NULL) {
        std::cout << visitado->nombre << ": ";
        visitado->Imprimir();
        visitado = visitado->siguiente;
        std::cout << std::endl;
    }
}
//*************************************************
void Grafica::Vaciar(char nom) {
    Nodo *porVaciar = BuscarDireccion(nom);
    if (porVaciar == NULL) return;
    numAristas -= porVaciar->Vaciar();
}
//*************************************************
void Grafica::Vaciar() {
    while (primero != NULL) Eliminar(primero->nombre);
}
//*************************************************
Nodo *Grafica::BuscarDireccion(char nom, Nodo **ant /*=NULL*/) const {
    Nodo *aux = primero;
    if (ant != NULL) *ant = NULL;
    while (aux != NULL && aux->nombre != nom) {
        if (ant != NULL) *ant = aux;
        aux = aux->siguiente;
    }
    return aux;
}

//*********************************************************88


// Función para verificar si la gráfica es conexa
bool Grafica::EsConexa() const {
    bool* visitado = new bool[numNodos]{false};
    if (primero == nullptr) {
        delete[] visitado;
        return true;
    }

    // Usamos DFS para recorrer la gráfica
    DFS(primero, visitado);

    // Comprobamos si todos los nodos fueron visitados
    for (int i = 0; i < numNodos; ++i) {
        if (!visitado[i]) {
            delete[] visitado;
            std::cout << "La gráfica NO es conexa." << std::endl;
            return false;  // Si algún nodo no fue visitado, la gráfica no es conexa
        }
    }

    delete[] visitado;
    std::cout << "La gráfica es conexa." << std::endl;
    return true;
}

// Función para verificar si todos los nodos tienen grado par
bool Grafica::TieneGradoPar() const {
    Nodo* nodoActual = primero;
    while (nodoActual != nullptr) {
        std::cout << "Nodo " << nodoActual->nombre << " tiene grado: " << nodoActual->grado << std::endl;
        if (nodoActual->grado % 2 != 0) {
            return false;  // Si encontramos un nodo con grado impar, retornamos false
        }
        nodoActual = nodoActual->siguiente;
    }
    return true;  // Todos los nodos tienen grado par
}


// Función DFS (Depth First Search)
void Grafica::DFS(Nodo* nodo, bool* visitado) const {
    Pila<Nodo*> pila;  // Usamos la Pila proporcionada para hacer DFS
    pila.Apilar(nodo);

    while (!pila.EstaVacia()) {
        Nodo* nodoActual = pila.ObtenerTope();
        pila.Desapilar();

        if (!visitado[nodoActual->nombre - '1']) {
            visitado[nodoActual->nombre - '1'] = true;
            Arista* arista = nodoActual->primera;
            while (arista != nullptr) {
                Nodo* adyacente = arista->adyacente;
                if (!visitado[adyacente->nombre - '1']) {
                    pila.Apilar(adyacente);
                }
                arista = arista->siguiente;
            }
        }
    }
}


// Implementación del BFS (Breadth First Search) usando estructuras genéricas (Pila o Cola)
template <typename T>
void Grafica::BFS(Nodo* nodo, bool* visitado, T& estructura) const {
    estructura.Encolar(nodo);  // Usamos Encolar de forma genérica
    visitado[nodo->nombre - '1'] = true;

    while (!estructura.EstaVacia()) {
        Nodo* actual = estructura.ConocerPrim();  // ConocerPrim para Cola
        estructura.Desencolar();  // Desencolamos de forma genérica

        Arista* arista = actual->primera;
        while (arista != nullptr) {
            Nodo* adyacente = arista->adyacente;
            if (!visitado[adyacente->nombre - '1']) {
                visitado[adyacente->nombre - '1'] = true;
                estructura.Encolar(adyacente);  // Encolamos el nodo adyacente no visitado
            }
            arista = arista->siguiente;
        }
    }
}

// Función adaptada para encontrar el camino euleriano
void Grafica::CaminoEuleriano() {
    // Verificamos si la gráfica es conexa y si tiene todos los grados pares.
    if (!EsConexa() || !TieneGradoPar()) {
        std::cout << "La gráfica no tiene un camino euleriano." << std::endl;
        return;
    }

    // Usamos una cola para recorrer los nodos en BFS
    Cola<Nodo*> cola;
    Pila<Nodo*> pila;  // Usamos la pila como indica el algoritmo de Fleury

    Nodo* v_c = primero;  // Nodo inicial (cualquier vértice)
    Nodo* v_p = v_c;      // El mismo vértice es v_p en el primer paso

    cola.Encolar(v_c);
    pila.Apilar(v_c);

    // Mientras haya nodos en la cola
    while (!cola.EstaVacia()) {
        v_c = cola.ConocerPrim();  // Obtenemos el nodo al frente de la cola
        cola.Desencolar();         // Desencolamos el nodo

        // Mientras haya aristas, seguimos buscando el camino Euleriano
        while (v_c->grado > 0) {
            Arista* arista = v_c->primera;
            Nodo* w = nullptr;

            // Buscamos una arista donde el grado de w no sea 1
            while (arista != nullptr) {
                w = arista->adyacente;
                if (w->grado != 1) {
                    break;
                }
                arista = arista->siguiente;
            }

            // Si encontramos una arista adecuada
            if (w != nullptr) {
                // Eliminamos la arista de la gráfica
                Eliminar(v_c->nombre, w->nombre);
                std::cout << "Eliminando arista: " << v_c->nombre << " - " << w->nombre << std::endl;

                // Agregamos w a la cola
                cola.Encolar(w);
                v_c = w;  // Movemos a v_c
            } 
            // Si no encontramos una arista adecuada, usamos el vértice anterior (v_p)
            else {
                // Elegimos la única arista de v_p
                Nodo* k = v_p->primera->adyacente;
                Eliminar(v_p->nombre, k->nombre);
                std::cout << "Eliminando arista: " << v_p->nombre << " - " << k->nombre << std::endl;

                // Agregamos k a la pila
                pila.Apilar(k);
                v_p = k;  // Movemos a v_p
            }
        }
    }

    // Ahora imprimimos el camino euleriano
    std::cout << "Camino Euleriano: ";

    // Primero, imprimimos los nodos de la pila
    // La pila contiene el recorrido de nodos en el camino Euleriano
    while (!pila.EstaVacia()) {
        std::cout << pila.ObtenerTope()->nombre << " -> ";
        pila.Desapilar();
    }

    std::cout << "Fin" << std::endl;
}


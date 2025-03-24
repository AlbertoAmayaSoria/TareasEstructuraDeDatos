/**
 * @file Grafica.cpp
 * @brief Implementación de la clase Grafica para representar un grafo no dirigido.
 */

#include <iostream>
#include "../Headers/Grafica.hpp"
#include "../Headers/Pila.hpp"
#include "../Headers/Cola.hpp"

//*************************************************
/**
 * @brief Constructor por defecto de la clase Grafica.
 * Inicializa la gráfica como vacía.
 */
Grafica::Grafica(): primero(NULL), ultimo(NULL), numNodos(0), numAristas(0) {}

//*************************************************
/**
 * @brief Constructor de copia de la clase Grafica.
 * @param g Objeto de la clase Grafica a copiar.
 */
Grafica::Grafica(const Grafica &g): primero(NULL), ultimo(NULL), numNodos(0), numAristas(0) {
    *this = g;
}

//*************************************************
/**
 * @brief Destructor de la clase Grafica.
 * Libera toda la memoria utilizada por la gráfica.
 */
Grafica::~Grafica() {
    Vaciar();
}

//*************************************************
/**
 * @brief Sobrecarga del operador de asignación.
 * @param g Objeto de la clase Grafica a asignar.
 * @return Referencia a la instancia actual de Grafica.
 */
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
/**
 * @brief Agrega un nodo a la gráfica.
 * @param nom Nombre del nodo a agregar.
 */
void Grafica::Agregar(char nom) {
    Nodo *nuevo = new Nodo(nom);
    numNodos == 0 ? primero = nuevo : ultimo->siguiente = nuevo;
    ultimo = nuevo;
    ++numNodos;
}

//*************************************************
/**
 * @brief Agrega una arista entre dos nodos.
 * @param nomInicial Nombre del nodo inicial.
 * @param nomFinal Nombre del nodo final.
 */
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
/**
 * @brief Elimina un nodo de la gráfica.
 * @param nom Nombre del nodo a eliminar.
 */
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
/**
 * @brief Elimina una arista entre dos nodos.
 * @param nomInicial Nombre del nodo inicial.
 * @param nomFinal Nombre del nodo final.
 */
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
/**
 * @brief Obtiene el número de nodos en la gráfica.
 * @return Número de nodos.
 */
int Grafica::ObtenerNumNodos() const {
    return numNodos;
}

//*************************************************
/**
 * @brief Obtiene el número de aristas en la gráfica.
 * @return Número de aristas.
 */
int Grafica::ObtenerNumAristas() const {
    return numAristas;
}

//*************************************************
/**
 * @brief Obtiene el grado de un nodo.
 * @param nom Nombre del nodo.
 * @return Grado del nodo.
 * @throw "Nodo inexistente" si el nodo no existe.
 */
int Grafica::ObtenerGrado(char nom) const {
    Nodo *nodoBuscado = BuscarDireccion(nom);
    if (nodoBuscado == NULL) throw "Nodo inexistente";
    return nodoBuscado->grado;
}

//*************************************************
/**
 * @brief Verifica si un nodo existe en la gráfica.
 * @param nom Nombre del nodo.
 * @return true si el nodo existe, false en caso contrario.
 */
bool Grafica::Buscar(char nom) const {
    return BuscarDireccion(nom) != NULL;
}

//*************************************************
/**
 * @brief Verifica si existe una arista entre dos nodos.
 * @param nomInicial Nombre del nodo inicial.
 * @param nomFinal Nombre del nodo final.
 * @return true si la arista existe, false en caso contrario.
 */
bool Grafica::Buscar(char nomInicial, char nomFinal) const {
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if (dirInicial == NULL) return false;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if (dirFinal == NULL) return false;
    return dirInicial->Buscar(dirFinal);
}

//*************************************************
/**
 * @brief Imprime la representación de la gráfica en consola.
 */
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
/**
 * @brief Vacía todas las aristas de un nodo.
 * @param nom Nombre del nodo a vaciar.
 */
void Grafica::Vaciar(char nom) {
    Nodo *porVaciar = BuscarDireccion(nom);
    if (porVaciar == NULL) return;
    numAristas -= porVaciar->Vaciar();
}

//*************************************************
/**
 * @brief Vacía toda la gráfica eliminando todos los nodos y aristas.
 */
void Grafica::Vaciar() {
    while (primero != NULL) Eliminar(primero->nombre);
}

//*************************************************
/**
 * @brief Busca un nodo en la gráfica y opcionalmente devuelve su predecesor.
 * @param nom Nombre del nodo a buscar.
 * @param ant Puntero opcional al nodo anterior.
 * @return Puntero al nodo encontrado o NULL si no existe.
 */
Nodo *Grafica::BuscarDireccion(char nom, Nodo **ant /*=NULL*/) const {
    Nodo *aux = primero;
    if (ant != NULL) *ant = NULL;
    while (aux != NULL && aux->nombre != nom) {
        if (ant != NULL) *ant = aux;
        aux = aux->siguiente;
    }
    return aux;
}


//*********************************************************

/**
 * @brief Verifica si la gráfica es conexa.
 * @return true si la gráfica es conexa, false en caso contrario.
 */
bool Grafica::EsConexa() const {
    std::map<char, bool> visitado;
    if (primero == nullptr) {
        std::cout << "La gráfica es vacía." << std::endl;
        return true;
    }

    DFS(primero, visitado);

    Nodo* nodoActual = primero;
    while (nodoActual != nullptr) {
        if (visitado.find(nodoActual->nombre) == visitado.end()) {
            std::cout << "La gráfica NO es conexa." << std::endl;
            return false;
        }
        nodoActual = nodoActual->siguiente;
    }

    std::cout << "La gráfica es conexa." << std::endl;
    return true;
}

//*********************************************************

/**
 * @brief Verifica si todos los nodos de la gráfica tienen grado par.
 * @return true si todos los nodos tienen grado par, false si hay al menos un nodo con grado impar.
 */
bool Grafica::TieneGradoPar() const {
    Nodo* nodoActual = primero;
    while (nodoActual != nullptr) {
        std::cout << "Nodo " << nodoActual->nombre << " tiene grado: " << nodoActual->grado << std::endl;
        if (nodoActual->grado % 2 != 0) {
            return false;
        }
        nodoActual = nodoActual->siguiente;
    }
    return true;
}

//*********************************************************

/**
 * @brief Realiza un recorrido en profundidad (DFS) en la gráfica.
 * @param nodo Nodo inicial desde donde comienza la búsqueda.
 * @param visitado Mapa que registra los nodos visitados.
 */
void Grafica::DFS(Nodo* nodo, std::map<char, bool>& visitado) const {
    Pila<Nodo*> pila;
    pila.Apilar(nodo);
    visitado[nodo->nombre] = true;

    while (!pila.EstaVacia()) {
        Nodo* nodoActual = pila.ObtenerTope();
        pila.Desapilar();

        Arista* arista = nodoActual->primera;
        while (arista != nullptr) {
            Nodo* adyacente = arista->adyacente;
            if (visitado.find(adyacente->nombre) == visitado.end()) {
                visitado[adyacente->nombre] = true;
                pila.Apilar(adyacente);
            }
            arista = arista->siguiente;
        }
    }
}

//*********************************************************

/**
 * @brief Encuentra y muestra el camino euleriano de la gráfica si existe.
 */
void Grafica::CaminoEuleriano() {
    if (!EsConexa() || !TieneGradoPar()) {
        std::cout << "La gráfica no tiene un camino euleriano." << std::endl;
        return;
    }

    Pila<Nodo*> pila;
    Cola<Nodo*> cola;

    Nodo* v_c = primero;
    pila.Apilar(v_c);
    cola.Encolar(v_c);

    while (!pila.EstaVacia()) {
        v_c = pila.ObtenerTope();

        if (v_c->grado > 0) {
            Arista* arista = v_c->primera;
            Nodo* w = arista->adyacente;

            Eliminar(v_c->nombre, w->nombre);
            std::cout << "Eliminando arista: " << v_c->nombre << " - " << w->nombre << std::endl;

            cola.Encolar(w);
            pila.Apilar(w);

        } else {
            pila.Desapilar();
        }
    }

    std::cout << "Camino Euleriano: ";
    while (!cola.EstaVacia()) {
        std::cout << cola.ConocerPrim()->nombre << " -> ";
        cola.Desencolar();
    }
    while (!pila.EstaVacia()) {
        std::cout << pila.ObtenerTope()->nombre << " -> ";
        pila.Desapilar();
    }
    std::cout << "Fin" << std::endl;
}


#include <iostream>
#include "../Headers/Grafica.hpp"
#include "../Headers/Pila.hpp"

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
    std::map<char, bool> visitado;  // Usamos un map para marcar los nodos visitados
    if (primero == nullptr) {
        std::cout << "La gráfica es vacía." << std::endl;
        return true;
    }

    // Usamos DFS para recorrer la gráfica
    DFS(primero, visitado);

    // Comprobamos si todos los nodos fueron visitados
    Nodo* nodoActual = primero;
    while (nodoActual != nullptr) {
        if (visitado.find(nodoActual->nombre) == visitado.end()) {
            std::cout << "La gráfica NO es conexa." << std::endl;
            return false;  // Si algún nodo no fue visitado, la gráfica no es conexa
        }
        nodoActual = nodoActual->siguiente;
    }

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
void Grafica::DFS(Nodo* nodo, std::map<char, bool>& visitado) const {
    Pila<Nodo*> pila;  // Usamos la Pila proporcionada para hacer DFS
    pila.Apilar(nodo);
    visitado[nodo->nombre] = true;  // Marcamos el nodo como visitado

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


// Función adaptada para encontrar el camino euleriano
void Grafica::CaminoEuleriano() {
    // Verificamos si la gráfica es conexa y si tiene todos los grados pares.
    if (!EsConexa() || !TieneGradoPar()) {
        std::cout << "La gráfica no tiene un camino euleriano." << std::endl;
        return;
    }

    Pila<Nodo*> pila;
    Pila<Nodo*> camino;

    Nodo* v_c = primero;  // Nodo inicial (cualquier vértice)
    pila.Apilar(v_c);

    while (!pila.EstaVacia()) {
        v_c = pila.ObtenerTope();

        if (v_c->grado > 0) {
            Arista* arista = v_c->primera;
            Nodo* w = arista->adyacente;

            // Eliminamos la arista de la gráfica
            Eliminar(v_c->nombre, w->nombre);
            std::cout << "Eliminando arista: " << v_c->nombre << " - " << w->nombre << std::endl;

            pila.Apilar(w);
        } else {
            camino.Apilar(pila.ObtenerTope());
            pila.Desapilar();
        }
    }

    // Ahora imprimimos el camino euleriano
    std::cout << "Camino Euleriano: ";

    while (!camino.EstaVacia()) {
        std::cout << camino.ObtenerTope()->nombre << " -> ";
        camino.Desapilar();
    }

    std::cout << "Fin" << std::endl;
}

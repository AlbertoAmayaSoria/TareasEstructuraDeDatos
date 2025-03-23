#include <iostream>
#include "../Headers/Grafica.hpp"
#include "../Headers/Pila.hpp"
#include "../Headers/Cola.hpp"

//*************************************************
Grafica::Grafica():primero(NULL),ultimo(NULL),numNodos(0),
    numAristas(0){}
//*************************************************
Grafica::Grafica(const Grafica &g):primero(NULL),
    ultimo(NULL),numNodos(0),numAristas(0)
{
    *this = g;
}
//*************************************************
Grafica::~Grafica()
{
    Vaciar();
}
//*************************************************
Grafica & Grafica::operator=(const Grafica &g)
{
    if(this == &g) return *this;
    Vaciar();
    Nodo *nodoVisitado = g.primero;
    while(nodoVisitado != NULL){
        Agregar(nodoVisitado->nombre);
        nodoVisitado = nodoVisitado->siguiente;
    }
    nodoVisitado = g.primero;
    Arista *aristaVisitada;
    while(nodoVisitado != NULL){
        aristaVisitada = nodoVisitado->primera;
        while(aristaVisitada != NULL){
            if(!Buscar(nodoVisitado->nombre,
            aristaVisitada->adyacente->nombre)){

                Agregar(nodoVisitado->nombre,
                aristaVisitada->adyacente->nombre);
            }
            aristaVisitada = aristaVisitada->siguiente;
        }
        nodoVisitado = nodoVisitado->siguiente;
    }
    return *this;
}
//*************************************************
void Grafica::Agregar(char nom)
{
    Nodo * nuevo = new Nodo(nom);
    numNodos == 0 ? primero = nuevo : ultimo->siguiente = nuevo;
    ultimo = nuevo;
    ++numNodos;
}
//*************************************************
void Grafica::Agregar(char nomInicial, char nomFinal)
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return;
    //Agregar el nodo final en la lista del nodo inicial
    dirInicial->Agregar(dirFinal);
    //Agregar el nodo inicial en la lista del nodo final
    dirFinal->Agregar(dirInicial);
    ++numAristas;
}
//*************************************************
void Grafica::Eliminar(char nom)
{
    Nodo *ant, *porBorrar = BuscarDireccion(nom,&ant);
    if(porBorrar == NULL) return;
    numAristas -= porBorrar->Vaciar();
    if(ant == NULL) primero = primero->siguiente;
    else ant->siguiente =porBorrar->siguiente;
    if(primero == NULL) ultimo = NULL;
    delete porBorrar;
    --numNodos;
}
//*************************************************
void Grafica::Eliminar(char nomInicial, char nomFinal)
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return;
    //Eliminar el final de la lista del inicial
    dirInicial->Eliminar(dirFinal);
    //Eliminar el inicial de la lista del final
    dirFinal->Eliminar(dirInicial);
    --numAristas;
}
//*************************************************
int Grafica::ObtenerNumNodos() const
{
    return numNodos;
}

//*************************************************
int Grafica::ObtenerNumAristas() const
{
    return numAristas;
}

//*************************************************
int Grafica::ObtenerGrado(char nom) const
{
    Nodo *nodoBuscado = BuscarDireccion(nom);
    if(nodoBuscado == NULL) throw "Nodo inexistente";
    return nodoBuscado->grado;
}

//*************************************************
bool Grafica::Buscar(char nom) const
{
    return BuscarDireccion(nom) != NULL;
}
//*************************************************
bool Grafica::Buscar(char nomInicial, char nomFinal) const
{
    Nodo *dirInicial = BuscarDireccion(nomInicial);
    if(dirInicial == NULL) return false;
    Nodo *dirFinal = BuscarDireccion(nomFinal);
    if(dirFinal == NULL) return false;

    return dirInicial->Buscar(dirFinal);
}
//*************************************************
void Grafica::Imprimir()const
{
    Nodo *visitado = primero;
    while(visitado != NULL){
        std::cout << visitado->nombre << ": ";
        visitado->Imprimir();
        visitado = visitado->siguiente;
        std::cout << std::endl;
    }
}
//*************************************************
void Grafica::Vaciar(char nom)
{
    Nodo *porVaciar = BuscarDireccion(nom);
    if(porVaciar == NULL) return;
    numAristas -= porVaciar->Vaciar();
}
//*************************************************
void Grafica::Vaciar()
{
    while(primero != NULL) Eliminar(primero->nombre);
}
//*************************************************
Nodo * Grafica::BuscarDireccion(char nom, Nodo **ant /*=NULL*/)const
{
    Nodo *aux = primero;
    if(ant != NULL) *ant = NULL;
    while(aux != NULL && aux->nombre != nom){
        if(ant != NULL) *ant = aux;
        aux = aux->siguiente;
    }
    return aux;
}

//*************************************************
/*void RecorrerNodos(const Grafica& g) {
    Nodo* actual = g.primero;  // Comienza desde el primer nodo

    // Recorre la lista hasta llegar al final
    while (actual != nullptr) {
        std::cout << "Nodo: " << actual->nombre << std::endl;  // Imprimir el nombre del nodo
        actual = actual->siguiente;  // Avanzamos al siguiente nodo
    }
}*/

//*************************************************

// Verificar si la gráfica es conexa (usando DFS)
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
            return false;  // Si algún nodo no fue visitado, la gráfica no es conexa
        }
    }

    delete[] visitado;
    return true;
}

//**************************************************

// Verificar si todos los nodos tienen grado par
bool Grafica::TieneGradoPar() const {
    Nodo* nodoActual = primero;
    while (nodoActual != nullptr) {
        if (nodoActual->grado % 2 != 0) {
            return false;  // Si encontramos un nodo con grado impar, retornamos false
        }
        nodoActual = nodoActual->siguiente;
    }
    return true;  // Todos los nodos tienen grado par
}

//***************************************************

// DFS auxiliar para verificar si la gráfica es conexa
void Grafica::DFS(Nodo* inicio, bool *visitado) const {
    Pila<Nodo*> pila;  // Usamos la Pila proporcionada para hacer DFS
    pila.Apilar(inicio);

    while (!pila.EstaVacia()) {
        Nodo* nodoActual = pila.ObtenerTope();
        pila.Desapilar();

        if (!visitado[nodoActual->nombre - '0']) {
            visitado[nodoActual->nombre - '0'] = true;
            Arista* arista = nodoActual->primera;
            while (arista != nullptr) {
                Nodo* adyacente = arista->adyacente;
                if (!visitado[adyacente->nombre - '0']) {
                    pila.Apilar(adyacente);
                }
                arista = arista->siguiente;
            }
        }
    }
}

//****************************************************************

void Grafica::CaminoEuleriano() {
    if (!EsConexa() || !TieneGradoPar()) {
        std::cout << "La gráfica no tiene un camino euleriano." << std::endl;
        return;
    }
    
    Cola<Nodo*> cola;
    Pila<Nodo*> pila;
    Nodo* v_c = primero;
    Nodo* v_p = v_c;
    
    cola.Encolar(v_c);
    pila.Apilar(v_p);
    
    while (v_c->grado > 0 || v_p->grado > 0) {
        if (v_c->grado > 0) {
            Arista* arista = v_c->primera;
            Nodo* w = arista->adyacente;
            
            // Verificar si eliminar {v_c, w} desconectaría el grafo
            if (ObtenerGrado(w) != 1 || v_c->grado == 1) {
                Eliminar(v_c->nombre, w->nombre);
                cola.Encolar(w);
                v_c = w;
            }
        } else if (v_p->grado == 1) {
            Arista* arista = v_p->primera;
            Nodo* k = arista->adyacente;
            
            Eliminar(v_p->nombre, k->nombre);
            pila.Apilar(k);
            v_p = k;
        }
    }
    
    // Imprimir el camino euleriano
    std::cout << "Camino Euleriano: ";
    while (!cola.EstaVacia()) {
        std::cout << cola.ObtenerFrente()->nombre << " -> ";
        cola.Desencolar();
    }
    while (!pila.EstaVacia()) {
        std::cout << pila.ObtenerTope()->nombre << " -> ";
        pila.Desapilar();
    }
    std::cout << "Fin" << std::endl;
}



/*
// Función DFS (Depth First Search)
void Grafica::DFS(Nodo* nodo, bool* visitado) const {
    Pila<Nodo*> pila;
    pila.Apilar(nodo);

    while (!pila.EstaVacia()) {
        Nodo* actual = pila.ObtenerTope();
        pila.Desapilar();

        // Si no se ha visitado este nodo
        if (!visitado[actual->nombre - '1']) {
            visitado[actual->nombre - '1'] = true;

            // Recorremos las aristas del nodo
            Arista* arista = actual->primera;
            while (arista != nullptr) {
                Nodo* adyacente = arista->adyacente;
                if (!visitado[adyacente->nombre - '1']) {
                    pila.Apilar(adyacente);  // Apilamos el nodo adyacente no visitado
                }
                arista = arista->siguiente;
            }
        }
    }
}

// Función BFS (Breadth First Search)
void Grafica::BFS(Nodo* nodo, bool* visitado) const {
    Cola<Nodo*> cola;
    cola.Encolar(nodo);
    visitado[nodo->nombre - '1'] = true;

    while (!cola.EstaVacia()) {
        Nodo* actual = cola.ConocerPrim();
        cola.Desencolar();

        // Recorremos las aristas del nodo
        Arista* arista = actual->primera;
        while (arista != nullptr) {
            Nodo* adyacente = arista->adyacente;
            if (!visitado[adyacente->nombre - '1']) {
                visitado[adyacente->nombre - '1'] = true;
                cola.Encolar(adyacente); // Encolamos el nodo adyacente no visitado
            }
            arista = arista->siguiente;
        }
    }
}*/

#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

#include "Nodo.hpp"
#include "Pila.hpp"  // Para usar Pila
#include "Cola.hpp"  // Para usar Cola

class Grafica {
public:
    Grafica();
    Grafica(const Grafica &g);
    ~Grafica();
    Grafica & operator=(const Grafica &g);

    // Agregar nodo
    void Agregar(char nom);
    // Agregar arista
    void Agregar(char nomInicial, char nomFinal);

    // Eliminar nodo
    void Eliminar(char nom);
    // Eliminar arista
    void Eliminar(char nomInicial, char nomFinal);

    // Obtener el n�mero de nodos
    int ObtenerNumNodos() const;
    // Obtener el n�mero de aristas
    int ObtenerNumAristas() const;
    // Obtener el grado de un nodo
    int ObtenerGrado(char nom) const;

    // Verificar existencia de nodo
    bool Buscar(char nom) const;
    // Verificar existencia de arista
    bool Buscar(char nomInicial, char nomFinal) const;

    // Imprimir la gr�fica
    void Imprimir() const;

    // Vaciar un nodo
    void Vaciar(char nom);
    // Vaciar toda la gr�fica
    void Vaciar();

    // Funciones de Fleury
    void CaminoEuleriano();
    bool EsConexa() const;
    bool TieneGradoPar() const;
    void DFS(Nodo* inicio, bool *visitado) const;

    // Funciones de b�squeda con contenedores gen�ricos
    template <typename T>
    void DFS(Nodo* nodo, bool* visitado, T& estructura) const;  // DFS usando estructura gen�rica

    /*template <typename T>
    void BFS(Nodo* nodo, bool* visitado, T& estructura) const;  // BFS usando estructura gen�rica
    */

private:
    Nodo *primero, *ultimo;
    int numNodos, numAristas;

    Nodo *BuscarDireccion(char nom, Nodo **ant = NULL) const;
};

#endif // GRAFICA_HPP_INCLUDED


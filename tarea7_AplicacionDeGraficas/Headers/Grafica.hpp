#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

#include "Nodo.hpp"
#include "Pila.hpp"  // Para usar Pila
#include "Cola.hpp"  // Para usar Cola

class Grafica{
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

    // M�todos para la verificaci�n de conectividad y euleriano
    bool EsConexa() const;  // Verificar si la gr�fica es conexa
    bool TieneGradoPar() const;  // Verificar si todos los nodos tienen grado par
    void CaminoEuleriano();  // Buscar el camino euleriano

private:
    Nodo *primero, *ultimo;
    int numNodos, numAristas;

    Nodo *BuscarDireccion(char nom, Nodo **ant = NULL) const;
    void DFS(Nodo* nodo, bool* visitado) const;  // DFS
    void BFS(Nodo* nodo, bool* visitado) const;  // BFS
};

#endif // GRAFICA_HPP_INCLUDED


/**
 * @file Grafica.hpp
 * @brief Definici�n de la clase Grafica para representar un grafo.
 */

#ifndef GRAFICA_HPP_INCLUDED
#define GRAFICA_HPP_INCLUDED

#include "Nodo.hpp"
#include <map>

/**
 * @class Grafica
 * @brief Representa una estructura de datos para un grafo no dirigido.
 */
class Grafica {
public:
    /**
     * @brief Constructor por defecto.
     */
    Grafica();
    
    /**
     * @brief Constructor de copia.
     * @param g Referencia al objeto Grafica a copiar.
     */
    Grafica(const Grafica &g);
    
    /**
     * @brief Destructor de la gr�fica.
     */
    ~Grafica();
    
    /**
     * @brief Sobrecarga del operador de asignaci�n.
     * @param g Referencia al objeto Grafica a asignar.
     * @return Referencia a la instancia actual.
     */
    Grafica & operator=(const Grafica &g);

    /**
     * @brief Agrega un nodo a la gr�fica.
     * @param nom Nombre del nodo a agregar.
     */
    void Agregar(char nom);
    
    /**
     * @brief Agrega una arista entre dos nodos existentes.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     */
    void Agregar(char nomInicial, char nomFinal);

    /**
     * @brief Elimina un nodo de la gr�fica.
     * @param nom Nombre del nodo a eliminar.
     */
    void Eliminar(char nom);
    
    /**
     * @brief Elimina una arista entre dos nodos.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     */
    void Eliminar(char nomInicial, char nomFinal);

    /**
     * @brief Obtiene el n�mero de nodos en la gr�fica.
     * @return Cantidad de nodos en la gr�fica.
     */
    int ObtenerNumNodos() const;
    
    /**
     * @brief Obtiene el n�mero de aristas en la gr�fica.
     * @return Cantidad de aristas en la gr�fica.
     */
    int ObtenerNumAristas() const;
    
    /**
     * @brief Obtiene el grado de un nodo.
     * @param nom Nombre del nodo.
     * @return Grado del nodo.
     * @throws Excepci�n si el nodo no existe.
     */
    int ObtenerGrado(char nom) const;

    /**
     * @brief Verifica si un nodo existe en la gr�fica.
     * @param nom Nombre del nodo.
     * @return true si el nodo existe, false en caso contrario.
     */
    bool Buscar(char nom) const;
    
    /**
     * @brief Verifica si una arista existe entre dos nodos.
     * @param nomInicial Nombre del nodo inicial.
     * @param nomFinal Nombre del nodo final.
     * @return true si la arista existe, false en caso contrario.
     */
    bool Buscar(char nomInicial, char nomFinal) const;

    /**
     * @brief Imprime la representaci�n de la gr�fica.
     */
    void Imprimir() const;

    /**
     * @brief Vac�a todas las aristas de un nodo.
     * @param nom Nombre del nodo a vaciar.
     */
    void Vaciar(char nom);
    
    /**
     * @brief Vac�a completamente la gr�fica, eliminando todos los nodos y aristas.
     */
    void Vaciar();

    /**
     * @brief Verifica si la gr�fica es conexa.
     * @return true si la gr�fica es conexa, false en caso contrario.
     */
    bool EsConexa() const;
    
    /**
     * @brief Verifica si todos los nodos tienen grado par.
     * @return true si todos los nodos tienen grado par, false en caso contrario.
     */
    bool TieneGradoPar() const;

    /**
     * @brief Realiza una b�squeda en profundidad (DFS) en la gr�fica.
     * @param nodo Nodo inicial para la b�squeda.
     * @param visitado Mapa que registra los nodos visitados.
     */
    void DFS(Nodo* nodo, std::map<char, bool>& visitado) const;

    /**
     * @brief Encuentra un camino euleriano en la gr�fica, si existe.
     */
    void CaminoEuleriano();

private:
    Nodo *primero, *ultimo; ///< Punteros al primer y �ltimo nodo de la gr�fica.
    int numNodos, numAristas; ///< Contadores de nodos y aristas.

    /**
     * @brief Busca la direcci�n de un nodo en la gr�fica.
     * @param nom Nombre del nodo a buscar.
     * @param ant Puntero al nodo anterior (opcional).
     * @return Puntero al nodo encontrado o nullptr si no existe.
     */
    Nodo *BuscarDireccion(char nom, Nodo **ant = NULL) const;
};

#endif // GRAFICA_HPP_INCLUDED


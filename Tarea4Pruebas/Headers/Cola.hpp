#ifndef COLA_HPP_INCLUDED
#define COLA_HPP_INCLUDED

/**
 * @brief Clase Cola implementada como una cola enlazada circular.
 * @tparam Tipo Tipo de dato almacenado en la cola (por defecto, int).
 */
template <typename Tipo = int>
class Cola {
public:
    /**
     * @brief Constructor por defecto. Inicializa la cola como vacía.
     */
    Cola();
    
    /**
     * @brief Constructor de copia. Copia los elementos de otra cola.
     * @param c Cola a copiar.
     */
    Cola(const Cola<Tipo>& c);
    
    /**
     * @brief Destructor. Libera la memoria ocupada por la cola.
     */
    ~Cola();
    
    /**
     * @brief Operador de asignación para copiar una cola en otra.
     * @param c Cola a copiar.
     * @return Referencia a la cola actual con los elementos copiados.
     */
    Cola<Tipo>& operator=(const Cola<Tipo>& c);

    /**
     * @brief Agrega un elemento a la cola.
     * @param valor Valor a agregar.
     */
    void Encolar(Tipo valor);
    
    /**
     * @brief Elimina el primer elemento de la cola.
     * @throws Excepción si la cola está vacía.
     */
    void Desencolar();
    
    /**
     * @brief Verifica si la cola está vacía.
     * @return true si la cola está vacía, false en caso contrario.
     */
    bool EstaVacia() const;
    
    /**
     * @brief Elimina todos los elementos de la cola.
     */
    void Vaciar();
    
    /**
     * @brief Devuelve la cantidad de elementos en la cola.
     * @return Número de elementos en la cola.
     */
    int ObtenerCantElem() const;
    
    /**
     * @brief Imprime los elementos de la cola en orden.
     */
    void Imprimir() const;
    
    /**
     * @brief Devuelve el primer elemento de la cola sin eliminarlo.
     * @return Valor del primer elemento.
     * @throws Excepción si la cola está vacía.
     */
    Tipo ConocerPrim() const;
    
    /**
     * @brief Devuelve el último elemento de la cola sin eliminarlo.
     * @return Valor del último elemento.
     * @throws Excepción si la cola está vacía.
     */
    Tipo ConocerUlt() const;

private:
    int numElem; ///< Número de elementos en la cola.
    
    /**
     * @brief Estructura que representa un nodo en la cola.
     */
    struct Elemento {
        Tipo valor; ///< Valor almacenado en el nodo.
        Elemento* siguiente; ///< Puntero al siguiente nodo.
    } *ultimo; ///< Puntero al último nodo en la cola.
};

#include "../Templates/Cola.tpp"

#endif // COLA_HPP_INCLUDED

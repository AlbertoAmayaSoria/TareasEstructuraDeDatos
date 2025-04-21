#ifndef ARBOLAVL_H_INCLUDED
#define ARBOLAVL_H_INCLUDED

/**
 * @class ArbolAVL
 * @brief Clase genérica para representar un árbol AVL.
 *
 * @tparam Type Tipo de dato almacenado en los nodos del árbol.
 */
template<typename Type>
class ArbolAVL {
public:
    /**
     * @brief Constructor por defecto. Inicializa un árbol vacío.
     */
    explicit ArbolAVL();

    /**
     * @brief Constructor de copia. Crea un nuevo árbol idéntico a otro.
     * @param AVL Árbol a copiar.
     */
    ArbolAVL(const ArbolAVL &AVL);

    /**
     * @brief Destructor. Libera la memoria de todos los nodos.
     */
    ~ArbolAVL();

    /**
     * @brief Operador de asignación.
     * @param AVL Árbol cuyo contenido se asignará.
     * @return Referencia al árbol asignado.
     */
    ArbolAVL & operator=(const ArbolAVL &AVL);

    /**
     * @brief Inserta un nuevo valor en el árbol.
     * @param valor Valor a insertar.
     */
    void Agregar(Type valor);

    /**
     * @brief Elimina un valor del árbol si existe.
     * @param valor Valor a eliminar.
     */
    void Eliminar(Type valor);

    /**
     * @brief Busca un valor en el árbol.
     * @param valor Valor a buscar.
     * @return true si el valor existe, false en caso contrario.
     */
    bool Buscar(Type valor) const;

    /**
     * @brief Obtiene el número total de nodos en el árbol.
     * @return Número de nodos.
     */
    int NumNodos() const;

    /**
     * @brief Vacía el árbol, eliminando todos los nodos.
     */
    void Vaciar();

    /**
     * @brief Calcula la altura del árbol.
     * @return Altura desde la raíz hasta la hoja más profunda.
     */
    int AlturaArbol() const;

    /**
     * @brief Obtiene el valor máximo almacenado en el árbol.
     * @return Valor máximo.
     * @note Requiere al menos un nodo en el árbol.
     */
    Type ObtenerMayor() const;

    /**
     * @brief Obtiene el valor mínimo almacenado en el árbol.
     * @return Valor mínimo.
     * @note Requiere al menos un nodo en el árbol.
     */
    Type ObtenerMenor() const;

    /**
     * @brief Imprime los valores del árbol en orden ascendente.
     */
    void ImprimirAsc() const;

    /**
     * @brief Imprime los valores del árbol en orden descendente.
     */
    void ImprimirDec() const;

    /**
     * @brief Imprime los valores del árbol por niveles (recorrido por amplitud).
     */
    void ImprimirNiveles() const;

private:
    int numNodos;  /**< @brief Conteo interno de nodos. */

    /**
     * @struct Nodo
     * @brief Estructura interna que representa un nodo del árbol.
     */
    struct Nodo {
        Type valor;        /**< Valor almacenado en el nodo. */
        Nodo *hijoIzq;     /**< Puntero al hijo izquierdo. */
        Nodo *hijoDer;     /**< Puntero al hijo derecho. */

        /**
         * @brief Constructor de nodo.
         * @param v Valor a almacenar.
         * @param hijIzq Puntero inicial al hijo izquierdo.
         * @param hijDer Puntero inicial al hijo derecho.
         */
        Nodo(Type v, Nodo *hijIzq = nullptr, Nodo *hijDer = nullptr)
            : valor(v), hijoIzq(hijIzq), hijoDer(hijDer) {}
    } *raiz;   /**< @brief Puntero a la raíz del árbol. */

    /**
     * @brief Inserta un valor en el subárbol dado.
     * @param valor Valor a insertar.
     * @param subraiz Puntero al subárbol.
     */
    void Agregar(Type valor, Nodo *&subraiz);

    /**
     * @brief Elimina un valor en el subárbol dado.
     * @param valor Valor a eliminar.
     * @param subraiz Puntero al subárbol.
     */
    void Eliminar(Type valor, Nodo *&subraiz);

    /**
     * @brief Calcula la altura de un subárbol.
     * @param subraiz Raíz del subárbol.
     * @return Altura desde subraiz.
     */
    int AlturaArbol(Nodo* subraiz) const;

    /**
     * @brief Imprime valores en orden ascendente en un subárbol.
     * @param subraiz Raíz del subárbol.
     */
    void ImprimirAsc(Nodo* subraiz) const;

    /**
     * @brief Imprime valores en orden descendente en un subárbol.
     * @param subraiz Raíz del subárbol.
     */
    void ImprimirDec(Nodo* subraiz) const;

    /**
     * @brief Libera todos los nodos del subárbol con el valor dado.
     * @param valor Valor hasta donde podar.
     */
    void Podar(Type valor);

    /**
     * @brief Libera todos los nodos de un subárbol.
     * @param subraiz Raíz del subárbol.
     */
    void Podar(Nodo* subraiz);

    /**
     * @brief Copia recursivamente un subárbol.
     * @param subraiz Raíz del subárbol a copiar.
     * @return Nueva raíz copiada.
     */
    Nodo* CopiarArbol(Nodo* subraiz);

    /**
     * @brief Busca la dirección de un valor en el subárbol.
     * @param valor Valor buscado.
     * @param subraiz Subárbol donde buscar.
     * @return Referencia al puntero donde está o debería estar el nodo.
     */
    Nodo *& BuscarDir(Type valor, Nodo *&subraiz) const;

    /**
     * @brief Encuentra el sucesor in-order de un nodo.
     * @param subraiz Nodo cuyo sucesor se busca.
     * @return Puntero al nodo sucesor.
     */
    Nodo* BuscarSucesor(Nodo* subraiz) const;

    /**
     * @brief Balancea un subárbol mediante rotaciones.
     * @param subraiz Raíz del subárbol.
     * @return Referencia a la nueva raíz balanceada.
     */
    Nodo *& Balancear(Nodo *&subraiz);

    /**
     * @brief Calcula el factor de balance de un nodo.
     * @param subraiz Nodo a evaluar.
     * @return Factor de balance (altura-hijoIzq - altura-hijoDer).
     */
    int FactorBalance(Nodo *subraiz);

    /**
     * @brief Rotación simple a la derecha (Right Single).
     * @param x Subárbol a rotar.
     * @return Nueva raíz tras la rotación.
     */
    Nodo *& RSD(Nodo *&x);

    /**
     * @brief Rotación simple a la izquierda (Left Single).
     * @param x Subárbol a rotar.
     * @return Nueva raíz tras la rotación.
     */
    Nodo *& RSI(Nodo *&x);

    /**
     * @brief Rotación doble derecha-izquierda (Right-Left Double).
     * @param x Subárbol a rotar.
     * @return Nueva raíz tras la rotación.
     */
    Nodo *& RDI(Nodo *&x);

    /**
     * @brief Rotación doble izquierda-derecha (Left-Right Double).
     * @param x Subárbol a rotar.
     * @return Nueva raíz tras la rotación.
     */
    Nodo *& RDD(Nodo *&x);
};

#include "../Templates/ArbolAVL.tpp"

#endif // ARBOLAVL_H_INCLUDED


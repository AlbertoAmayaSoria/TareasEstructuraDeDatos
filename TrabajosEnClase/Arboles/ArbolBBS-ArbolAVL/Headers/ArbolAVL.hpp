#ifndef ARBOLAVL_H_INCLUDED
#define ARBOLAVL_H_INCLUDED

template<typename Type>
class ArbolAVL{
public:
    
    // Constructor
    explicit ArbolAVL();
    // Constructor de copias
    ArbolAVL(const ArbolAVL &AVL);
    // Destructor
    ~ArbolAVL();
    // Operador =
    ArbolAVL & operator=(const ArbolAVL &AVL);
    
    void Agregar(Type valor);

    void Eliminar(Type valor);

    bool Buscar(Type valor) const;

    int NumNodos() const;

    void Vaciar();

    int AlturaArbol() const;

    Type ObtenerMayor() const; //no necesario
    Type ObtenerMenor() const; //no necesario
    //int AlturaArbol() const;

    void ImprimirAsc() const;
    void ImprimirDec() const;
    void ImprimirNiveles() const;

    //void Vaciar();

    //void ImprimirNiveles() const;

private:
    int numNodos;

    struct Nodo{
        Type valor;
        Nodo *hijoIzq, *hijoDer;
        Nodo(Type v, Nodo *hijIzq = nullptr, Nodo *hijDer = nullptr): valor(v), hijoIzq(hijIzq), hijoDer(hijDer){}
    } *raiz;

    void Agregar(Type valor, Nodo *&subraiz);

    void Eliminar(Type valor, Nodo *&subraiz);

    int AlturaArbol(Nodo* subraiz) const;

    void ImprimirAsc(Nodo* subraiz) const;

    void ImprimirDec(Nodo* subraiz) const;

    void Podar(Type valor);
    void Podar(Nodo* subraiz);

    // Función auxiliar para copiar el árbol recursivamente
    Nodo* CopiarArbol(Nodo* subraiz);

    Nodo *& BuscarDir(Type valor, Nodo *&subraiz) const;

    // Función auxiliar para encontrar el sucesor in-order
    Nodo* BuscarSucesor(Nodo* subraiz) const;

    Nodo *&Balancear(Nodo *&subraiz);

    int FactorBalance(Nodo *subraiz);

    Nodo *&RSI(Nodo *&x);

    Nodo *&RSD(Nodo *&x);
    
    Nodo *&RDI(Nodo *&x);
    
    Nodo *&RDD(Nodo *&x);

    //int FactrorBalance(Nodo *subraiz);
};

#include "../Templates/ArbolAVL.tpp"

#endif // ArbolAVL_HPP_INCLUDED

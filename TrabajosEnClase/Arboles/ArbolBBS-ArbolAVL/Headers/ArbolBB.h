#ifndef ARBOLBB_H_INCLUDED
#define ARBOLBB_H_INCLUDED

template<typename Type>
class ArbolBB{
public:

    // Constructor
    explicit ArbolBB();
    // Constructor de Copia
    ArbolBB(const ArbolBB &ABB);
    // Destructor
    ~ArbolBB();
    // Operador =
    ArbolBB & operator=(const ArbolBB &ab);
    // Métodos públicos
    void Agregar(Type valor);
    void Eliminar(Type valor);

    bool Buscar(Type valor)const;
    
    int NumeroNodos();
    Type ObtenerMayor();
    Type ObtenerMenor();
    
    int AlturaArbol() const;

    void Podar(Type valor);
    void Vaciar();

    void ImprimirAsc() const;
    void ImprimirDec() const;
    void ImprimirNiveles() const;

private:
    int numNodos;

    struct Nodo {
        Type valor;
        Nodo *hijoIzq, *hijoDer;
        Nodo(Type v, Nodo *hI = nullptr, Nodo* hD = nullptr): valor(v), hijoIzq(hI), hijoDer(hD) {}
    } *raiz;

    void Agregar(Type valor, Nodo *&subraiz);
    void Eliminar(Type valor, Nodo *&subraiz);
    void ImprimirAsc(Nodo *subraiz) const;
    Nodo *& BuscarDir(Type valor, Nodo *&subraiz) const;
    void Podar(Nodo *&subraiz);
    void ImprimirDec(Nodo *subraiz) const;

    int AlturaArbol(Nodo* subraiz) const;

    // Función auxiliar para copiar un árbol recursivamente
    Nodo* CopiarArbol(Nodo* subraiz);

    // Función auxiliar para encontrar el sucesor in-order
    Nodo* BuscarSucesor(Nodo* subraiz) const;


};

#include "../Templates/ArbolBB.tpp"

#endif // ARBOLBB_H_INCLUDED


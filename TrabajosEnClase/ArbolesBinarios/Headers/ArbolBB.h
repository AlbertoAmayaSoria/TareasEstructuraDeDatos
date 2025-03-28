#ifndef ARBOLBB_H_INCLUDED
#define ARBOLBB_H_INCLUDED


template<typename Type>
class ArbolBB{
public:

    //Constructor
    explicit ArbolBB();
    //Constructor de Copias
    ArbolBB(const ArbolBB &ABB);
    //Destructor
    ~ArbolBB();
    //Operador =
    ArbolBB & operator=(const ArbolBB &ab);
    //Metodos publicos
    void Agregar(Type valor);

    void ImprimirAsc() const;

    void Podar(Type valor);

    void ImprimirDec() const;

    void Vaciar();

    void ImprimirNiveles() const;

private:
    int numNodos;

    struct Nodo{
      Type valor;
      Nodo *hijoIzq, *hijoDer;
      Nodo(Type v, Nodo *hI = nullptr, Nodo* hD = nullptr): valor(v), hijoIzq(hI), hijoDer(hD){}
    } *raiz;

    void Agregar(Type valor, Nodo *&subraiz);

    void ImprimirAsc(Nodo *subraiz) const;

    Nodo *& BuscarDir(Type valor, Nodo *&subraiz) const;

    void Podar(Nodo *&subraiz);

    void ImprimirDec(Nodo *subraiz) const;




};

#include "../Templates/ArbolBB.tpp"

#endif // ARBOLBB_H_INCLUDED

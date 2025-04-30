#ifndef ARBOLB_HPP_INCLUDED
#define ARBOLB_HPP_INCLUDED

<<<<<<< HEAD
template <typename Type, int grado = 5>
class ArbolB {
=======
template<typename T, int grado=5>
class ArbolB{
private:

    struct Nodo{
        T clave[grado];
        Nodo* hijo[grado+1];
        int cuenta;//cuantas claves hay
        bool esHoja

        Nodo(){
            cuenta=0;
            esHoja=true;
            for (int i=0; i< grado + 1;++1)
                hijo[i]=NULL;
        }
    };
    Nodo* raiz;
    int totalClaves;

    //metodos auxiliares
    void InsertarEnNodo(Nodo*& nodo, T clave);
    void ImprimirAscedente(Nodo* nodo) const;
    void Liberar (Nodo* nodo);

public:
    ArbolB();
    ~ArbolB();

    void Agregar(T clave);
    void ImprimirAscedente() const;
    int NumClaves() const;
    void Vaciar();
};





/****

>>>>>>> a09ac4f1d9b5d9a73eb2a1661614b3c4575ae0e2
public:

    explicit ArbolB(); // Constructor por defecto
    
    ArbolB(const ArbolB &c); // Constrctor de copia

    ~ArbolB(); // Destructor

    ArbolB& operator=(const ArbolB &c); // Operador asignación

   void Agregar(Type valor); // Agrega un nuevo elemento

    void Eliminar(Type valor); // Elimina el frente (raíz)

    void BuscarElem(); // Busca un elemento en el arbol

    int CantElem() const; // Devuelve la cantidad de elementos actuales

    void Vaciar(); // Vacia el arbol

    // Imprimir
    void ImprimirAsc() const;

    void ImprimirDes() const;

    void ImprimirNiveles() const;


private:

<<<<<<< HEAD
     


=======
>>>>>>> a09ac4f1d9b5d9a73eb2a1661614b3c4575ae0e2
};

//#include 

<<<<<<< HEAD
#endif // ARBOLB_HPP_INCLUDED
=======
#endif // !ARBOLB_HPP_INCLUDED

*/

>>>>>>> a09ac4f1d9b5d9a73eb2a1661614b3c4575ae0e2

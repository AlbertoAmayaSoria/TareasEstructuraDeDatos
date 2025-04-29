#ifndef ARBOLB_HPP_INCLUDED
#define ARBOLB_HPP_INCLUDED

template <typename Type>
class ArbolB {
public:

    explicit ArbolB(); // Constructor por defecto
    
    ArbolB(const ArbolB &c); // Constrctor de copia

    ~ArbolB(); // Destructor

    ArbolB& operator=(const Arbol &c); // Operador asignación

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

    


}

//#include 

#endif // !ARBOLB_HPP_INCLUDED
#define ARBOLB_HPP_INCLUDED

template <typename Type>
class ArbolB {
public:

    explicit ArbolB(); // Constructor por defecto
    
    ArbolB(const ArbolB &c); // Constrctor de copia

    ~ArbolB(); // Destructor

    ArbolB& operator=(const Arbol &c); // Operador asignación

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

    


}

//#include 

#ifndef ARBOLB_HPP_INCLUDED
#define ARBOLB_HPP_INCLUDED

template <typename Type, int grado>
class ArbolB {
public:
    explicit ArbolB(); // Constructor por defecto
    ArbolB(const ArbolB &c); // Constructor de copia
    ~ArbolB(); // Destructor
    ArbolB& operator=(const ArbolB &c); // Operador asignación

    void Agregar(Type valor); // Agrega un nuevo elemento
    void Eliminar(Type valor); // Elimina el primer elemento con este valor

    bool Buscar(Type valor) const; // Busca un elemento en el árbol
    int CantElem() const; // Devuelve la cantidad de elementos actuales

    void Vaciar(); // Vacía el árbol

    // Métodos de impresión
    void ImprimirAsc() const;
    void ImprimirDes() const;
    void ImprimirNiveles() const;

private:
    int cantElem;

    struct Nodo {
        int elemNodo;
        Type claves[grado];
        Nodo* hijo[grado + 1];
        
        Nodo() : elemNodo(0) {
            for(int i = 0; i <= grado; ++i) {
                hijo[i] = nullptr;
            }
        }
    } *raiz;

    // Métodos auxiliares privados
    Nodo* CopiarArbol(Nodo* subraiz);
    void Agregar(Type valor, Nodo* subraiz);
    bool EsHoja(Nodo* nodo) const;
    void dividirNodo(Nodo* padre, int indiceHijo);
    void Vaciar(Nodo* nodo);
    
    // Métodos para búsqueda
    bool Buscar(Type valor, Nodo* subraiz) const;
    
    // Métodos para impresión
    void ImprimirAsc(Nodo* nodo) const;
    void ImprimirDes(Nodo* nodo) const;
    
    // Métodos para eliminación
    void Eliminar(Type valor, Nodo* subraiz);
    void EliminarDeHoja(Nodo* nodo, int indice);
    void EliminarDeNodoInterno(Nodo* nodo, int indice);
    void ManejarUnderflow(Nodo* padre, int indiceHijo);
    void PrestarseDeHermanoIzq(Nodo* padre, int indiceHijo);
    void PrestarseDeHermanoDer(Nodo* padre, int indiceHijo);
    void FusionarHijos(Nodo* padre, int indiceHijo);
    Type ObtenerPredecesor(Nodo* subraiz);
    Type ObtenerSucesor(Nodo* subraiz);
    
    // Métodos auxiliares adicionales para eliminación
    Nodo* EncontrarPadre(Nodo* actual, Nodo* padre, Nodo* buscado);
    int ObtenerIndiceHijo(Nodo* padre, Nodo* hijo);
};

#include "../Templates/ArbolB.tpp"

#endif // ARBOLB_HPP_INCLUDED

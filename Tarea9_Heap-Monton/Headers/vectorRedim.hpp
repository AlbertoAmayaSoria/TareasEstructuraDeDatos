#ifndef VECTORREDIM_HPP
#define VECTORREDIM_HPP

#include <stdexcept>  // Para manejar excepciones

template <typename Type>
class vectorRedim {
public:
    // Constructor y destructor
    vectorRedim();
    ~vectorRedim();

    // Operaciones principales
    void insertar(const Type& valor);
    void eliminar(const Type& valor); // sin implementar

    Type& operator[](size_t indice);
    const Type& operator[](size_t indice) const;
    int tamano() const;
    int capacidad() const;
    bool vacio() const;

private:
    // Atributos internos
    Type* datos;
    int tamanoActual;
    int capacidadActual;

    // Métodos internos
    void redimensionar();
};

#include "../Templates/vectorRedim.tpp"  // Incluir la implementación de los métodos

#endif // VECTORREDIM_HPP


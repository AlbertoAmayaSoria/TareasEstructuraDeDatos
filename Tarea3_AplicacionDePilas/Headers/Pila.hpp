#ifndef PILA_HPP_INCLUDED
#define PILA_HPP_INCLUDED


/**
 * Contenedor tipo LIFO de datos doble
 * \tparam Tipo Tipo de dato
 */
template <typename Tipo = int>
class Pila{
public:
    /** \brief Constructor de la Pila. Genera una pila vac&iacute;a
     */
     Pila(); //dinamica-----------------------------------------------------------------------------

    /** \brief Constructor de copias de la pilaa. Genera una pila nueva con las medidas actuales
     */
     Pila(const Pila<Tipo>& p);

     /** \brief Destructor. Libera memoria en la pila.
     */
    ~Pila();

    /** \brief Operador de asignacion sobrecargado para copiar una pila de forma segura.
     */
    Pila<Tipo>& operator=(const Pila<Tipo>& p);

    /** \brief Permite agregar un elemento a la pila
     *
     * \param valor Valor a agregar
     * \return Ninguno
     * \exception const char * Cuando se intenta agregar en una pila llena
     */
    void Apilar(Tipo valor);

    /** \brief Permite eliminar un elemento de la pila
     *
     * \return Ninguno
     * \exception char * Cuando se intenta eliminar de una pila vac&iacute;a
     */
    void Desapilar();

    /** \brief Obtiene el elemento que se encuentra en el tope de la pila
     *
     * \return El valor del tope
     * \exception char * Cuando se intenta obtener el valor del tope de una pila vac&iacute;a
     */
    Tipo ObtenerTope() const;

    /** \brief Indica si la pila est&aacute; vac&iacute;a
     *
     * \return true si la pila est&aacute; vac&iacute;a, false en caso contrario
     */
    bool EstaVacia() const;


    /** \brief Vac&iacute;a la pila
     *
     * \return Ninguno
     */
    void Vaciar();

    /** \brief Indica el n&uacute;mero de elementos que tiene la pila
     *
     * \return N&uacute;mero de elementos en la pila
     */
    int ObtenerCantElem() const;

    // Para pruebas
    /** \brief Imprime los elementos de la pila del fondo hasta el tope
     *
     * \return Ninguno
     */
    void Imprimir() const;

    /** \brief Indica la capacidad actual de la pila
     *
     * \return cap capacidad de la pila
     */
    int ObtenerCap() const;

private:
    int numElem;

    struct Elemento{
        Tipo valor;
        Elemento *siguiente;
    } * tope;




    /** \brief Redimensiona la pila para duplicar su capacidad si llega al m&aacute;ximo
     *
     * \return Ninguno
     */
    void Redim();
};
#include "../Templates/Pila.tpp"
#endif // PILA_HPP_INCLUDED

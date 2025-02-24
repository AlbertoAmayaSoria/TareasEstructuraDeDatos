#ifndef CAPTURA_SEGURA_HPP
#define CAPTURA_SEGURA_HPP

#include <iostream>
#include <limits>
#include <algorithm>
#include <type_traits>


template <typename N = int, typename T = std::string>
class CapturaSegura
{
//static_assert(std::is_arithmetic_v<N>, "N debe ser un numero");
static_assert(std::is_arithmetic_v<N> || std::is_same_v<T, std::string>, "N debe ser un numero o T debe ser un std::string");

static_assert(std::is_same_v<T, std::string> || std::is_same_v<T, char>, "S debe ser un tipo de texto (std::string o char)");

public:
    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que la cadena ingresada sea del tipo correcto.
    *
    * \return Devuelve la misma cadena si esta es del tipo correcto.
    */
    static T TextoSeguro();

    static T TextoMinimo(unsigned min);

    static T TextoMaximo(unsigned max);

    static T TextoCerrado(unsigned min, unsigned max);
    
    static T TextoPermitido(const char caracteres[], unsigned int longitudCaracteres);

    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que el valor ingresado sea del tipo correcto.
    *
    * \return Devuelve el mismo valor si este es del tipo correcto.
    */
    static N LongitudSegura();

    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que el valor ingresado sea positivo.
    *
    * \return Devuelve el valor ingresado si cumple con la condicion.
    */
    static N LongitudPositiva();

    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que el valor ingresado no sea menor al establecido.
    *
    * \param min Es el valor minmo que puede ser ingresado.
    * 
    * \return Devuelve el valor ingresado si cumple con la condicion.
    */
    static N LongitudMinima(N min);

    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que el valor ingresado no sea mayor al establecido.
    *
    * \param max Es el valor maximo que puede ser igresado.
    * 
    * \return Devuelve el valor ingresado si cumple con la condicion.
    */
    static N LongitudMaxima(N max);

    //-------------------------------------------------------------------------------------------------------------------------
    /** \brief Verifica que el valor ingresado no salga de los limites establecidos.
    *
    * \param min Es el valor minimo que puede ser ingresado.
    * \param max Es el valor maximo que puede ser ingresado.
    * 
    * \return Devuelve el valor ingresado si cumple con la condicion.
    */
    static N LongitudCerrada(N min, N max);
};

#include "../Templates/CapturaSegura.tpp"

#endif

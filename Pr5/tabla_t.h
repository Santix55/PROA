/**
 * Clase que implementa una tabla hash con tipo clave, valor y lista de colisiones variables.
 * El tipo que implementa la lista de colisiones debe de soportar las siguientes operaciones para su correcto funciona-
 * miento: resize(), begin()->iterator, end()->iterator y push_back(TipoClave)
 * @file tabla_t.h
 * @author Enric Gil Gallen
 * @author Santiago Millán Giner
 */
#ifndef _TABLA_T_H
#define _TABLA_T_H
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <functional>
using namespace std;

/**
 * @class HashInt
 * Policy Class para calcular el hash de cualquier clave, sin importar su tipo
 */
template<class T>
class miHash {
public:
    /**
     * Función hash
     * @param clave entero de entrada
     * @return hash de dicho valor
     */
    static unsigned hash (T clave) {
        std::hash<T> h;
        return h(clave);
    }
};

template <
        typename TipoClave,
        typename TipoDato,
        template<typename Celda, typename Alloc = std::allocator<Celda>> class Cont = std::vector,
        typename Hash = miHash<TipoClave>> //

class Tabla_t {
    public:
        struct Celda {
            TipoClave clave;
            TipoDato dato;
        };

        Tabla_t (unsigned);
        bool buscar(TipoClave, TipoDato&) ;
        void insertar(TipoClave, const TipoDato&);
        unsigned hash(TipoClave) const;
        void mostrar(std::ostream & sal) const;

    private:
        typedef Cont<Celda> ListaDatos; // Se tiene que permitir cambiar desde el main
        vector<ListaDatos> t;
};

/**
 * Constructor of class
 * @param tam Size of table. Must be double of the number of elements.
 */
template <typename TipoClave, typename TipoDato, template<typename,typename> class Cont, typename Hash>
Tabla_t<TipoClave,TipoDato,Cont,Hash>::Tabla_t(unsigned tam)
{
    t.resize(tam);
}

/**
 * Insert an element
 * @param clave Key of the element
 * @param valor Value to be stored
 */
template <typename TipoClave, typename TipoDato, template<typename,typename> class Cont, typename Hash>
void Tabla_t<TipoClave,TipoDato,Cont,Hash>::insertar(TipoClave clave, const TipoDato & valor)
{
    unsigned i;
    i = hash(clave);
    t[i].push_back(Celda{clave,valor} );
}

/**
 * Search for an element
 * @param clave Key of the element
 * @param valor Value founded with key "clave"
 * @return true if element founded, false otherwise
 */
template <typename TipoClave, typename TipoDato, template<typename,typename> class Cont, typename Hash>
bool Tabla_t<TipoClave,TipoDato,Cont,Hash>::buscar(TipoClave clave, TipoDato & valor)
{
    unsigned i;
    i = hash(clave);
    for(auto e: t[i])
    {
        if(e.clave == clave)
        {
            valor = e.dato;
            return true;
        }
    }
    return false;
}

/**
 * Hash function for any value
 * @param clave Key
 */
template <typename TipoClave, typename TipoDato, template<typename,typename> class Cont, typename Hash>
unsigned Tabla_t<TipoClave,TipoDato,Cont,Hash>::hash(TipoClave clave) const
{
    /*
    unsigned long h = 5381;

    // Solo valido para strings
    for(unsigned i = 0; i < clave.size(); i++)
        h = ((h << 5) + h) + clave[i];

    return h % t.size();
     */
    return Hash::hash(clave) % t.size();
}

/**
 * Write the hash table to a stream
 * @param sal output stream
 */
template <typename TipoClave, typename TipoDato, template<typename,typename> class Cont, typename Hash>
void Tabla_t<TipoClave,TipoDato,Cont,Hash>::mostrar(std::ostream & sal) const
{
    for(unsigned i = 0; i < t.size(); i++)
    {
        sal << i << ":" ;
        for(auto e: t)
            sal << e.dato << " -> ";
        sal << std::endl;
    }
}

#endif //_TABLA_T_H

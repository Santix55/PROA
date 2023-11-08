/**
 * @author Santiago Millán Giner
 * @author Enric Gil Gallen
 *  TablaIterator practia 6
 *  @file tabla_t.h
 */
#ifndef _TABLA_T_H
#define _TABLA_T_H

#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <type_traits>

using namespace std;

template<typename TipoClave, typename TipoDato>
class TablaIterator;

template<typename TipoClave, typename TipoDato>

/**
 * @class Tabla_t
 * @tparam TipoClave valor que tendra la clave
 * @tparam TipoDato valor que tendra el valor valga la redundancia
 */
class Tabla_t {

    friend class TablaIterator<TipoClave, TipoDato>;

public:
    /**
     * @tparam TipoClave valor que tendra la clave
     * @tparam TipoDato valor que tendra el valor valga la redundancia
     */
    struct Celda {
        TipoClave clave;
        TipoDato dato;

        ostream &operator<<(ostream &out) {
            out << clave << ":" << dato << endl;
            return out;
        }

        friend ostream &operator<<(ostream &out, Celda celda) {
            out << celda.clave << " : " << celda.dato;
            return out;
        }

        bool operator<(Celda other) {
            return this->clave < other.clave;
        }
    };

    Tabla_t(unsigned);

    bool buscar(TipoClave, TipoDato &);

    void insertar(TipoClave, const TipoDato &);

    unsigned hash(TipoClave) const;

    void mostrar(std::ostream &sal) const;

    TablaIterator<TipoClave, TipoDato> begin();

    TablaIterator<TipoClave, TipoDato> end();

private:
    typedef vector<Celda> ListaDatos; // Se tiene que permitir cambiar desde el main
    vector<ListaDatos> t;
};

/**
 * Constructor of class
 * @param tam Size of table. Must be double of the number of elements.
 */
template<typename TipoClave, typename TipoDato>
Tabla_t<TipoClave, TipoDato>::Tabla_t(unsigned tam) {
    t.resize(tam);
}

/**
 * Insert an element
 * @param clave Key of the element
 * @param valor Value to be stored
 */
template<typename TipoClave, typename TipoDato>
void Tabla_t<TipoClave, TipoDato>::insertar(TipoClave clave, const TipoDato &valor) {
    unsigned i;
    i = hash(clave);
    t[i].push_back(Celda{clave, valor});
}

/**
 * Search for an element
 * @param clave Key of the element
 * @param valor Value founded with key "clave"
 * @return true if element founded, false otherwise
 */
template<typename TipoClave, typename TipoDato>
bool Tabla_t<TipoClave, TipoDato>::buscar(TipoClave clave, TipoDato &valor) {
    unsigned i;
    i = hash(clave);
    for (unsigned j = 0; j < t[i].size(); j++) {
        if (t[i][j].clave == clave) {
            valor = t[i][j].dato;
            return true;
        }
    }
    return false;
}

/**
 * Hash function for strings
 * @param clave Key
 */
template<typename TipoClave, typename TipoDato>
unsigned Tabla_t<TipoClave, TipoDato>::hash(TipoClave clave) const {
    unsigned long h = 5381;

    // Solo valido para strings
    for (unsigned i = 0; i < clave.size(); i++)
        h = ((h << 5) + h) + clave[i];

    return h % t.size();
}

/**
 * Write the hash table to a stream
 * @param sal output stream
 */
template<typename TipoClave, typename TipoDato>
void Tabla_t<TipoClave, TipoDato>::mostrar(std::ostream &sal) const {
    for (unsigned i = 0; i < t.size(); i++) {
        sal << i << ":";
        for (unsigned j = 0; j < t[i].size(); j++)
            sal << t[i][j].dato << " -> ";
        sal << std::endl;
    }
}

/**
 *
 * @tparam TipoClave
 * @tparam TipoDato
 *
 *  It_v Iterador del vector
 *  It_vv Iterador del vector de vectores
 *  It_vv_end Iterador elemento final del vector de vectores
 */
template<typename TipoClave, typename TipoDato>
class TablaIterator : public std::iterator<std::forward_iterator_tag,
        typename Tabla_t<TipoClave, TipoDato>::Celda,
        std::ptrdiff_t,
        typename Tabla_t<TipoClave, TipoDato>::Celda *,
        typename Tabla_t<TipoClave, TipoDato>::Celda &> {
private:
    using Celda = typename Tabla_t<TipoClave, TipoDato>::Celda;
    using It_v = typename Tabla_t<TipoClave, TipoDato>::ListaDatos::iterator;                    // Iterador de vectores
    using It_vv = typename vector<typename Tabla_t<TipoClave, TipoDato>::ListaDatos>::iterator; // Iterador de vector de vectores

    It_v it_v;     // Iterador del vector
    It_vv it_vv;    // Iterador del vector de vectores
    It_vv it_vv_end;// Iterador elemento final del vector de vectores

public:
    TablaIterator() {};

    TablaIterator(It_v _it_v, It_vv _it_vv, It_vv _it_vv_end) {
        it_v = _it_v;
        it_vv = _it_vv;
        it_vv_end = _it_vv_end;
    }

    void desplazar();

    /**
     * Cojer el dato al que apunta el iterador
     * @return el valor al que apunta el iterador
     */
    Celda operator*() const {
        return *it_v;
    }

    /**
     * Avanzar iterador
     * @return el iterador en el que nos encontavamos
     */
    TablaIterator operator++() { // ++ prefijo
        it_v++;
        desplazar();
        return *this;
    }

    /**
     * Avanzar iterador
     * @return el iterador en el que nos encontavamos
     */
    TablaIterator operator++(int _) {   // posfijo ++
        auto it_vv_ret = it_vv;
        auto it_v_ret = it_v;
        it_v++;
        desplazar();
        return TablaIterator<TipoClave, TipoDato>(it_v, it_vv, it_vv_end);
    }

    /**
     * Comprueba si son iguales los iteradores
     * @return resultado
     */
    friend bool operator==(const TablaIterator &a, const TablaIterator &b) {
        if(a.it_vv ==  a.it_vv_end && b.it_vv == b.it_vv_end)
            return true;
        return a.it_v == b.it_v;
    }

    /**
     * Comprueba si son distintos los iteradores
     * @return resultado
     */
    friend bool operator!=(const TablaIterator &a, const TablaIterator &b) {
        return !(a==b);
    }

    /*void debug() {
        cout << "Posición a elemento " <<&(*it_vv()) - &(*it_v.begin()) << endl;
        cout << "del vector"
    } */
};

/**
 * Función auxiliar que desplaza hasta que el puntero a celda no apunte al final de una celda,
 * a no ser que esa celda se encuentre en el último vector del vector de Listos.
 */
template<typename TipoClave, typename TipoDato>
void TablaIterator<TipoClave, TipoDato>::desplazar() {
    while (it_v == it_vv->end() && it_vv != it_vv_end) {
        ++it_vv;
        it_v = it_vv->begin();
    }
}

template<typename TipoClave, typename TipoDato>
TablaIterator<TipoClave, TipoDato> Tabla_t<TipoClave, TipoDato>::begin() {
    TablaIterator<TipoClave, TipoDato> it(t.begin()->begin(), t.begin(), t.end());
    it.desplazar();
    return it;
}

template<typename TipoClave, typename TipoDato>
TablaIterator<TipoClave, TipoDato> Tabla_t<TipoClave, TipoDato>::end() {
    typename Tabla_t<TipoClave, TipoDato>::ListaDatos::iterator xdefecto;
    TablaIterator<TipoClave, TipoDato> it (xdefecto, t.end(), t.end());
    return it;
}

#endif //_TABLA_T_H

/**
 * Single linked list implementation
 * Programación Avanzada
 * Year 2021/2022
 * 
 * @author F. Barber
 */

#ifndef _LISTA_H
#define _LISTA_H

#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <iostream>

template<typename T>
class ListaIterator;

/**
 * Single linked list
 * @tparam T Type of the elements in the list
 */
template<typename T>
class Lista {
    /**
     * @param T Type of the elements in the list
     * @Nodo referencia al siguiente nodo
     */
    struct Nodo {
        T valor;
        Nodo *sig;
    };

    typedef Nodo *PtrNodo;

    PtrNodo ptr;
    //PtrNodo begin_ptr;

    friend class ListaIterator<T>;

public:
    using iterator = ListaIterator<T>;

    Lista() : ptr(nullptr) {}

    void push_front(const T &);

    void mostrar() const;

    ListaIterator<T> begin() const {
        return ListaIterator<T>(ptr);
    }

    ListaIterator<T> end() const {
        return ListaIterator<T>(nullptr);
    }
};

template<typename T>
class ListaIterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T *, T &> {
private:
    typename Lista<T>::PtrNodo it_ptr;

public:
    ListaIterator() {}

    ListaIterator(typename Lista<T>::PtrNodo _it_ptr) : it_ptr(_it_ptr) {}

    /**
     * Cojer el dato al que apunta el iterador
     * @return el valor al que apunta el iterador
     */
    T operator*() const {
        return it_ptr->valor;
    }

    /**
     * Avanzar iterador
     * @return el iterador en el que nos encontavamos
     */
    ListaIterator operator++() { // ++ Prefijo
        it_ptr = it_ptr->sig;
        return *this;
    }

    /**
     * Avanzar iterador
     * @return el iterador en el que nos encontavamos
     */
    ListaIterator operator++(int n) { // Posfijo ++
        auto it_ret = it_ptr;
        it_ptr = it_ptr->sig;
        return iterator(it_ret);
    }

    /**
     * Comprueba si son iguales los iteradores
     * @return resultado
     */
    friend bool operator==(const ListaIterator &a, const ListaIterator &b) {
        return a.it_ptr == b.it_ptr;
    }

    /**
     * Comprueba si son distintos los iteradores
     * @return resultado
     */
    friend bool operator!=(const ListaIterator &a, const ListaIterator &b) {
        return a.it_ptr != b.it_ptr;
    }
};

/**
 * Add element at the beginning of the list
 * @param x element
 */
template<typename T>
void Lista<T>::push_front(const T &x) {
    PtrNodo aux = new Nodo;
    aux->valor = x;
    aux->sig = ptr;
    ptr = aux;
}

/**
 * Show the list
 */
template<typename T>
void Lista<T>::mostrar() const {
    PtrNodo aux = ptr;

    while (aux != nullptr) {
        std::cout << aux->valor << " ";
        aux = aux->sig;
    }
}

#endif

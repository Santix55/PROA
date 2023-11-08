#include <iostream>
#include <algorithm>
#include "lista.h"
#include <vector>
#include "tabla_t.h"
using namespace std;

template <typename Iter>
void mostrar(Iter begin, Iter end);

int main() {
    Lista<int> l1;
    l1.push_front(5);
    l1.push_front(3);
    l1.push_front(-1);
    l1.push_front(7);

    {
        /**
         * Muostrar el primer elemento de la lista
         */
        cout << "TEST 2.1" << endl;
        Lista<int>::iterator it;
        it = l1.begin();
        std::cout << *it << std::endl;
    }

    cout << endl << endl;

    {
        /**
         * Mostrar la lista
         */
        cout << "TEST 2.2" << endl;
        mostrar(l1.begin(), l1.end()); // Segmentation fault
    }

    cout << endl << endl;

    {
        /**
         * Copiar todos los elementos de la lista a un vector utilizando la función STL copy y mostrar el vector con la función anterior.
         */
        cout << "TEST 2.3" << endl;
        vector<int> v(4);
        std::copy(l1.begin(), l1.end(), v.begin());
        mostrar(v.begin(), v.end());
    }

    cout << endl << endl;

    {
        /**
         * Optiene el elemento mínimo con la función STL min_elemento.
         */
        cout << "TEST 2.4" << endl;
        std::cout << *std::min_element(l1.begin(),l1.end()) << std::endl; // Segmentation fault
    }

    cout << endl << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tabla_t<string,string> t(20);
    t.insertar("hola"s,"mundo"s);
    t.insertar("PROA"s,"C++"s);
    t.insertar("Nota P6"s,"10/10");
    t.insertar("clave"s, "valor"s);

    /**
     * Muostrar el primer elemento de la lista
     */
    {
        cout << "TEST 3.1" << endl;
        auto it = t.begin();
        std::cout << *it << std::endl;
    }

    cout << endl << endl;
    /**
     * Mostrar la lista
     */
    {
        cout << "TEST 3.2" << endl;
        mostrar(t.begin(), t.end());
    }

    cout << endl << endl;

    /**
     * Copiar todos los elementos de la lista a un vector utilizando la función STL copy y mostrar el vector con la función anterior.
     */
    {
        cout << "TEST 3.3" << endl;
        vector<typename Tabla_t<string,string>::Celda> v(4);
        std::copy(t.begin(), t.end(), v.begin());
        mostrar(v.begin(), v.end());
    }

    cout << endl << endl;

    /**
     * Optiene el elemento mínimo con la función STL min_elemento.
     */
    {
        cout << "TEST 3.4" << endl;
        std::cout << *std::min_element(t.begin(),t.end()) << std::endl; // Segmentation fault
    }


    return 0;
}

/**
 * Metodo que muestra todos los elementos
 * @tparam Iter
 * @param begin Iterador de inicio
 * @param end Iterador al final
 */
template <typename Iter>
void mostrar(Iter begin, Iter end) {
    while (begin != end) {
        cout << "- " << *begin << endl;
        ++begin;
    }
}
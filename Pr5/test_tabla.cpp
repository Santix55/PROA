/**
 * Prueba de la clase Tabla con contenedor de colisiones y función hash personalizable
 * @file test_tabla.cpp
 * @author Santiago Millán Giner
 * @author Enric Gil Gallen
 */
#include "alumno.h"
#include "tabla_t.h"
#include <list>
#include <iostream>
using namespace std;

/**
 * @class HashInt
 * Policy Class para calcular el hash de un entero
 */
template <typename T>
class HashInt {
public:
    /**
     * Función hash del entero i
     * @param i entero de entrada
     * @return hash de dicho entero
     */
    static unsigned hash(int i) {
        std::hash<int> h;
        return h(i);
    }
};

const int N_ELEMENTOS = 20;
const string SEPARATOR = "\n----------------------------\n";

int main () {
    /*
    cout << "1.- PREVIO" << endl;
    Tabla t (N_ELEMENTOS);

    for (int i=0; i<N_ELEMENTOS-1; ++i) {
        Alumno a(4);
        t.insertar(a.getDNI(), a);
    }
    Alumno a1(1);
    string dni = a1.getDNI();
    t.insertar(dni, a1);

    Alumno _;
    if (t.buscar(dni, _)) {
        cout << "El estudiante ha sido encontrado" << endl;
    }

    if (!t.buscar(""s, _)) {
        cout << "El estudiante no existe" <<endl;
    }
     */


    cout << SEPARATOR; ////////////////////////////////////////

    {
        Alumno a1(1);
        string dni = a1.getDNI();
        cout << "2.- TEMPLATE VECTOR" << endl;
        Tabla_t<string, Alumno> tt(N_ELEMENTOS);

        tt.insertar(dni, a1);
        for (int i = 0; i < N_ELEMENTOS - 1; ++i) {
            Alumno a(4);
            tt.insertar(a.getDNI(), a);
        }

        if (!tt.buscar(dni, a1)) {
            cout << "El estudiante ha sido encontrado" << endl;
        }

        if (!tt.buscar(""s, _)) {
            cout << "El estudiante no existe" << endl;
        }
    }

    cout << SEPARATOR; ////////////////////////////////////////


    cout << "3.- TEMPLATE LIST" << endl;
    Tabla_t<string,Alumno,list> tl (N_ELEMENTOS);

    Alumno a3(3);
    tl.insertar(a3.getDNI(),a3);
    for (int i=0; i<N_ELEMENTOS-1; ++i) {
        Alumno a(4);
        tl.insertar(dni, a);
    }

    if (!tl.buscar(a3.getDNI(), a3)) {
        cout << "El estudiante ha sido encontrado" <<endl;
    }

    if (!tl.buscar(""s, _)) {
        cout << "El estudiante no existe" <<endl;
    }


    cout << SEPARATOR; ////////////////////////////////////////

    cout << "4.- ENTEROS" << endl;
    Tabla_t<int,Alumno,vector,HashInt<int>> ti (N_ELEMENTOS);

    ti.insertar(1, a1);
    for (int i=0; i<N_ELEMENTOS-1; ++i) {
        Alumno a(4);
        ti.insertar(3, a);
    }

    if (!ti.buscar(1, a1)) {
        cout << "El estudiante ha sido encontrado" <<endl;
    }

    if (!tt.buscar(0, _)) {
        cout << "El estudiante no existe" <<endl;
    }

    return 0;
}

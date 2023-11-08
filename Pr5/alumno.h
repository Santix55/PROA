/**
 * Clase para representar alumnos
 * Curso 2020/2021
 */

#include <iostream>
#include <string>
#include <random>
#include <array>

using std::string;

#ifndef _ALUMNO_H_
#define _ALUMNO_H_

class Alumno
{
    string dni;
    string nombre;
    string apellidos;
    unsigned curso;
    unsigned telefono;
    
    static const unsigned NUM_NOMBRE = 15;
    static std::array<string, NUM_NOMBRE> list_nombre;
    static std::array<string, NUM_NOMBRE> list_apellido;
    static std::default_random_engine rnd;


public:
    /**
     * Constructor por defecto.
     * Crea un alumno vacio.
     */
    Alumno() {};
    /**
     * Crea un alumno para un curso concreto, con el resto de datos aleatorios.
     * @param curs Curso del alumno
     */
    Alumno(unsigned curs);
    /**
     * Devuelve el DNI para usarlo como clave.
     * @return DNI del alumno.
     */
    string getDNI() const 
        {return dni; };
        
    friend std::ostream & operator<<(std::ostream &, const Alumno &);
             
};

#endif

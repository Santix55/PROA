#include "lista.h"

template <typename T>
class ListaIterator : public std::iterator<std::forward_iterator_tag, Lista<T>>{
    Nodo<T> * head;

public:
    Nodo<T>* getHead(){
        return this->head;
    }

    void agragarInicio(T valor){
        Nodo<T> nuevo = new Nodo<T>(valor, this-> head);
        this->head = nuevo;
    }

    void agregarFinal(T valor){
        Nodo<T> nuevo = new Nodo<T>(valor, nullptr);
        if(this->head){
            Nodo<T>* current = this->head;
            while(current -> getnext()){
                current = current -> getnext();
            }
            current -> setNext(nuevo);
        }
        else{
            this->head = nuevo;
        }
    }

    Nodo darPrimero(){
        return this->head;
    }

    Nodo darUltimo(){
        if(this->head){
            Nodo<T>* current = this->head;
            while(current -> getnext()){
                current = current -> getnext();
            }
            return current;
        }
        else{
            return this->head;
        }
    }
};
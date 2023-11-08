/**
 * Class  Array (SArray) 2
 *
 */
#ifndef _SARRAY2_H
#define _SARRAY2_H

#include "expresion.h"
#include <cmath>

template<typename T>
class SArray2 {
    T *storage;       // storage of the elements
    size_t storage_size;  // number of elements

public:
    // create array with initial size
    explicit SArray2(size_t s)
            : storage(new T[s]), storage_size(s) {
        init();
    }

    // copy constructor
    SArray2(SArray2<T> const &orig)
            : storage(new T[orig.size()]), storage_size(orig.size()) {
        copy(orig);
    }

    ~SArray2() {
        delete[] storage;
    }

    SArray2<T> &operator=(SArray2<T> const &orig) {
        if (&orig != this) {
            copy(orig);
        }
        return *this;
    }

    size_t size() const {
        return storage_size;
    }

    T operator[](size_t idx) const {
        return storage[idx];
    }

    T &operator[](size_t idx) {
        return storage[idx];
    }

protected:
    // init values with default constructor
    void init() {
        for (size_t idx = 0; idx < size(); ++idx) {
            storage[idx] = T();
        }
    }

    // copy values of another array
    void copy(SArray2<T> const &orig) {
        assert(size() == orig.size());
        for (size_t idx = 0; idx < size(); ++idx) {
            storage[idx] = orig.storage[idx];
        }
    }

    // Metodo +
    template<class T2>
    friend SArray2<T2> operator+(SArray2<T2> const &a, SArray2<T2> const &b);

    template<class T2>
    friend SArray2<T2> operator+(T2 const &a, SArray2<T2> const &b);

    template<class T2>
    friend SArray2<T2> operator+(SArray2<T2> const &b, T2 const &a);

    //Metodo *
    template<typename T2>
    friend SArray2<T2> operator*(SArray2<T2> const &a, SArray2<T2> const &b);

    template<class T2>
    friend SArray2<T2> operator*(T2 const &a, SArray2<T2> const &b);

    template<class T2>
    friend SArray2<T2> operator*(SArray2<T2> const &b, T2 const &a);

    //Método pow
public:
    SArray2 pow (T n) const {
        SArray2<T> res (this->size());
        for (size_t idx = 0; idx < size(); ++idx) {
            res[idx] = std::pow (storage[idx], n);
        }
        return res;
    }

    /*
    // Metodo pow
    template<typename T>
    SArray2<T> pow (SArray2<T> const& a, SArray2<T> const& b)
    {
        SArray2<T> result(a.size());
        for (size_t k = 0; k < a.size(); ++k) {
            result[k] = pow(a[k],b[k]);
        }
        return result;
    }
    */
};

template<typename T>
SArray2<T> operator+(SArray2<T> const &a, SArray2<T> const &b) {
    SArray2<T> result(a.size());
    for (size_t k = 0; k < a.size(); ++k) {
        result[k] = a[k] + b[k];
    }
    return result;
}

template<typename T>
SArray2<T> operator+(T const &a, SArray2<T> const &b) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = a + b[k];
    }
    return result;
}

template<typename T>
SArray2<T> operator+(SArray2<T> const &b, T const &a) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = a + b[k];
    }
    return result;
}

template<typename T>
SArray2<T> operator*(SArray2<T> const &a, SArray2<T> const &b)
{
    SArray2<T> result(a.size());
    for (size_t k = 0; k < a.size(); ++k) {
        result[k] = a[k] * b[k];
    }
    return result;
}

template<typename T>
SArray2<T> operator*(T const &a, SArray2<T> const &b) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = a * b[k];
    }
    return result;
}

template<typename T>
SArray2<T> operator*(SArray2<T> const &b, T const &a) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = a * b[k];
    }
    return result;
}

// POW
/*
template<typename T>
SArray2<T> pow(SArray2<T> const &a, SArray2<T> const &b)
{
    SArray2<T> result(a.size());
    for (size_t k = 0; k < a.size(); ++k) {
        result[k] = pow(a[k],b[k]);
    }
    return result;
}

template<typename T>
SArray2<T> pow(T const &a, SArray2<T> const &b) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = pow(a,b[k]);
    }
    return result;
}

template<typename T>
SArray2<T> pow(SArray2<T> const &b, T const &a) {
    SArray2<T> result(b.size());
    for (size_t k = 0; k < b.size(); ++k) {
        result[k] = pow(a,b[k]);
    }
    return result;
}
 */

#endif //SARRAY2_H

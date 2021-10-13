#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <cstddef>

template <class Category,
            class T,
            class Distance = ptrdiff_t,
            class Pointer = T*,
            class Reference = T&
            >
class Iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
private:
    T* ptr;
public:
    Iterator(T* x) : ptr(x) {}
    Iterator(const Iterator& x) : ptr(x.ptr) {}
    Iterator & operator++() { ++p; return *this; }
    Iterator operator++(T x) { Iterator tmp(*this); operator++(); return tmp; }
    bool operator==(const Iterator &ths) const { return ptr == ths.ptr; }
    bool operator!=(const Iterator &ths) const { return ptr != ths.ptr; }
    T *operator*() { return *ptr }
};

#endif
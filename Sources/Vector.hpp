#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "Iterators.hpp"

template <class T>
class IteratorVector : public Iterator
{
	T _ptr;
public:
	IteratorVector() {}
	IteratorVector(const IteratorVector& other) { this->_ptr = other._ptr; return; }
	~IteratorVector() {};
	IteratorVector& operator==(const IteratorVector& other) const { return this->_ptr == other._ptr; }
	IteratorVector& operator!=(const IteratorVector& other) const { return this->_ptr != other._ptr; }
	
};

template < class T, class Alloc = std::allocator<T> >
class vector
{
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef reference allocator_type::reference;
	typedef pointer allocator_type::pointer;
	typedef const_reference allocator_type::const_reference;
	typedef const_pointer allocator_type::const_pointer;
	typedef difference_type IteratorTraits<iterator>::difference_type;
};

#endif
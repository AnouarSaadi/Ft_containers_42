#ifndef VECTOR_HPP
# define VECTOR_HPP

template <class T>
class Allocator
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template <class Type> struct rebind {
  		typedef Allocator<Type> other;
	};
};

template < class T, class Alloc = Allocator<T> >
class vector : public Iterator
{
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef reference allocator_type::reference;
	typedef pointer allocator_type::pointer;
	typedef const_reference allocator_type::const_reference;
	typedef const_pointer allocator_type::const_pointer;
	// typedef itera
};

#endif
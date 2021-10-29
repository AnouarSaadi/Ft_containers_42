#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include "Iterators.hpp"
#include <iostream>
class Iterator;
// # include <vector> // vector
namespace ft {
	template <class Vector>
	class VectorIterator
	{ 
	public:
		// typedef typename Vector::value_type	value_type;
		typedef typename ft::IteratorTraits<Vector>::value_type	value_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef std::ptrdiff_t				difference_type; 
	
	private:
		pointer m_Ptr;

	public:
		// Member functions
		VectorIterator<Vector>() {} // constructor
		VectorIterator<Vector>(const pointer ptr) : m_Ptr(ptr) {} // param constructor
		VectorIterator<Vector>(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return; } // copy constructor
		VectorIterator<Vector>& operator=(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return *this; }// assignment operator
		~VectorIterator<Vector>() {}; // destructor
		// operator *
		reference operator*() const { return *m_Ptr; }
		// ->
		pointer operator->() const { return m_Ptr; }

		// +
		VectorIterator<Vector> operator+(difference_type off) { return VectorIterator(m_Ptr + off); }
		VectorIterator<Vector>& operator+= (difference_type off) {
			m_Ptr += off;
			return *this;
		}
		VectorIterator<Vector> & operator++() {
			m_Ptr++;
			return *this;
		}
		VectorIterator<Vector> operator++(int) {
			VectorIterator<Vector> tmp(*this);
			++*this;
			return tmp;
		}

		// -
		VectorIterator<Vector> operator-(difference_type off) { return VectorIterator(m_Ptr - off); }
		VectorIterator<Vector>& operator-= (difference_type off) {
			m_Ptr -= off;
			return *this;
		}
		VectorIterator<Vector>& operator--() {
			m_Ptr--;
			return *this;
		}
		VectorIterator<Vector> operator--(int) {
			VectorIterator<Vector> tmp(*this);
			--*this;
			return tmp;
		}
		
		// []
		reference operator[] (difference_type idx) const { return *(m_Ptr + idx); }

		// base()
		pointer base() const { return m_Ptr; }
		
	}; // end VectorIterator class
	// Non-member function overloads
	// operator ==
	template <class Vector>
  	bool operator== (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	// operator !=
	template <class Vector>
  	bool operator!= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return !(lhs == rhs);
	}
	// operator +
	template <class Vector>
	VectorIterator<Vector> operator+ (typename VectorIterator<Vector>::difference_type n, const VectorIterator<Vector>& _it)
	{
		return VectorIterator<Vector>(_it + n);
	}
	// operator -
	template <class Vector>
	typename VectorIterator<Vector>::difference_type operator- (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	// operator <
	template <class Vector>
	bool operator< (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() < rhs.base(); }
	// operator >
	template <class Vector>
	bool operator> (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() > rhs.base(); }
	// operator <=
	template <class Vector>
	bool operator<= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return !(lhs > rhs); }
	// operator>=
	template <class Vector>
	bool operator>= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return !(lhs < rhs); }
	
	
	// Vector Class
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef typename Alloc::reference						reference;
		typedef typename Alloc::const_reference					const_reference;
		typedef typename Alloc::pointer							pointer;
		typedef typename Alloc::const_pointer					const_pointer;
		typedef typename ft::VectorIterator< Vector<T> > 		iterator;
		typedef typename ft::VectorIterator< const Vector<T> >	const_iterator;
		typedef typename ft::ReverseIterator<iterator>			reverse_iterator;
	
	private:
		pointer			vecData;
		size_type		vecSize;
		size_type		vecCapacity;
		allocator_type	vecAllocator;

	public:
		// destructors
			// default
		Vector(const allocator_type& alloc = allocator_type()) : vecData(nullptr), vecSize(0)
		{
			vecAllocator = alloc;
			std::cout << "Vector 0" << std::endl;
			vecData = vecAllocator.allocator();
			vecSize = 0;
			vecCapacity = 0;
		}
			// fill
		Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : vecData(nullptr) , vecSize(0)
		{
			vecAllocator = alloc;
			std::cout << "Vector 1" << std::endl;
			vecData = vecAllocator.allocate(1);
			vecSize = n;
			for (size_type i = 0; i < vecSize; ++i)
				vecData[i] = val;
			vecCapacity = vecSize;
		}
			// range
		// template <class InputIterator> 
		// Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : vecData(nullptr), vecSize(0)
		// {
		// 	std::cout << "Vector 2" << std::endl;
		// 	(void)last; (void)first; (void)alloc;
		// }
			// copy
		Vector(const Vector& x) { (void)x; }
		// assign operator
		Vector& operator= (const Vector& x) { (void)x; }

		// operator []
		reference operator[] (size_type idx) { return vecData[idx]; };
	};// end vector class
}; // end namspace ft
#endif

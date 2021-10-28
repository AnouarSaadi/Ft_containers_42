#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include "Iterators.hpp"
class Iterator;
// # include <vector> // vector
namespace ft {
	template <class Vector>
	class VectorIterator : public Iterator
	{ 
	public:
		typedef typename Vector::value_type	value_type;
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
		// reference operator=(difference_type off) const { *this = off; return *this; }

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
	// operator <=
	template <class Vector>
	bool operator<= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() <= rhs.base(); }
	// operator >
	template <class Vector>
	bool operator> (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() > rhs.base(); }
	// operator>=
	template <class Vector>
	bool operator>= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() >= rhs.base(); }
	
	
	// Vector Class
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef VectorIterator< Vector<T> > 						iterator;
		typedef typename IteratorTraits<iterator>::difference_type	difference_type;
		typedef ReverseIterator<iterator>							reverse_iterator;
		typedef size_t												size_type;
	
	private:
		pointer		m_Data;
		size_type	m_Size;
		size_type	m_Capacity;

	public:
		// destructors
			// default
		Vector (const allocator_type& alloc = allocator_type()) : m_Data(nullptr), m_Size(0)
		{
			(void)alloc;
		}
			// fill
		Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : m_Data(nullptr) , m_Size(0)
		{
			m_Data = alloc.allocate(n, 0);
			m_Size = n;
			for (size_type i = 0; i < m_Size; ++i)
				m_Data[i] = val;
		}
			// range
		template <class Iterator> Vector (Iterator first, Iterator last, const allocator_type& alloc = allocator_type()) : m_Data(nullptr), m_Size(0)
		{
			(void)last; (void)first; (void)alloc;
		}
			// copy
		Vector (const Vector& x) { (void)x; }
		// assign operator
		Vector& operator= (const Vector& x) { (void)x; }

		// operator []
		reference operator[] (size_type n) { return m_Data[n]; };
	};// end vector class
}; // end namspace ft
#endif

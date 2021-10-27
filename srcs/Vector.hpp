#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include "Iterators.hpp"
# include <vector> // vector
namespace ft {
	template <class Vector>
	class VectorIterator : public Iterator
	{ 
	public:
		typedef Vector::value_type	value_type;
		typedef value_type*			pointer;
		typedef value_type&			reference;
	
	private:
		pointer m_Ptr;

	public:
		// Member functions
		VectorIterator() {} // constructor
		VectorIterator(const pointer ptr) : m_Ptr(ptr) {} // param constructor
		VectorIterator(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return; } // copy constructor
		VectorIterator& operator=(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return *this; }// assignment operator
		~VectorIterator() {}; // destructor
		// operator *
		reference operator*() const { return *m_Ptr; }
		// ->
		pointer operator->() const { return m_Ptr; }
		// reference operator=(difference_type off) const { *this = off; return *this; }

		// +
		VectorIterator operator+(difference_type off) { return VectorIterator(m_Ptr + off); }
		VectorIterator& operator+= (difference_type off) {
			m_Ptr += off;
			return *this;
		}
		VectorIterator & operator++() {
			m_Ptr++;
			return *this;
		}
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			++*this;
			return tmp;
		}
		// -
		VectorIterator operator-(difference_type off) { return VectorIterator(m_Ptr - off); }
		VectorIterator& operator-= (difference_type off) {
			m_Ptr -= off;
			return *this;
		}
		VectorIterator& operator--() {
			m_Ptr--;
			return *this;
		}
		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
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
	template <class Iterator>
  	bool operator== (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	// operator !=
	template <class Iterator>
  	bool operator!= (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}
	// operator +
	template <class Iterator>
	VectorIterator<Iterator> operator+ (typename VectorIterator<Iterator>::difference_type n, const VectorIterator<Iterator>& _it)
	{
		return VectorIterator(_it + n);
	}
	// operator -
	template <class Iterator>
	typename VectorIterator<Iterator>::difference_type operator- (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	// operator <
	template <class Iterator>
	bool operator< (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }
	// operator <=
	template <class Iterator>
	bool operator<= (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
	// operator >
	template <class Iterator>
	bool operator> (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
	// operator>=
	template <class Iterator>
	bool operator>= (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }
	
	
	// Vector Class
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef allocator_type::reference					reference;
		typedef allocator_type::pointer						pointer;
		typedef allocator_type::const_reference				const_reference;
		typedef allocator_type::const_pointer				const_pointer;
		typedef IteratorTraits<iterator>::difference_type	difference_type;
		typedef VectorIterator< Vector<T> >					iterator;
		typedef ReverseIterator<iterator>					reverse_iterator;
		typedef size_t										size_type;
	
	private:
		pointer m_Data;
		size_type m_Size;

	public:
		// destructors
			// default
		Vector (const allocator_type& alloc = allocator_type()) 
		{
			m_Data = alloc.allocator();
			m_Size = 0;
		}
			// fill
		Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) 
		{
			
		}
			// range
		template <class Iterator> Vector (Iterator first, Iterator last, const allocator_type& alloc = allocator_type()) {}
			// copy
		Vector (const Vector& x) {}
		// assign operator
		Vector& operator= (const Vector& x) {}
	};// end vector class
}; // end namspace ft
#endif
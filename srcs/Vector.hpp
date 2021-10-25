#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "Iterators.hpp"
namespace ft {
	template <class T>
	class IteratorVector : public Iterator
	{
		T _ptr;
	public:
		// Member functions
		IteratorVector() {} // constructor
		IteratorVector(const IteratorVector& other) { this->_ptr = other._ptr; return; } // copy constructor
		IteratorVector& operator=(const IteratorVector& other) { this->_ptr = other._ptr; return *this; }// assignment operator
		~IteratorVector() {}; // destructor
		reference operator*() const { return *(this->_ptr); }
		pointer operator->() const { return &(operator*()); }

		IteratorVector & operator++() {
			++(this->_ptr);
			return *this;
		}
		IteratorVector operator++(int) {
			IteratorVector tmp(*this);
			++(*this);
			return tmp;
		}
		IteratorVector& operator--() {
			--(this->_ptr);
			return *this;
		}
		IteratorVector operator--(int) {
			IteratorVector tmp(*this);
			--(*this);
			return tmp;
		}
		IteratorVector operator+(difference_type n) { return IteratorVector(this->_ptr + n); }
		IteratorVector operator-(difference_type n) { return IteratorVector(this->_ptr - n); }
		IteratorVector& operator+= (difference_type n) {
			this->_it += n;
			return *this;
		}
		IteratorVector& operator-= (difference_type n) {
			this->_it -= n;
			return *this;
		}
	}; // end IteratorVector class
	// Non-member function overloads
	template <class Iterator>
  	bool operator== (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs)
	{
		return (lhs.operator*() == rhs.operator*());
	}
	template <class Iterator>
  	bool operator!= (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs)
	{
		return (lhs.operator*() != rhs.operator*());
	}
	template <class Iterator>
	IteratorVector<Iterator> operator+ (typename IteratorVector<Iterator>::difference_type n, const IteratorVector<Iterator>& _it)
	{
		return IteratorVector(_it + n);
	}
	template <class Iterator>
	IteratorVector<Iterator> operator- (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs)
	{
		return lhs.operator*() - rhs.operator*();
	}
	template <class Iterator>
	bool operator< (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs) { return lhs.operator*() < rhs.operator*(); }
	template <class Iterator>
	bool operator<= (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs) { return lhs.operator*() <= rhs.operator*(); }
	template <class Iterator>
	bool operator> (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs) { return lhs.operator*() > rhs.operator*(); }
	template <class Iterator>
	bool operator>= (const IteratorVector<Iterator>& lhs, const IteratorVector<Iterator>& rhs) { return lhs.operator*() >= rhs.operator*(); }

	// Vector Class
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef reference allocator_type::reference;
		typedef pointer allocator_type::pointer;
		typedef const_reference allocator_type::const_reference;
		typedef const_pointer allocator_type::const_pointer;
		typedef difference_type IteratorTraits<iterator>::difference_type;
	};// end vector class
}; // end namspace ft
#endif
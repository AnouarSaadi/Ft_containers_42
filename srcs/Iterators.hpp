#ifndef ITERATORS_HPP
#	define ITERATORS_HPP
#	include <iterator>
#	include <cstddef>
#include "Vector.hpp"
class Vector;
namespace ft {
	/* iterator */

	template <class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&
				>
	class Iterator
	{
	public:
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
		typedef Category	iterator_category;
	}; // end Iterator

	/* iterator_traits */

	template <class Iter>
	class IteratorTraits
	{
	public:
		
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
	}; // end class IteratorTraits

	template <class T>
	class IteratorTraits<T*>
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; //end class IteratorTraits<T*>

	template <class T>
	class IteratorTraits<const T*>
	{
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; // end IteratorTraits<const T*>

	/* reverse_iterator */

	template <class Iter> 
	class ReverseIterator
	{
	public:
		typedef Iter												iterator_type;
		typedef typename IteratorTraits<Iter>::value_type			value_type;
		typedef typename IteratorTraits<Iter>::pointer				pointer;
		typedef typename IteratorTraits<Iter>::reference			reference;
		typedef typename IteratorTraits<Iter>::difference_type		difference_type;
		typedef typename IteratorTraits<Iter>::iterator_category	iterator_category;
	
	protected:
		iterator_type _it;

	public:
		// Member functions
		ReverseIterator<Iter>() : _it(nullptr) {}
		ReverseIterator<Iter>(iterator_type it) : _it(it) {}
		ReverseIterator<Iter>(const ReverseIterator& oth) : _it(oth._it) {}
		iterator_type base() const { return _it; }
		reference operator*() const { return *_it; }
		// +
		ReverseIterator<Iter> operator+ (difference_type off) const { return ReverseIterator<Iter>(_it - off); }
		ReverseIterator<Iter> & operator++() {
			_it--;
			return *this;
		}
		ReverseIterator<Iter> operator++(int) {
			ReverseIterator<Iter> tmp(*this);
			--*this;
			return tmp;
		}
		ReverseIterator<Iter>& operator+= (difference_type off) {
			_it -= off;
			return *this;
		}
		// -
		ReverseIterator<Iter> operator- (difference_type off) const { return ReverseIterator<Iter>(this->_it + off); }
		ReverseIterator<Iter> & operator--() {
			_it++;
			return *this;
		}
		ReverseIterator<Iter> operator--(int) {
			ReverseIterator<Iter> temp(*this);
			++*this;
			return temp;
		}
		ReverseIterator<Iter>& operator-= (difference_type off) {
			_it += off;
			return *this;
		}
		// ->
		pointer operator->() const { return _it; }
		// []
		reference operator[] (typename ReverseIterator<Iter>::difference_type idx) const { return *(*this + idx); }
	}; // end reverse_iterator class
	// Non-member function overloads
	template <class Iter>
  	bool operator== (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iter>
  	bool operator!= (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Iter>
  	bool operator<  (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iter>
  	bool operator<=  (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iter>
	bool operator>  (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class Iter>
	bool operator>=  (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iter>
	ReverseIterator<Iter> operator+ (typename ReverseIterator<Iter>::difference_type off, const ReverseIterator<Iter>& rev_it)
	{
		return ReverseIterator<Iter>(rev_it - off);
	}
	template <class Iter>
	typename ReverseIterator<Iter>::difference_type operator- (const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return lhs.base() - rhs.base();
	}
}; // end namespace ft
#endif
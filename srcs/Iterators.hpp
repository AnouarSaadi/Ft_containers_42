#ifndef ITERATORS_HPP
#	define ITERATORS_HPP
#	include <iterator>
#	include <cstddef>
#	include "Vector.hpp"
class Vector;
namespace ft {
	/* iterator */

	template <
				class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&
				>
	class Iterator
	{
	public:
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
	}; // end Iterator

	/* iiterator_traits */
	template <class Iter>
	class iterator_traits
	{
	public:
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
		// typedef typename Iter::iterator_category	iterator_category;
	}; // end class iterator_traits

	template <class T>
	class iterator_traits<T*>
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; //end class iterator_traits<T*>

	template <class T>
	class iterator_traits<const T*>
	{
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; // end iterator_traits<const T*>

	/* reverse_iterator */

	template <class Iter> 
	class reverse_iterator
	{
	public:
		typedef Iter												iterator_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		// typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	
	protected:
		iterator_type _it;

	public:
		// Member functions
		reverse_iterator<Iter>() : _it(nullptr) {}
		reverse_iterator<Iter>(iterator_type it) : _it(it) {}
		reverse_iterator<Iter>(const reverse_iterator& oth) : _it(oth._it) {}
		iterator_type base() const { return _it; }
		reference operator*() const { return *_it; }
		// +
		reverse_iterator<Iter> operator+(difference_type off) const {
			return reverse_iterator<Iter>(_it - off);
		}
		reverse_iterator<Iter> & operator++() {
			_it--;
			return *this;
		}
		reverse_iterator<Iter> operator++(int) {
			reverse_iterator<Iter> tmp(*this);
			--*this;
			return tmp;
		}
		reverse_iterator<Iter>& operator+=(difference_type off) {
			_it -= off;
			return *this;
		}
		// -
		reverse_iterator<Iter> operator-(difference_type off) const {
			return reverse_iterator<Iter>(this->_it + off);
		}
		reverse_iterator<Iter> & operator--() {
			_it++;
			return *this;
		}
		reverse_iterator<Iter> operator--(int) {
			reverse_iterator<Iter> temp(*this);
			++*this;
			return temp;
		}
		reverse_iterator<Iter>& operator-=(difference_type off) {
			_it += off;
			return *this;
		}
		// ->
		pointer operator->() const { return _it; }
		// []
		reference operator[](typename reverse_iterator<Iter>::difference_type idx) const {
			return *(*this + idx);
		}
	};
	// Non-member function overloads
	template <class Iter>
  		bool operator==(const reverse_iterator<Iter>& lhs,
		  	const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iter>
  		bool operator!=(const reverse_iterator<Iter>& lhs,
		  	const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <class Iter>
  		bool operator<(const reverse_iterator<Iter>& lhs,
		  	const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	template <class Iter>
  		bool operator<=(const reverse_iterator<Iter>& lhs,
		  	const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template <class Iter>
		bool operator>(const reverse_iterator<Iter>& lhs,
			const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	template <class Iter>
		bool operator>=(const reverse_iterator<Iter>& lhs,
			const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	template <class Iter>
		reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type off,
			const reverse_iterator<Iter>& rev_it)
	{
		return reverse_iterator<Iter>(rev_it - off);
	}
	template <class Iter>
		typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs,
			const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() - rhs.base();
	}

}; // end namespace ft
#endif
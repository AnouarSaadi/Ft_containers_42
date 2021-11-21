#ifndef ITERATORS_HPP
# define ITERATORS_HPP
// #	include <iterator>
// #	include <cstddef>
# include "Vector.hpp"
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
	class iterator
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
		typedef typename Iter::iterator_category	iterator_category;
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
	class reverse_iterator : public iterator<typename iterator_traits<Iter>::iterator_category,
												typename iterator_traits<Iter>::value_type,
												typename iterator_traits<Iter>::difference_type,
												typename iterator_traits<Iter>::pointer,
												typename iterator_traits<Iter>::reference
												>
	{
	public:
		typedef Iter												iterator_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;	
	protected:
		iterator_type _it;
	public:
		/* Member functions */
		reverse_iterator() : _it()
		{
		}
		reverse_iterator(iterator_type x) : _it(x)
		{
		}
		template <class OthIter>
			reverse_iterator (const reverse_iterator<OthIter>& rev_it) : _it(rev_it.base())
		{
		}
		iterator_type base() const
		{
			return _it;
		}
		reference operator*() const
		{
			iterator_type copy = _it.base();
			--copy;
			return *copy;
		}
		// +
		reverse_iterator operator+(difference_type off) const
		{
			return reverse_iterator(_it - off);
		}
		reverse_iterator & operator++()
		{
			_it--;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--_it;
			return tmp;
		}
		reverse_iterator & operator+=(difference_type off)
		{
			_it -= off;
			return *this;
		}
		// -
		reverse_iterator operator-(difference_type off) const
		{
			return reverse_iterator(_it + off);
		}
		reverse_iterator & operator--()
		{
			_it++;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++_it;
			return tmp;
		}
		reverse_iterator& operator-=(difference_type off)
		{
			_it += off;
			return *this;
		}
		// ->
		pointer operator->() const
		{
			return &(operator*());
		}
		// []
		reference operator[](difference_type idx) const
		{
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
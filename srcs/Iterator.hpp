#ifndef ITERATOR_HPP
# define ITERATOR_HPP
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
	}; // end Iterator class

	/* iterator_traits */
	template <class Iter>
		class iterator_traits
	{
	public:
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
	}; // end iterator_traits class

	template <class T>
	class iterator_traits<T*>
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; //end iterator_traits<T*> class

	template <class T>
	class iterator_traits<const T*>
	{
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; // end iterator_traits<const T*> class

/* vector iterator eith category of random_access_iterator_tag */
	template <class Iter>
	class vector_iter : public iterator<std::random_access_iterator_tag,
									typename iterator_traits<Iter>::value_type
									>
	{
	public:
    	typedef Iter	                                                   	iterator_type;
    	typedef typename iterator_traits<Iter>::difference_type				difference_type;
    	typedef typename iterator_traits<Iter>::pointer						pointer;
    	typedef typename iterator_traits<Iter>::reference					reference;
	private:
		iterator_type _it;
	public:
		/****** Member functions ******/
		vector_iter() : _it(iterator_type())
		{
		} // default constructor
		vector_iter(iterator_type x) : _it(x)
		{
		} // param constructor
		template <class OthIter>
			vector_iter(const vector_iter<OthIter>& other) : _it(other._it)
		{
		} // copy constructor
		/* assignment operator */
		template <class OthIter>
			vector_iter& operator=(const vector_iter<OthIter>& other)
		{
			this->_it = other.base();
			return (*this);
		}
		~vector_iter()
		{
		} // destructor
		/* operator * */
		reference operator*() const
		{
			return *this->_it;
		}
		/* operator -> */
		pointer operator->() const
		{
			return &(operator*());
		}
		/* operator += ++ */
		vector_iter operator+(difference_type off) const
		{
			return vector_iter(this->_it + off);
		}
		vector_iter & operator+= (difference_type off)
		{
			this->_it += off;
			return (*this);
		}
		vector_iter & operator++()
		{
			++(this->_it);
			return (*this);
		}
		vector_iter operator++(int)
		{
			vector_iter tmp = *this;
			++(this->_it);
			return (tmp);
		}
		/* operator -= -- */
		vector_iter operator-(difference_type off) const
		{
			return vector_iter(this->_it - off);
		}
		vector_iter & operator-= (difference_type off)
		{
			this->_it -= off;
			return (*this);
		}
		vector_iter & operator--()
		{
			--this->_it;
			return (*this);
		}
		vector_iter operator--(int)
		{
			vector_iter tmp = *this;
			--this->_it;
			return (tmp);
		}
		
		/* operator [] */
		reference operator[] (difference_type idx) const
		{
			return *(*this + idx);
		}
		/* base() */
		iterator_type base() const
		{
			return (this->_it);
		}
		}; // end vector_iter class

	/****** Non-member function overloads ******/
	/*  operator == */
	template <class Iter>
  	bool operator==(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	/* operator != */
	template <class Iter>
  	bool operator!=(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return !(lhs == rhs);
	}
	/* operator + */
	template <class Iter>
	vector_iter<Iter> operator+(typename vector_iter<Iter>::difference_type n, const vector_iter<Iter>& _it)
	{
		return vector_iter<Iter>(_it + n);
	}
	/* operator - */
	template <class Iter>
	typename vector_iter<Iter>::difference_type operator-(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	/* operator < */
	template <class Iter>
	bool operator<(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	/* operator > */
	template <class Iter>
	bool operator>(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	/* operator <= */
	template <class Iter>
	bool operator<=(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return !(lhs > rhs);
	}
	/* operator>= */
	template <class Iter>
	bool operator>=(const vector_iter<Iter>& lhs, const vector_iter<Iter>& rhs)
	{
		return !(lhs < rhs);
	}
	
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
			reverse_iterator(const reverse_iterator<OthIter>& rev_it) : _it(rev_it.base())
		{
		}
		iterator_type base() const
		{
			return _it;
		}
		reference operator*() const
		{
			iterator_type cp = _it;
			--cp;
			return *cp;
		}
		// +
		reverse_iterator operator+(difference_type off) const
		{
			return reverse_iterator(_it - off);
		}
		reverse_iterator & operator++()
		{
			_it--;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_it;
			return tmp;
		}
		reverse_iterator & operator+=(difference_type off)
		{
			_it -= off;
			return (*this);
		}
		// -
		reverse_iterator operator-(difference_type off) const
		{
			return reverse_iterator(_it + off);
		}
		reverse_iterator & operator--()
		{
			_it++;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_it;
			return tmp;
		}
		reverse_iterator& operator-=(difference_type off)
		{
			_it += off;
			return (*this);
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
	}; // end reverse_iterator class
	/* Non-member function overloads */
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
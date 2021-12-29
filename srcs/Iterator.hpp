#ifndef ITERATOR_HPP
# define ITERATOR_HPP

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
		iterator_type _current;
	public:
		/*		Member functions		*/
		vector_iter() : _current(nullptr)
		{
		} // default constructor
		vector_iter(iterator_type x) : _current(x)
		{
		} // param constructor
		template <class OthIter>
			vector_iter(const vector_iter<OthIter>& other) : _current(other.base())
		{
		} // copy constructor
		/* assignment operator */
		template <class OthIter>
			vector_iter& operator=(const vector_iter<OthIter>& other)
		{
			this->_current = other.base();
			return (*this);
		}
		~vector_iter()
		{
		} // destructor
		/* operator * */
		reference operator*() const
		{
			return *this->_current;
		}
		/* operator -> */
		pointer operator->() const
		{
			return &(operator*());
		}
		/* operator += ++ */
		vector_iter operator+(difference_type off) const
		{
			return vector_iter(this->_current + off);
		}
		vector_iter & operator+= (difference_type off)
		{
			this->_current += off;
			return (*this);
		}
		vector_iter & operator++()
		{
			++(this->_current);
			return (*this);
		}
		vector_iter operator++(int)
		{
			vector_iter _tmp = *this;
			++(this->_current);
			return (_tmp);
		}
		/* operator -= -- */
		vector_iter operator-(difference_type off) const
		{
			return vector_iter(this->_current - off);
		}
		vector_iter & operator-= (difference_type off)
		{
			this->_current -= off;
			return (*this);
		}
		vector_iter & operator--()
		{
			--this->_current;
			return (*this);
		}
		vector_iter operator--(int)
		{
			vector_iter _tmp = *this;
			--this->_current;
			return (_tmp);
		}
		
		/* operator [] */
		reference operator[] (difference_type idx) const
		{
			return *(*this + idx);
		}
		/* base() */
		iterator_type base() const
		{
			return (this->_current);
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
	vector_iter<Iter> operator+(typename vector_iter<Iter>::difference_type n, const vector_iter<Iter>& _current)
	{
		return vector_iter<Iter>(_current + n);
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
		iterator_type _current;
	public:
		/* Member functions */
		reverse_iterator() : _current(nullptr)
		{
		}
		reverse_iterator(iterator_type x) : _current(x)
		{
		}
		template <class OthIter>
			reverse_iterator(const reverse_iterator<OthIter>& rev_it) : _current(rev_it.base())
		{
		}
		iterator_type base() const
		{
			return _current;
		}
		reference operator*() const
		{
			iterator_type _cp = _current;
			--_cp;
			return *_cp;
		}
		// +
		reverse_iterator operator+(difference_type off) const
		{
			return reverse_iterator(_current - off);
		}
		reverse_iterator & operator++()
		{
			_current--;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator _tmp = *this;
			--_current;
			return _tmp;
		}
		reverse_iterator & operator+=(difference_type off)
		{
			_current -= off;
			return (*this);
		}
		// -
		reverse_iterator operator-(difference_type off) const
		{
			return reverse_iterator(_current + off);
		}
		reverse_iterator & operator--()
		{
			_current++;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator _tmp = *this;
			++_current;
			return _tmp;
		}
		reverse_iterator& operator-=(difference_type off)
		{
			_current += off;
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
#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
	/* Iterator base class */
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
	};

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
	};

	template <class T>
	class iterator_traits<T*>
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};
	template <class Iter>
	class vector_iterator : public iterator<std::random_access_iterator_tag,
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
		vector_iterator() : _current(nullptr)
		{
		}
		vector_iterator(iterator_type x) : _current(x)
		{
		}
		template <class OthIter>
			vector_iterator(const vector_iterator<OthIter>& other) : _current(other.base())
		{
		}
		template <class OthIter>
		vector_iterator& operator=(const vector_iterator<OthIter>& other)
		{
			this->_current = other.base();
			return (*this);
		}
		~vector_iterator()
		{
		}
		
		reference operator*() const
		{
			return *this->_current;
		}
		
		pointer operator->() const
		{
			return &(operator*());
		}
		
		vector_iterator operator+(difference_type _off) const
		{
			return vector_iterator(this->_current + _off);
		}
		vector_iterator & operator+= (difference_type _off)
		{
			this->_current += _off;
			return (*this);
		}
		vector_iterator & operator++()
		{
			++(this->_current);
			return (*this);
		}
		vector_iterator operator++(int)
		{
			vector_iterator _tmp = *this;
			++(this->_current);
			return (_tmp);
		}
		
		vector_iterator operator-(difference_type _off) const
		{
			return vector_iterator(this->_current - _off);
		}
		vector_iterator & operator-= (difference_type _off)
		{
			this->_current -= _off;
			return (*this);
		}
		vector_iterator & operator--()
		{
			--this->_current;
			return (*this);
		}
		vector_iterator operator--(int)
		{
			vector_iterator _tmp(*this);
			--this->_current;
			return (_tmp);
		}
		
		reference operator[] (difference_type _idx) const
		{
			return *(*this + _idx);
		}
		
		iterator_type base() const
		{
			return (this->_current);
		}
	};

	template <class Iter>
  	bool operator==(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return _lhs.base() == _rhs.base();
	}
	template <class Iter>
  	bool operator!=(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return !(_lhs == _rhs);
	}
	template <class Iter>
	vector_iterator<Iter> operator+(typename vector_iterator<Iter>::difference_type n, const vector_iterator<Iter>& _current)
	{
		return vector_iterator<Iter>(_current + n);
	}
	template <class Iter>
	typename vector_iterator<Iter>::difference_type operator-(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return _lhs.base() - _rhs.base();
	}
	template <class Iter>
	bool operator<(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return _lhs.base() < _rhs.base();
	}
	template <class Iter>
	bool operator>(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return _lhs.base() > _rhs.base();
	}
	template <class Iter>
	bool operator<=(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return !(_lhs > _rhs);
	}
	template <class Iter>
	bool operator>=(const vector_iterator<Iter>& _lhs, const vector_iterator<Iter>& _rhs)
	{
		return !(_lhs < _rhs);
	}

	/* reverse iterator class */
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
		reverse_iterator operator+(difference_type _n) const
		{
			return reverse_iterator(_current - _n);
		}
		reverse_iterator & operator++()
		{
			--_current;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator _tmp(*this);
			--_current;
			return _tmp;
		}
		reverse_iterator & operator+=(difference_type _n)
		{
			_current -= _n;
			return (*this);
		}
		reverse_iterator operator-(difference_type _n) const
		{
			return reverse_iterator(_current + _n);
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
		reverse_iterator& operator-=(difference_type _n)
		{
			_current += _n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type _idx) const
		{
			return *(*this + _idx);
		}
	};

	template <class Iter>
  		bool operator==(const reverse_iterator<Iter>& _lhs,
		  	const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() == _rhs.base();
	}
	template <class Iter>
  		bool operator!=(const reverse_iterator<Iter>& _lhs,
		  	const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() != _rhs.base();
	}
	template <class Iter>
  		bool operator<(const reverse_iterator<Iter>& _lhs,
		  	const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() > _rhs.base();
	}
	template <class Iter>
  		bool operator<=(const reverse_iterator<Iter>& _lhs,
		  	const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() >= _rhs.base();
	}
	template <class Iter>
		bool operator>(const reverse_iterator<Iter>& _lhs,
			const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() < _rhs.base();
	}
	template <class Iter>
		bool operator>=(const reverse_iterator<Iter>& _lhs,
			const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() <= _rhs.base();
	}
	template <class Iter>
		reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type _n,
			const reverse_iterator<Iter>& rev_it)
	{
		return reverse_iterator<Iter>(rev_it - _n);
	}
	template <class Iter>
		typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& _lhs,
			const reverse_iterator<Iter>& _rhs)
	{
		return _lhs.base() - _rhs.base();
	}
	
};
#endif
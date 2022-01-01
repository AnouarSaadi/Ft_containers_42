#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "Iterator.hpp"
#include "Algorithm.hpp"
#include "Type_traits.hpp"
#include <algorithm>

namespace ft
{
	/*************************** vector: Template class *********************/
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef typename Alloc::reference	reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer	pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		typedef vector_iterator<pointer>	iterator;
		typedef vector_iterator<const_pointer>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t	size_type;

	private:
		pointer _data;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

	public:
		/* default */
		vector(const allocator_type &_alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
		{
		}
		/* fill */
		vector(size_type _n, const value_type &_val = value_type(),
			   const allocator_type &_alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
		{
			this->assign(_n, _val);
		}
		/* range */
		template <class InputIterator>
		vector(InputIterator _first, InputIterator _last,
			   const allocator_type &_alloc = allocator_type(),
			   typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
		{
			this->assign(_first, _last);
		}
		/* copy */
		vector(const vector &_v) : _data(nullptr), _size(0),
								   _capacity(0), _alloc(_v._alloc)
		{
			*this = _v;
		}

		/* Destructor */
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_data, this->capacity());
			this->_capacity = 0;
		}
		/* assign operator */
		vector &operator=(const vector &_v)
		{
			if (this != &_v)
			{
				this->clear();
				this->_alloc.deallocate(this->_data, this->capacity());
				this->_alloc = _v._alloc;
				this->_size = _v.size();
				this->_capacity = _v.capacity();
				this->_data = _alloc.allocate(_v.capacity());
				for (size_type _i = 0; _i < _v.size(); _i++)
					this->_alloc.construct(&this->_data[_i], _v._data[_i]);
			}
			return (*this);
		}
		
		/* begin */
		iterator begin()
		{
			return (iterator(this->_data));
		}
		const_iterator begin() const
		{
			return (const_iterator(this->_data));
		}
		/* end */
		iterator end()
		{
			return (iterator(this->_data + this->_size));
		}
		const_iterator end() const
		{
			return (const_iterator(this->_data + this->_size));
		}
		/* rbegin */
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}
		/* rend */
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}
		
		/* size */
		size_type size() const
		{
			return (this->_size);
		}
		/* max size */
		size_type max_size() const
		{
			return (std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max()));
		}
		/* resize */
		void resize(size_type _n, value_type _val = value_type())
		{
			size_type _sz = size();
			if (_sz > _n)
			{
				for (size_type _i = _n - 1; _i < _sz; _i++)
					this->_alloc.destroy(&this->_data[_i]);
				this->_size = _n;
			}
			else if (_sz < _n)
			{
				this->reserve(_n);
				this->_size = _n;
				for (size_type _i = _sz; _i < _n; _i++)
					this->_alloc.construct(&this->_data[_i], _val);
			}
		}
		/* capacity */
		size_type capacity() const
		{
			return (this->_capacity);
		}
		/* empty */
		bool empty() const
		{
			return (this->_size == 0);
		}
		/* reserve */
		void reserve(size_type _n)
		{
			if (_n > this->_capacity)
			{
				size_type capacity = this->_capacity;
				this->_capacity = (this->_capacity * 2 >= _n) ? this->_capacity * 2 : _n;
				pointer _save_data = this->_alloc.allocate(this->_capacity);
				for (size_type _i = 0; _i < size(); _i++)
					this->_alloc.construct(&_save_data[_i], this->_data[_i]);
				if (this->_size)
					this->_alloc.destroy(this->_data);
				if (this->_capacity)
					this->_alloc.deallocate(this->_data, capacity);
				this->_data = _save_data;
			}
		}
		
		/* operator [] */
		reference operator[](size_type _idx)
		{
			return (this->_data[_idx]);
		}
		/* at */
		reference at(size_type _n)
		{
			if (_size - _n < 0)
				throw std::out_of_range("vector");
			return (this->_data[_n]);
		}
		const_reference at(size_type _n) const
		{
			return (this->_data[_n]);
		}
		/* front */
		reference front()
		{
			return *(this->_data);
		}
		const_reference front() const
		{
			return *(this->_data);
		}
		/* back */
		reference back()
		{
			return (this->_data[this->_size - 1]);
		}
		const_reference back() const
		{
			return (this->_data[this->_size - 1]);
		}
		/*********************** Modifiers **********************/
		/* assign */
		/* fill */
		void assign(size_type _n, const value_type &_val)
		{
			if (_n <= 0)
				return;
			this->reserve(_n);
			this->_size = _n;
			for (size_type _i = 0; _i < _n; ++_i)
				this->_alloc.construct(&this->_data[_i], _val);
		}
		/* range */
		template <class InputIterator>
		void assign(InputIterator _first, InputIterator _last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			difference_type _rngLen = _last - _first;
			if (_rngLen <= 0)
				return;
			this->reserve(_rngLen);
			this->_size = _rngLen;
			size_type _i = 0;
			for (InputIterator it = _first; it != _last; ++it)
				this->_alloc.construct(&this->_data[_i++], *it);
		}
		/* push_back */
		void push_back(const value_type &_val)
		{
			this->reserve(this->_size + 1);
			this->_alloc.construct(&this->_data[this->_size++], _val);
		}
		/* pop_back */
		void pop_back()
		{
			this->_alloc.destroy(&this->_data[this->_size - 1]);
			this->_size--;
		}

		/* insert */
		iterator insert(iterator position, const value_type &_val)
		{
			difference_type _idx = position - begin();
			if (_idx < 0)
				throw std::out_of_range("vector");
			this->reserve(this->_size + 1);
			this->_size += 1;
			difference_type _i = size();
			while (--_i >= 0)
			{
				if (_i == _idx)
				{
					this->_alloc.construct(&this->_data[_i], _val);
					break;
				}
				this->_alloc.construct(&this->_data[_i], this->_data[_i - 1]);
			}
			return (iterator(this->_data + _idx));
		}
		void insert(iterator position, size_type _n, const value_type &_val)
		{
			if (_n <= 0)
				return;
			difference_type _idx = position - begin();
			if (_idx < 0)
				return;
			this->reserve(size() + _n);
			this->_size += _n;
			difference_type _i = size();
			while (--_i >= 0)
			{
				if (_i == (_idx + (difference_type)_n) - 1)
				{
					_alloc.construct(&this->_data[_i], _val);
					_n--;
				}
				else
					_alloc.construct(&this->_data[_i], this->_data[_i - _n]);
				if (_i == _idx)
					break;
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator _first, InputIterator _last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			difference_type _idx = position - begin();
			difference_type _rngLen = _last - _first;
			if (_rngLen <= 0)
				return;
			this->reserve(size() + _rngLen);
			this->_size += _rngLen;
			difference_type _i = size();
			while (--_i >= 0)
			{
				if (_i == _idx + _rngLen - 1)
				{
					_alloc.construct(&_data[_i], *--_last);
					_rngLen--;
				}
				else
					_alloc.construct(&_data[_i], _data[_i - _rngLen]);
				if (_i == _idx)
					break;
			}
		}
		/* erase */
		iterator erase(iterator position)
		{
			difference_type _idx = position - begin();
			if (_idx < 0)
				throw std::out_of_range("vector");
			size_type _i = 0, _j = 0;
			while (_i < size())
			{
				if (_i == (size_type)_idx)
					_alloc.destroy(&_data[_i++]);
				_alloc.construct(&_data[_j++], _data[_i]);
				_i++;
			}
			_size--;
			return (iterator(this->_data + _idx));
		}
		iterator erase(iterator _first, iterator _last)
		{
			difference_type _idx = _first - begin();
			if ((_last - _first) <= 0)
				throw std::out_of_range("vector");
			size_type _rngLen = 0;
			size_type _i = 0, _j = 0;
			while (_i < size())
			{
				if (_i == (size_type)_idx)
				{
					for (; _first != _last; _first++)
					{
						this->_alloc.destroy(&this->_data[_i++]);
						_rngLen++;
					}
				}
				this->_alloc.construct(&this->_data[_j++], this->_data[_i++]);
			}
			this->_size -= _rngLen;
			return (iterator(this->_data + _idx));
		}
		/* swap */
		void swap(vector &_v)
		{
			std::swap(this->_data, _v._data);
			std::swap(this->_size, _v._size);
			std::swap(this->_capacity, _v._capacity);
			std::swap(this->_alloc, _v._alloc);
		}
		/* clear */
		void clear()
		{
			if (!this->empty())
			{
				for (size_type _i = 0; _i < this->size(); _i++)
					this->_alloc.destroy(&this->_data[_i]);
				this->_size = 0;
			}
		}
		/* get_allocator */
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
	}; // end vector class

	/*  FX Non-member function overloads  */
	/* operator == */
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs.size() == lhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	/* operator != */
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	/* operator < */
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	/* operator > */
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	/* operator <= */
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
	/* operator >= */
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	/* non-member swap */
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &_x, vector<T, Alloc> &_y)
	{
		_x.swap(_y);
	}
}; // end namspace ft
#endif

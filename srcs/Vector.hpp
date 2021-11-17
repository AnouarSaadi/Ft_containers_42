
#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include <iostream>
# include "Iterators.hpp"
# include "Utils.hpp"

class Iterator;
// vector
namespace ft {
	template <class Vector>
		class WrapIter
		{ 
		public:
    		typedef Vector                                                    iterator_type;
    		typedef typename iterator_traits<iterator_type>::value_type        value_type;
    		typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    		typedef typename iterator_traits<iterator_type>::pointer           pointer;
    		typedef typename iterator_traits<iterator_type>::reference         reference;
    		// typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		
		private:
			pointer m_Ptr;

		public:
			/* ######## FX Member functions ######## */
			WrapIter<Vector>() {} // constructor
			WrapIter<Vector>(const pointer ptr) : m_Ptr(ptr) {} // param constructor
			WrapIter<Vector>(const WrapIter& other) { this->m_Ptr = other.m_Ptr; return; } // copy constructor
			WrapIter<Vector>& operator=(const WrapIter& other) { this->m_Ptr = other.m_Ptr; return *this; }// assignment operator
			~WrapIter<Vector>() {}; // destructor
			// operator *
			reference operator*() const { return *m_Ptr; }
			// ->
			pointer operator->() const { return m_Ptr; }

			// +
			WrapIter<Vector> operator+(difference_type off) { return WrapIter(m_Ptr + off); }
			WrapIter<Vector>& operator+= (difference_type off) {
				m_Ptr += off;
				return *this;
			}
			WrapIter<Vector> & operator++() {
				m_Ptr++;
				return *this;
			}
			WrapIter<Vector> operator++(int) {
				WrapIter<Vector> tmp(*this);
				++*this;
				return tmp;
			}

			// -
			WrapIter<Vector> operator-(difference_type off) { return WrapIter(m_Ptr - off); }
			WrapIter<Vector>& operator-= (difference_type off) {
				m_Ptr -= off;
				return *this;
			}
			WrapIter<Vector>& operator--() {
				m_Ptr--;
				return *this;
			}
			WrapIter<Vector> operator--(int) {
				WrapIter<Vector> tmp(*this);
				--*this;
				return tmp;
			}
			
			// []
			reference operator[] (difference_type idx) const { return *(m_Ptr + idx); }

			// base()
			pointer base() const { return m_Ptr; }
			
		}; // end WrapIter class
	// Non-member function overloads
	// operator ==
	template <class Vector>
  	bool operator==(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	// operator !=
	template <class Vector>
  	bool operator!=(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs)
	{
		return !(lhs == rhs);
	}
	// operator +
	template <class Vector>
	WrapIter<Vector> operator+(typename WrapIter<Vector>::difference_type n, const WrapIter<Vector>& _it)
	{
		return WrapIter<Vector>(_it + n);
	}
	// operator -
	template <class Vector>
	typename WrapIter<Vector>::difference_type operator-(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	// operator <
	template <class Vector>
	bool operator<(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs) { return lhs.base() < rhs.base(); }
	// operator >
	template <class Vector>
	bool operator>(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs) { return lhs.base() > rhs.base(); }
	// operator <=
	template <class Vector>
	bool operator<=(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs) { return !(lhs > rhs); }
	// operator>=
	template <class Vector>
	bool operator>=(const WrapIter<Vector>& lhs, const WrapIter<Vector>& rhs) { return !(lhs < rhs); }
	
	// vector Class
	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef typename Alloc::reference						reference;
			typedef typename Alloc::const_reference					const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef typename Alloc::const_pointer					const_pointer;
			typedef WrapIter< vector<T> > 							iterator;
			typedef WrapIter< const vector<T> >						const_iterator;
			typedef reverse_iterator< const_iterator >				const_reverse_iterator;
			typedef reverse_iterator< iterator >					reverse_iterator;
		
		private:
			pointer			_vecData;
			size_type		_vecSize;
			size_type		_vecCapacity;
			allocator_type	_vecAlloc;

		public:
			/*********************** Coplien form **********************/
			// default
			vector(const allocator_type& alloc = allocator_type()) :
				_vecData(NULL), _vecSize(0), _vecCapacity(0), _vecAlloc(alloc)
			{
			}
			// fill
			vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
					_vecData(NULL) , _vecSize(n), _vecAlloc(alloc)
			{
				_vecData = _vecAlloc.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					this->_vecAlloc.construct(&this->_vecData[i], val);
				}
				_vecCapacity = _vecSize;
			}
			// range
			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
						typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) :
						_vecData(NULL), _vecSize(0), _vecAlloc(alloc)
			{
				int size = 0;
				for (InputIterator it = first; it != last; ++it)
					size++;
				_vecSize = size;
				_vecCapacity = size;
				_vecData = _vecAlloc.allocate(size);
				for (size_type i = 0; i < _vecSize && first != last;)
						this->_vecAlloc.construct(&this->_vecData[i++], *first++);
			}
			// copy
			vector(const vector& x)  : _vecData(NULL), _vecSize(0),
				_vecCapacity(0) , _vecAlloc(x._vecAlloc)
			{
				*this = x;
			}

			// Destructor
			~vector()
			{
				this->clear();
			}
			// assign operator
			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					this->clear();
					this->_vecAlloc = x._vecAlloc;
					this->_vecSize = x.size();
					this->_vecCapacity = x.capacity();
					this->_vecData = _vecAlloc.allocate(x.size());
					for (size_type i = 0; i < x.size(); i++)
					{
						this->_vecAlloc.construct(&this->_vecData[i], x._vecData[i]);
					}
				}
				return *this;
			}

			/*********************** Iterators **********************/
			// begin
			iterator begin()
			{
				return iterator(_vecData);
			}
			const_iterator begin() const
			{
				return _vecData;
			}
			// end
			iterator end()
			{
				return iterator(_vecData + size());
			}
			const_iterator end() const
			{
				return const_iterator(_vecData + size());
			}
			// rbegin
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			// rend
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			/*********************** Capacity **********************/
			// size
			size_type size() const
			{
				 return _vecSize;
			}
			// max size
			size_type max_size() const
			{
				return _vecAlloc.max_size();
			}
			// resize
			void resize(size_type n, value_type val = value_type())
			{
				if (!empty()) 
					this->clear();
				_vecSize = n;
				_vecCapacity = _vecSize;
				_vecData = _vecAlloc.allocate(n);
				this->assign(n, val);
			}
			// capacity
			size_type capacity() const
			{
				return _vecCapacity;
			}
			// empty
			bool empty() const
			{
				return size() == 0;
			}
			// reserve
			void reserve(size_type n)
			{
				pointer arr = this->_vecAlloc.allocate(size());
				for (size_type i = 0; i < size(); i++)
					this->_vecAlloc.construct(&arr[i], _vecData[i]);
				// std::cout << "Debugging... Reserve " << n << std::endl;
				if (!empty())
				{
					this->_vecAlloc.destroy(this->_vecData);
					this->_vecAlloc.deallocate(this->_vecData, this->size());
				}
				this->_vecData = this->_vecAlloc.allocate(n);
				if (n > this->capacity())
					this->_vecCapacity = (this->_vecCapacity * 2 >= n) ? this->_vecCapacity * 2 : n;
				for (size_type i = 0; i < size(); i++)
				{
					this->_vecAlloc.construct(&this->_vecData[i], arr[i]);
				}
				this->_vecAlloc.destroy(arr);
				this->_vecAlloc.deallocate(arr, n);
			}

			/*********************** Element access **********************/
			// operator []
			reference operator[](size_type idx)
			{
				return _vecData[idx];
			}
			// at
			reference at(size_type n)
			{
				return _vecData[n];
			}
			const_reference at (size_type n) const
			{
				return _vecData[n];
			}
			// front
			reference front()
			{
				return _vecData[0];
			}
			const_reference front() const
			{
				return _vecData[0];
			}
			// back
			reference back()
			{
				return _vecData[size() - 1];
			}
			const_reference back() const
			{
				return _vecData[size() - 1];
			}
			/*********************** Modifiers **********************/
			// assign
				// fill
			void assign(size_type n, const value_type& val)
			{
				if (!n)
					return ;
				this->reserve(n);
				_vecSize = n;
				for (size_type i = 0; i < n; ++i)
					this->_vecAlloc.construct(&this->_vecData[i], val);
			}
				// range
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				size_type lenRange = 0;
				for (InputIterator it = first; it != last; ++it)
					lenRange++;
				if (!lenRange)
					return ;
				this->reserve(lenRange);
				_vecSize = lenRange;
				size_type i = 0;
				for (InputIterator it = first; it != last; ++it)
					this->_vecAlloc.construct(&this->_vecData[i++], *it);
			}
			// push_back
			void push_back (const value_type& val)
			{
				this->reserve(this->size() + 1);
				this->_vecAlloc.construct(&this->_vecData[this->_vecSize++], val);
			}
			// pop_back
			void pop_back()
			{
				this->_vecAlloc.destroy(&this->_vecData[size() - 1]);
				_vecSize--;
			}
			// insert
				// single element
			iterator insert(iterator position, const value_type& val)
			{
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == position)
						break ;
					idx++;
				}
				reserve(size() + 1);
				_vecSize++;
				size_type i = size();
				for (; i >= 0; i--)
				{
					if(i == idx)
					{
						this->_vecAlloc.construct(&this->_vecData[i], val);
						break ;
					}
					this->_vecAlloc.construct(&this->_vecData[i], _vecData[i - 1]);
				}

				return iterator(_vecData + idx);
			}
				// fill
			void insert(iterator position, size_type n, const value_type& val)
			{
				if (!n) return;
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == position)
						break ;
					idx++;
				}
				reserve(size() + n);
				_vecSize += n;
				size_type i = size();
				for (;i >= 0; --i)
				{
					if (i == (idx + n) - 1)
					{
						for (; i >= idx; i--)
						{
							this->_vecAlloc.construct(&_vecData[i], val);
						}
						break ;
					}
					this->_vecAlloc.construct(&_vecData[i], _vecData[i - n]);
				}
			}
				// range
			template <class InputIterator>
    			void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				{
					size_type idx = 0;
					for (iterator iter = begin(); iter != end(); ++iter)
					{
						if (iter == position)
							break ;
						idx++;
					}
					size_type lenRange = 0;
					for (InputIterator it = first; it != last; ++it)
						lenRange++;
					if (!lenRange) return;
					reserve(size() + lenRange);
					_vecSize += lenRange;
					size_type i = size();
					for (;i >= 0; i--)
					{
						if (i == (idx + lenRange) - 1)
						{
							for (;i >= idx ; i--)
								this->_vecAlloc.construct(&_vecData[i], *--last);
							break ;
						}
						this->_vecAlloc.construct(&_vecData[i], _vecData[i - lenRange]);
					}
				}
			// erase
			iterator erase(iterator position)
			{
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == position)
						break ;
					idx++;
				}
				size_type i = 0, j = 0;
				for (;i < size(); i++)
				{
					if (i == idx)
					{
						this->_vecAlloc.destroy(&_vecData[idx]);
						i++;
					}
					this->_vecAlloc.construct(&_vecData[j++], _vecData[i]);
				}
				_vecSize--;
				return iterator(_vecData + idx);
			}
			iterator erase(iterator first, iterator last)
			{
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == first)
						break ;
					idx++;
				}
				size_type rangeSize = 0;
				size_type i = 0, j = 0;
				for (; i < size(); i++)
				{
					if (i == idx)
					{
						for (;first != last; first++)
						{
							this->_vecAlloc.destroy(&_vecData[i++]);
							rangeSize++;
						}
					}
					this->_vecAlloc.construct(&_vecData[j++], _vecData[i]);
				}
				_vecSize -=rangeSize;
				return iterator(_vecData + idx);
			}
			// swap
			void swap(vector& x)
			{
				vector<value_type> vecSwap = *this;
				*this = x;
				x = vecSwap;
			}
			// clear
			void clear() {
				if (!this->empty())
				{
					_vecAlloc.destroy(this->_vecData);
					_vecAlloc.deallocate(this->_vecData, this->size());
					_vecSize = 0;
					_vecCapacity = 0;
				}
			}
			/*********************** Allocator **********************/
			allocator_type get_allocator() const { return _vecAlloc; }
		}; // end vector class
		/* ######## FX Non-member function overloads ######## */
		// operator ==
		template <class T, class Alloc>
  			bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return rhs.size() == lhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		// operator !=
		template <class T, class Alloc>
  			bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}
		// operator <
		template <class T, class Alloc>
  			bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		// operator >
		template <class T, class Alloc>
  			bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}
		// operator <=
		template <class T, class Alloc>
  			bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs < rhs);
		}
		// operator >=
		template <class T, class Alloc>
  			bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}
		// swap
		template <class T, class Alloc>
  			void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}; // end namspace ft
#endif
 
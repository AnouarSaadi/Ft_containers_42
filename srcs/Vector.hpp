#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include "Iterator.hpp"
# include "Algorithm.hpp"
# include "Type_traits.hpp"

	/*************************** vector: Template class *********************/
namespace ft
{
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
			typedef vector_iter<pointer> 							iterator;
			typedef vector_iter<const_pointer>						const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			pointer			_vecData;
			size_type		_vecSize;
			size_type		_vecCapacity;
			allocator_type	_vecAlloc;
		public:
			/*********************** Coplien form **********************/
			/* default */
			vector(const allocator_type& alloc = allocator_type()) :
				_vecData(nullptr), _vecSize(0), _vecCapacity(0), _vecAlloc(alloc)
			{
			}
			/* fill */
			vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
					_vecData(nullptr) , _vecSize(0), _vecCapacity(0),_vecAlloc(alloc)
			{
				if (!n)
					return ;
				this->assign(n, val);
			}
			/* range */
		 	template <class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
						typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) :
						_vecData(nullptr), _vecSize(0), _vecCapacity(0), _vecAlloc(alloc)
			{
				if (first == last)
					return ;
				this->assign(first, last);
			}
			/* copy */
			vector(const vector& x)  : _vecData(nullptr), _vecSize(0),
				_vecCapacity(0) , _vecAlloc(x._vecAlloc)
			{
				*this = x;
			}

			/* Destructor */
			~vector()
			{
				this->clear();
				this->_vecAlloc.deallocate(this->_vecData, this->capacity());
				this->_vecCapacity = 0;
			}
			/* assign operator */
			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					this->clear();
					this->_vecAlloc.deallocate(this->_vecData, this->capacity());
					this->_vecAlloc = x._vecAlloc;
					this->_vecSize = x.size();
					this->_vecCapacity = x.capacity();
					this->_vecData = _vecAlloc.allocate(x.size());
					for (size_type i = 0; i < x.size(); i++)
						this->_vecAlloc.construct(&this->_vecData[i], x._vecData[i]);
				}
				return (*this);
			}
			/*********************** Iterators **********************/
			/* begin */
			iterator begin()
			{
				return (iterator(this->_vecData));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->_vecData));
			}
			/* end */
			iterator end()
			{
				return (iterator(this->_vecData + this->_vecSize));
			}
			const_iterator end() const
			{
				return (const_iterator(this->_vecData + this->_vecSize));
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
			/*********************** Capacity **********************/
			/* size */
			size_type size() const
			{
				 return (this->_vecSize);
			}
			/* max size */
			size_type max_size() const
			{
				return (this->_vecAlloc.max_size());
			}
			/* resize */
			void resize(size_type n, value_type val = value_type())
			{
				size_type _sz = size();
				if (_sz > n)
				{
					for (size_type i = n; i < _sz; i++)
						this->_vecAlloc.destroy(&this->_vecData[i]);
					this->_vecSize = n;
				}
				else if (_sz < n)
				{
					this->reserve(n);
					this->_vecSize = n;
					for (size_type i = _sz; i < n; i++)
						this->_vecAlloc.construct(&this->_vecData[i], val);
				}
			}
			/* capacity */
			size_type capacity() const
			{
				return (this->_vecCapacity);
			}
			/* empty */
			bool empty() const
			{
				return (this->size() == 0);
			}
			/* reserve */
			void reserve(size_type n) // ! use capacity is allocation
			{
				pointer _data = this->_vecAlloc.allocate(this->size());
				for (size_type i = 0; i < size(); i++)
					this->_vecAlloc.construct(&_data[i], _vecData[i]);
				if (!this->empty())
				{
					this->_vecAlloc.destroy(this->_vecData);
					this->_vecAlloc.deallocate(this->_vecData, this->capacity());
				}
				this->_vecData = this->_vecAlloc.allocate(n);
				if (n > this->capacity())
					this->_vecCapacity = (this->_vecCapacity * 2 >= n) ? this->_vecCapacity * 2 : n;
				for (size_type i = 0; i < size(); i++)
				{
					this->_vecAlloc.construct(&this->_vecData[i], _data[i]);
				}
				this->_vecAlloc.destroy(_data);
				this->_vecAlloc.deallocate(_data, n);
			}
			/*********************** Element access **********************/
			/* operator [] */
			reference operator[](size_type idx)
			{
				return (this->_vecData[idx]);
			}
			/* at */
			reference at(size_type n)
			{
				return (this->_vecData[n]);
			}
			const_reference at (size_type n) const
			{
				return (this->_vecData[n]);
			}
			/* front */
			reference front()
			{
				return (this->_vecData[0]);
			}
			const_reference front() const
			{
				return (this->_vecData[0]);
			}
			/* back */
			reference back()
			{
				return (this->_vecData[this->_vecSize - 1]);
			}
			const_reference back() const
			{
				return (this->_vecData[this->_vecSize - 1]);
			}
			/*********************** Modifiers **********************/
			/* assign */
				/* fill */
			void assign(size_type n, const value_type& val)
			{
				if (!n)
					return ;
				this->reserve(n);
				this->_vecSize = n;
				for (size_type i = 0; i < n; ++i)
					this->_vecAlloc.construct(&this->_vecData[i], val);
			}
				/* range */
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				if (first == last)
					return ;
				size_type rngLen = 0;
				for (InputIterator it = first; it != last; ++it)
					rngLen++;
				this->reserve(rngLen);
				this->_vecSize = rngLen;
				size_type i = 0;
				for (InputIterator it = first; it != last; ++it)
					this->_vecAlloc.construct(&this->_vecData[i++], *it);
			}
			/* push_back */
			void push_back (const value_type& val)
			{
				this->reserve(this->size() + 1);
				this->_vecAlloc.construct(&this->_vecData[this->_vecSize++], val);
			}
			/* pop_back */
			void pop_back()
			{
				this->_vecAlloc.destroy(&this->_vecData[size() - 1]);
				this->_vecSize--;
			}
			/* insert */
				/* single element */
			iterator insert(iterator position, const value_type& val)
			{
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == position)
						break ;
					idx++;
				}
				this->reserve(this->_vecSize + 1);
				this->_vecSize++;
				size_type i = size();
				for (; i >= 0; i--)
				{
					if(i == idx)
					{
						this->_vecAlloc.construct(&this->_vecData[i], val);
						break ;
					}
					this->_vecAlloc.construct(&this->_vecData[i], this->_vecData[i - 1]);
				}

				return (iterator(this->_vecData + idx));
			}
				/* fill */
			void insert(iterator position, size_type n, const value_type& val)
			{
				if (!n)
					return;
				size_type idx = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter == position)
						break ;
					idx++;
				}
				this->reserve(size() + n);
				this->_vecSize += n;
				size_type i = size();
				for (;i >= 0; --i)
				{
					if (i == (idx + n) - 1)
					{
						for (; i >= idx; i--)
						{
							this->_vecAlloc.construct(&this->_vecData[i], val);
						}
						break ;
					}
					this->_vecAlloc.construct(&this->_vecData[i], this->_vecData[i - n]);
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
					size_type rngLen = 0;
					for (InputIterator it = first; it != last; ++it)
						rngLen++;
					if (!rngLen) return;
					this->reserve(size() + rngLen);
					this->_vecSize += rngLen;
					size_type i = size();
					for (;i >= 0; i--)
					{
						if (i == (idx + rngLen) - 1)
						{
							for (;i >= idx ; i--)
								this->_vecAlloc.construct(&this->_vecData[i], *--last);
							break ;
						}
						this->_vecAlloc.construct(&this->_vecData[i], this->_vecData[i - rngLen]);
					}
				}
			/* erase */
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
						this->_vecAlloc.destroy(&this->_vecData[idx]);
						i++;
					}
					this->_vecAlloc.construct(&this->_vecData[j++], this->_vecData[i]);
				}
				this->_vecSize--;
				return (iterator(this->_vecData + idx));
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
				size_type rngLen = 0;
				size_type i = 0, j = 0;
				for (; i < size(); i++)
				{
					if (i == idx)
					{
						for (;first != last; first++)
						{
							this->_vecAlloc.destroy(&this->_vecData[i++]);
							rngLen++;
						}
					}
					this->_vecAlloc.construct(&this->_vecData[j++], this->_vecData[i]);
				}
				this->_vecSize -=rngLen;
				return (iterator(this->_vecData + idx));
			}
			/* swap */
			void swap(vector& x)
			{
				std::swap(this->_vecData, x._vecData);
				std::swap(this->_vecSize, x._vecSize);
				std::swap(this->_vecCapacity, x._vecCapacity);
				std::swap(this->_vecAlloc, x._vecAlloc);
			}
			/* clear */
			void clear()
			{
				if (!this->empty())
				{
					for (size_type i = 0; i < this->size(); i++)
						this->_vecAlloc.destroy(&this->_vecData[i]);
					this->_vecSize = 0;
				}
			}
			/*********************** Allocator **********************/
			allocator_type get_allocator() const
			{
				return (this->_vecAlloc);
			}
		}; // end vector class
		/* ######## FX Non-member function overloads ######## */
		/* operator == */
		template <class T, class Alloc>
  			bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return rhs.size() == lhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		/* operator != */
		template <class T, class Alloc>
  			bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}
		/* operator < */
		template <class T, class Alloc>
  			bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		/* operator > */
		template <class T, class Alloc>
  			bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}
		/* operator <= */
		template <class T, class Alloc>
  			bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs < rhs);
		}
		/* operator >= */
		template <class T, class Alloc>
  			bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}
		/* swap */
		template <class T, class Alloc>
  			void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}; // end namspace ft
#endif
 
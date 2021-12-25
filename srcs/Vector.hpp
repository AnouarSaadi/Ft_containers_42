#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
# include "Iterator.hpp"
# include "Algorithm.hpp"
# include "Type_traits.hpp"
# include <vector> //

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
			pointer			_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
		public:
			/*********************** Coplien form **********************/
			/* default */
			vector(const allocator_type& alloc = allocator_type()) :
				_data(nullptr), _size(0), _capacity(0), _alloc(alloc)
			{
			}
			/* fill */
			vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
					_data(nullptr) , _size(0), _capacity(0),_alloc(alloc)
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
						_data(nullptr), _size(0), _capacity(0), _alloc(alloc)
			{
				if (first == last)
					return ;
				this->assign(first, last);
			}
			/* copy */
			vector(const vector& _x)  : _data(nullptr), _size(0),
				_capacity(0) , _alloc(_x._alloc)
			{
				*this = _x;
			}

			/* Destructor */
			~vector()
			{
				this->clear();
				this->_alloc.deallocate(this->_data, this->capacity());
				this->_capacity = 0;
			}
			/* assign operator */
			vector& operator=(const vector& _x)
			{
				if (this != &_x)
				{
					this->clear();
					this->_alloc.deallocate(this->_data, this->capacity());
					this->_alloc = _x._alloc;
					this->_size = _x.size();
					this->_capacity = _x.capacity();
					this->_data = _alloc.allocate(_x.size());
					for (size_type i = 0; i < _x.size(); i++)
						this->_alloc.construct(&this->_data[i], _x._data[i]);
				}
				return (*this);
			}
			/*********************** Iterators **********************/
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
			/*********************** Capacity **********************/
			/* size */
			size_type size() const
			{
				 return (this->_size);
			}
			/* max size */
			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}
			/* resize */
			void resize(size_type n, value_type val = value_type())
			{
				size_type _sz = size();
				if (_sz > n)
				{
					for (size_type i = n; i < _sz; i++)
						this->_alloc.destroy(&this->_data[i]);
					this->_size = n;
				}
				else if (_sz < n)
				{
					this->reserve(n);
					this->_size = n;
					for (size_type i = _sz; i < n; i++)
						this->_alloc.construct(&this->_data[i], val);
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
				return (this->size() == 0);
			}
			/* reserve */
			void reserve(size_type n) // ! use capacity is allocation
			{
				if (n > this->capacity())
				{
					size_type capacity = this->_capacity;
					this->_capacity = (this->_capacity * 2 >= n) ? this->_capacity * 2 : n;
					pointer data = this->_alloc.allocate(capacity);
					for (size_type i = 0; i < size(); i++)
						this->_alloc.construct(&data[i], this->_data[i]);
					if (!this->empty())
					{
						this->_alloc.destroy(this->_data);
						this->_alloc.deallocate(this->_data, this->capacity());
					}
					this->_data = this->_alloc.allocate(_capacity);
					for (size_type i = 0; i < size(); i++)
					{
						this->_alloc.construct(&this->_data[i], data[i]);
					}
					this->_alloc.destroy(data);
					this->_alloc.deallocate(data, capacity);
				}
			}
			/*********************** Element access **********************/
			/* operator [] */
			reference operator[](size_type idx)
			{
				return (this->_data[idx]);
			}
			/* at */
			reference at(size_type n)
			{
				return (this->_data[n]);
			}
			const_reference at (size_type n) const
			{
				return (this->_data[n]);
			}
			/* front */
			reference front()
			{
				return (this->_data[0]);
			}
			const_reference front() const
			{
				return (this->_data[0]);
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
			void assign(size_type n, const value_type& val)
			{
				if (!n)
					return ;
				this->reserve(n);
				this->_size = n;
				for (size_type i = 0; i < n; ++i)
					this->_alloc.construct(&this->_data[i], val);
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
				this->_size = rngLen;
				size_type i = 0;
				for (InputIterator it = first; it != last; ++it)
					this->_alloc.construct(&this->_data[i++], *it);
			}
			/* push_back */
			void push_back (const value_type& val)
			{
				this->reserve(this->size() + 1);
				this->_alloc.construct(&this->_data[this->_size++], val);
			}
			/* pop_back */
			void pop_back()
			{
				this->_alloc.destroy(&this->_data[size() - 1]);
				this->_size--;
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
				this->reserve(this->_size + 1);
				this->_size++;
				size_type i = size();
				for (; i >= 0; i--)
				{
					if(i == idx)
					{
						this->_alloc.construct(&this->_data[i], val);
						break ;
					}
					this->_alloc.construct(&this->_data[i], this->_data[i - 1]);
				}

				return (iterator(this->_data + idx));
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
				this->_size += n;
				size_type i = size();
				for (;i >= 0; --i)
				{
					if (i == (idx + n) - 1)
					{
						for (; i >= idx; i--)
						{
							this->_alloc.construct(&this->_data[i], val);
						}
						break ;
					}
					this->_alloc.construct(&this->_data[i], this->_data[i - n]);
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
					this->_size += rngLen;
					size_type i = size();
					for (;i >= 0; i--)
					{
						if (i == (idx + rngLen) - 1)
						{
							for (;i >= idx ; i--)
								this->_alloc.construct(&this->_data[i], *--last);
							break ;
						}
						this->_alloc.construct(&this->_data[i], this->_data[i - rngLen]);
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
						this->_alloc.destroy(&this->_data[idx]);
						i++;
					}
					this->_alloc.construct(&this->_data[j++], this->_data[i]);
				}
				this->_size--;
				return (iterator(this->_data + idx));
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
							this->_alloc.destroy(&this->_data[i++]);
							rngLen++;
						}
					}
					this->_alloc.construct(&this->_data[j++], this->_data[i]);
				}
				this->_size -=rngLen;
				return (iterator(this->_data + idx));
			}
			/* swap */
			void swap(vector& _x)
			{
				std::swap(this->_data, _x._data);
				std::swap(this->_size, _x._size);
				std::swap(this->_capacity, _x._capacity);
				std::swap(this->_alloc, _x._alloc);
			}
			/* clear */
			void clear()
			{
				if (!this->empty())
				{
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(&this->_data[i]);
					this->_size = 0;
				}
			}
			/*********************** Allocator **********************/
			allocator_type get_allocator() const
			{
				return (this->_alloc);
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
  			void swap(vector<T,Alloc>& _x, vector<T,Alloc>& y)
		{
			_x.swap(y);
		}
}; // end namspace ft
#endif
 
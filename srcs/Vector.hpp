
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
			pointer			vecData;
			size_type		vecSize;
			size_type		vecCapacity;
			allocator_type	vecAlloc;

		public:
			/*********************** Coplien form **********************/
			// default
			vector(const allocator_type& alloc = allocator_type()) :
				vecData(NULL), vecSize(0), vecCapacity(0), vecAlloc(alloc)
			{
			}
			// fill
			vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
					vecData(NULL) , vecSize(n), vecAlloc(alloc)
			{
				vecData = vecAlloc.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					this->vecAlloc.construct(&this->vecData[i], val);
				}
				vecCapacity = vecSize;
			}
			// range
			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
						typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) :
						vecData(NULL), vecSize(0), vecAlloc(alloc)
			{
				int size = 0;
				for (InputIterator it = first; it != last; ++it)
					size++;
				vecSize = size;
				vecCapacity = size;
				vecData = vecAlloc.allocate(size);
				for (size_type i = 0; i < vecSize && first != last;)
						this->vecAlloc.construct(&this->vecData[i++], *first++);
			}
			// copy
			vector(const vector& x)  : vecData(NULL), vecSize(0),
				vecCapacity(0) , vecAlloc(x.vecAlloc)
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
					this->vecAlloc = x.vecAlloc;
					this->vecSize = x.size();
					this->vecCapacity = x.capacity();
					this->vecData = vecAlloc.allocate(x.size());
					for (size_type i = 0; i < x.size(); i++)
					{
						this->vecAlloc.construct(&this->vecData[i], x.vecData[i]);
					}
				}
				return *this;
			}

			/*********************** Iterators **********************/
			// begin
			iterator begin()
			{
				return iterator(vecData);
			}
			const_iterator begin() const
			{
				return vecData;
			}
			// end
			iterator end()
			{
				return vecData + size();
			}
			const_iterator end() const
			{
				return vecData + size();
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
				 return vecSize;
			}
			// max size
			size_type max_size() const
			{
				return vecAlloc.max_size();
			}
			// resize
			void resize(size_type n, value_type val = value_type())
			{
				if (!empty()) 
					this->clear();
				vecSize = n;
				vecCapacity = vecSize;
				vecData = vecAlloc.allocate(n);
				this->assign(n, val);
			}
			// capacity
			size_type capacity() const
			{
				return vecCapacity;
			}
			// empty
			bool empty() const
			{
				return size() == 0;
			}
			// reserve
			void reserve(size_type n)
			{
				pointer arr = this->vecAlloc.allocate(size());
				for (size_type i = 0; i < size(); i++)
					this->vecAlloc.construct(&arr[i], vecData[i]);
				std::cout << "Debugging... Reserve " << n << std::endl;
				if (!empty())
				{
					this->vecAlloc.destroy(this->vecData);
					this->vecAlloc.deallocate(this->vecData, this->size());
				}
				this->vecData = this->vecAlloc.allocate(n);
				if (n > this->capacity())
					this->vecCapacity = (this->vecCapacity * 2 >= n) ? this->vecCapacity * 2 : n;
				for (size_type i = 0; i < size(); i++)
				{
					this->vecAlloc.construct(&this->vecData[i], arr[i]);
				}
				this->vecAlloc.destroy(arr);
				this->vecAlloc.deallocate(arr, n);
			}

			/*********************** Element access **********************/
			// operator []
			reference operator[](size_type idx)
			{
				return vecData[idx];
			}
			// at
			reference at(size_type n)
			{
				return vecData[n];
			}
			const_reference at (size_type n) const
			{
				return vecData[n];
			}
			// front
			reference front()
			{
				return vecData[0];
			}
			const_reference front() const
			{
				return vecData[0];
			}
			// back
			reference back()
			{
				return vecData[size() - 1];
			}
			const_reference back() const
			{
				return vecData[size() - 1];
			}
			/*********************** Modifiers **********************/
			// assign
				// fill
			void assign(size_type n, const value_type& val)
			{
				this->reserve(n);
				this->vecSize = n;
				for (size_type i = 0; i < n; ++i)
					this->vecAlloc.construct(&this->vecData[i], val);
			}
				// range
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				size_type sizeRange = 0;
				for (InputIterator it = first; it != last; ++it)
					sizeRange++;
				this->reserve(sizeRange);
				this->vecSize = sizeRange;
				int i = 0;
				for (InputIterator it = first; it != last; ++it)
					this->vecAlloc.construct(&this->vecData[i++], *it);
			}
			// push_back
			void push_back (const value_type& val)
			{
				this->reserve(this->size() + 1);
				this->vecAlloc.construct(&this->vecData[this->vecSize++], val);
			}
			// pop_back
			void pop_back()
			{
				this->vecAlloc.destroy(&this->vecData[size() - 1]);
				vecSize--;
			}
			// insert
				// single element
			iterator insert(iterator position, const value_type& val)
			{
				std::cout << "debugging... " << size() << std::endl;
				std::cout << "__begin  " << *(begin() + 2) << " " << *position << std::endl;
				reserve(size() + 1);
				std::cout << "__begin  " << *(begin() + 2) << " " << *position << std::endl;
				vecSize++;
				size_type i = size() - 1;
				for (iterator it = end() - 1; it != begin(); it--)
				{
					std::cout << "debugging... " << *it << "  " << *position << std::endl;
					if(it == position)
					{
						this->vecAlloc.construct(&this->vecData[i], val);
						break ;
					}
					else
						this->vecAlloc.construct(&this->vecData[i], vecData[i - 1]);
					i--;
				}
				// *this = tmp;
				return position.base();
			}
				// fill
			void insert(iterator position, size_type n, const value_type& val)
			{
				vector<value_type> tmp(*this);
				tmp.reserve(tmp.size());
				tmp.vecSize = tmp.size() + n;
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); i < tmp.size(); it++)
				{
					if (it == position)
					{
						for (size_type k = i; k < i + n; ++k) {
							this->vecAlloc.construct(&tmp.vecData[k], val);
						}
						i += n;
					}
					else
						this->vecAlloc.construct(&tmp.vecData[i++], this->vecData[j++]);
				}
				*this = tmp;
			}
				// range
			template <class InputIterator>
    			void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				{
					vector<value_type> tmp(*this);
					size_type sizeRange = 0;
					for (InputIterator it = first; it != last; ++it) { sizeRange++; }
					tmp.reserve(this->size() + sizeRange);
					tmp.vecSize = this->size() + sizeRange;
					size_type i = 0, j = 0;
					for (iterator it = this->begin(); i < tmp.size(); ++it)
					{
						if (it == position)
						{
							for (;first != last; ++first)
								this->vecAlloc.construct(&tmp.vecData[i++], *first);
						}
						else
							this->vecAlloc.construct(&tmp.vecData[i++], this->vecData[j++]);
					}
					*this = tmp;
				}
			// erase
			iterator erase(iterator position)
			{
				vector<value_type> tmp(*this);
				iterator itRet;
				tmp.reserve(tmp.vecSize - 1);
				tmp.vecSize = tmp.vecSize - 1;
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (it == position)
					{
						j++;
						itRet = it + 1;
					}
					else
						this->vecAlloc.construct(&tmp.vecData[i++], this->vecData[j++]);
				}
				*this = tmp;
				return itRet.base();
			}
			iterator erase(iterator first, iterator last)
			{
				vector<value_type> tmp(*this);
				iterator itRet;
				size_type rangeSize = 0;
				for(iterator it = first; it != last; ++it) { rangeSize++; }
				tmp.reserve(tmp.size() - rangeSize);
				tmp.vecSize = tmp.size() - rangeSize;
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (it == first)
					{
						for (;first != last; first++)
						{
							j++;
							it++;
						}
						itRet = last;
					}
					this->vecAlloc.construct(&tmp.vecData[i++], this->vecData[j++]);
				}
				*this = tmp;
				return itRet.base();
			}
			// swap
			void swap(vector& x)
			{
				vector<value_type> tmp = *this;
				*this = x;
				x = tmp;
			}
			// clear
			void clear() {
				if (!this->empty())
				{
					vecAlloc.destroy(this->vecData);
					vecAlloc.deallocate(this->vecData, this->size());
					vecSize = 0;
					vecCapacity = 0;
				}
			}
			/*********************** Allocator **********************/
			allocator_type get_allocator() const { return vecAlloc; }
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
 
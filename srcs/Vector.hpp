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
		class VectorIterator : public Iterator<std::random_access_iterator_tag,
			std::random_access_iterator_tag>
		{ 
		public:
    		typedef Vector                                                    iterator_type;
    		typedef typename IteratorTraits<iterator_type>::value_type        value_type;
    		typedef typename IteratorTraits<iterator_type>::difference_type   difference_type;
    		typedef typename IteratorTraits<iterator_type>::pointer           pointer;
    		typedef typename IteratorTraits<iterator_type>::reference         reference;
		
		private:
			pointer m_Ptr;

		public:
			// Member functions
			VectorIterator<Vector>() {} // constructor
			VectorIterator<Vector>(const pointer ptr) : m_Ptr(ptr) {} // param constructor
			VectorIterator<Vector>(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return; } // copy constructor
			VectorIterator<Vector>& operator=(const VectorIterator& other) { this->m_Ptr = other.m_Ptr; return *this; }// assignment operator
			~VectorIterator<Vector>() {}; // destructor
			// operator *
			reference operator*() const { return *m_Ptr; }
			// ->
			pointer operator->() const { return m_Ptr; }

			// +
			VectorIterator<Vector> operator+(difference_type off) { return VectorIterator(m_Ptr + off); }
			VectorIterator<Vector>& operator+= (difference_type off) {
				m_Ptr += off;
				return *this;
			}
			VectorIterator<Vector> & operator++() {
				m_Ptr++;
				return *this;
			}
			VectorIterator<Vector> operator++(int) {
				VectorIterator<Vector> tmp(*this);
				++*this;
				return tmp;
			}

			// -
			VectorIterator<Vector> operator-(difference_type off) { return VectorIterator(m_Ptr - off); }
			VectorIterator<Vector>& operator-= (difference_type off) {
				m_Ptr -= off;
				return *this;
			}
			VectorIterator<Vector>& operator--() {
				m_Ptr--;
				return *this;
			}
			VectorIterator<Vector> operator--(int) {
				VectorIterator<Vector> tmp(*this);
				--*this;
				return tmp;
			}
			
			// []
			reference operator[] (difference_type idx) const { return *(m_Ptr + idx); }

			// base()
			pointer base() const { return m_Ptr; }
			
		}; // end VectorIterator class
	// Non-member function overloads
	// operator ==
	template <class Vector>
  	bool operator== (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	// operator !=
	template <class Vector>
  	bool operator!= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return !(lhs == rhs);
	}
	// operator +
	template <class Vector>
	VectorIterator<Vector> operator+ (typename VectorIterator<Vector>::difference_type n, const VectorIterator<Vector>& _it)
	{
		return VectorIterator<Vector>(_it + n);
	}
	// operator -
	template <class Vector>
	typename VectorIterator<Vector>::difference_type operator- (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	// operator <
	template <class Vector>
	bool operator< (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() < rhs.base(); }
	// operator >
	template <class Vector>
	bool operator> (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return lhs.base() > rhs.base(); }
	// operator <=
	template <class Vector>
	bool operator<= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return !(lhs > rhs); }
	// operator>=
	template <class Vector>
	bool operator>= (const VectorIterator<Vector>& lhs, const VectorIterator<Vector>& rhs) { return !(lhs < rhs); }
	
	// Vector Class
	template < class T, class Alloc = std::allocator<T> >
		class Vector
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
			typedef typename ft::VectorIterator< Vector<T> > 		iterator;
			typedef typename ft::VectorIterator< const Vector<T> >	const_iterator;
			typedef typename ft::ReverseIterator< iterator >		reverse_iterator;
			typedef typename ft::ReverseIterator< const_iterator >	const_reverse_iterator;
		
		private:
			pointer			vecData;
			size_type		vecSize;
			size_type		vecCapacity;
			allocator_type	vecAllocator;

		public:
			/*********************** Coplien form **********************/
			// default
			Vector(const allocator_type& alloc = allocator_type()) :
				vecData(nullptr), vecSize(0), vecAllocator(alloc)
			{
				vecData = nullptr;
				vecSize = 0;
				vecCapacity = 0;
			}
			// fill
			Vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
					vecData(nullptr) , vecSize(n), vecAllocator(alloc)
			{
				vecData = vecAllocator.allocate(n);
				this->assign(n, val);
				vecCapacity = vecSize;
			}
			// range
			template <class InputIterator>
				Vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
						typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) :
						vecData(nullptr), vecSize(0), vecAllocator(alloc)
			{
				int size = 0;
				for (InputIterator it = first; it != last; ++it) { size++; }
				vecSize = size;
				vecCapacity = size;
				vecData = vecAllocator.allocate(size);
				this->assign(first, last);
			}
			// copy
			Vector(const Vector& x)  : vecData(nullptr), vecSize(0),
				vecCapacity(0) , vecAllocator(x.vecAllocator)
			{
				*this = x;
			}

			// Destructor
			~Vector()
			{
				this->clear();
			}
			// assign operator
			Vector& operator = (const Vector& x)
			{
				if (this != &x)
				{
					this->clear();
					this->vecAllocator = x.vecAllocator;
					this->vecSize = x.size();
					this->vecCapacity = x.capacity();
					this->vecData = vecAllocator.allocate(x.size());
					for (size_type i = 0; i < x.size(); i++) { this->vecData[i] = x.vecData[i]; }
				}
				return *this;
			}

			/*********************** Iterators **********************/
			// begin
			iterator begin() { return vecData; }
			const_iterator begin() const { return vecData; }

			// end
			iterator end() { return vecData + size(); }
			const_iterator end() const { return vecData + size(); }

			// rbegin
			reverse_iterator rbegin() { return end(); };
			const_reverse_iterator rbegin() const { return end(); };

			// rend
			reverse_iterator rend() { return begin(); };
			const_reverse_iterator rend() const { return begin(); };

			/*********************** Capacity **********************/
			// size
			size_type size() const { return vecSize; }
			// max size
			size_type max_size() const { return vecAllocator.max_size(); }
			// resize
			void resize (size_type n, value_type val = value_type())
			{
				if (this->size())  this->clear();
				vecSize = n;
				vecCapacity = vecSize;
				vecData = vecAllocator.allocate(n);
				this->assign(n, val);
			}
			// capacity
			size_type capacity() const { return vecCapacity; }
			// empty
			bool empty() const { return vecSize > 0 ? false : true; }
			// reserve
			void reserve (size_type n)
			{
				ft::Vector<value_type> tmp;
				tmp.vecData = tmp.vecAllocator.allocate(n);
				tmp.vecCapacity = this->capacity();
				if (n > tmp.vecCapacity)
					tmp.vecCapacity = (tmp.vecCapacity * 2 >= n) ? tmp.vecCapacity * 2 : n;
				tmp.vecAllocator.construct(tmp.vecData, n);
				for (size_type i = 0; i < this->size(); i++) { tmp.vecData[i] = this->vecData[i]; }
				tmp.vecSize = this->size();
				*this = tmp;
			}

			/*********************** Element access **********************/
			// operator []
			reference operator[] (size_type idx) { return vecData[idx]; }

			// at
			reference at (size_type n) { return vecData[n]; }
			const_reference at (size_type n) const { return vecData[n]; }

			// front
			reference front() { return vecData[0];}
			const_reference front() const { return vecData[0];}

			// back
			reference back() { return vecData[size() - 1]; }
			const_reference back() const { return vecData[size() - 1]; }

			/*********************** Modifiers **********************/

			// assign
				// fill
			void assign (size_type n, const value_type& val)
			{
				// reserve space
				for (size_type i = 0; i < n; ++i)
					vecData[i] = val;
			}
				// range
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				{
					// reserve space
					int i = 0;
					for (InputIterator it = first; it != last; ++it) { vecData[i++] = *it; }
				}
			// push_back
			void push_back (const value_type& val)
			{
				this->reserve(this->size() + 1);
				this->vecData[this->vecSize++] = val;
			}
			// pop_back
			void pop_back()
			{
				this->vecAllocator.destroy(&this->vecData[size() - 1]);
				this->vecSize -= 1;
			}
			// insert
				// single element
			iterator insert (iterator position, const value_type& val)
			{
				ft::Vector<value_type> tmp(*this);
				tmp.vecSize = this->vecSize + 1;
				tmp.reserve(tmp.size());
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); i < tmp.size(); it++) {
					tmp.vecData[i++] = (it == position) ? val : this->vecData[j++];
				}
				*this = tmp;
				return position.base();
			}
				// fill
			void insert (iterator position, size_type n, const value_type& val)
			{
				ft::Vector<value_type> tmp(*this);
				// tmp.vecCapacity = this->capacity();
				tmp.vecSize = tmp.size() + n;
				tmp.reserve(tmp.size());
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); i < tmp.size(); it++)
				{
					if (it == position)
					{
						for (size_type k = i; k < i + n; ++k) { tmp.vecData[k] = val; }
						i += n;
					}
					else
						tmp.vecData[i++] = this->vecData[j++];
				}
				*this = tmp;
			}
				// range
			template <class InputIterator>
    			void insert (iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				{
					ft::Vector<value_type> tmp(*this);
					size_type sizeRange = 0;
					for (InputIterator it = first; it != last; ++it) { sizeRange++; }
					tmp.vecSize = this->size() + sizeRange;
					tmp.reserve(tmp.size());
					size_type i = 0, j = 0;
					for (iterator it = this->begin(); i < tmp.size(); ++it)
					{
						if (it == position) {
							for (;first != last; ++first) { tmp.vecData[i++] = *first; }
						}
						else
							tmp.vecData[i++] = this->vecData[j++];
					}
					*this = tmp;
				}
			// erase
			iterator erase (iterator position)
			{
				ft::Vector<value_type> tmp(*this);
				iterator itRet;
				tmp.reserve(tmp.vecSize - 1);
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (it == position)
					{
						tmp.vecSize--;
						j++;
						itRet = it + 1;
					}
					else
						tmp.vecData[i++] = this->vecData[j++];
				}
				*this = tmp;
				return itRet.base();
			}
			iterator erase (iterator first, iterator last)
			{
				ft::Vector<value_type> tmp(*this);
				iterator itRet;
				size_type RangeSize = 0;
				for(iterator it = first; it != last; ++it) { RangeSize++; }
				tmp.reserve(tmp.size() - RangeSize);
				size_type i = 0, j = 0;
				for (iterator it = this->begin(); it != this->end(); ++it)
				{
					if (it == first)
					{
						for (;first != last; first++)
						{
							j++;
							it++;
							tmp.vecSize--;
						}
						itRet = last;
					}
					tmp.vecData[i++] = this->vecData[j++];
				}
				*this = tmp;
				return itRet.base();
			}
			// swap
			void swap (vector& x) { }
			// clear
			void clear() {
				if (!empty())
				{
					vecAllocator.destroy(this->vecData);
					vecAllocator.deallocate(this->vecData, this->size());
					vecSize = 0;
					vecCapacity = 0;
				}
			}
		}; // end vector class
}; // end namspace ft
#endif
 
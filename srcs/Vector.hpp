#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // std::allocator
#	include <iostream>
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
				vecData = vecAllocator.allocator();
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
				//assign
				this->assign(first, last);
				(void)last; (void)first;
			}
			// copy
			Vector(const Vector& x) { *this = x; }

			// Destructor
			~Vector()
			{
				vecAllocator.destroy(vecData);
				vecSize = 0;
				vecCapacity = 0;
			}
			// assign operator
			Vector& operator= (const Vector& x)
			{
				if (this != &x)
				{
					this->vecAllocator = x.vecAllocator;
					this->vecSize = x.size();
					this->vecCapacity = x.Capacity();
					this->vecAllocator.destroy(vecData);
					this->vecData = vecAllocator.allocate(vecCapacity);
					this->vecData.assign(x.begin(), x.end());
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
				vecAllocator.destroy(vecData);
				vecSize = n;
				vecCapacity = vecSize;
				vecData = vecAllocator.allocate(n);
				this->assign(n, val);
			}
			// capacity
			size_type capacity() const { return vecCapacity; }
			// empty
			bool empty() const { return !vecSize ? true : false; }
			// reserve
			void reserve (size_type n)
			{
				pointer tmp;
				tmp = vecAllocator.allocate(n);
				tmp.assign(vecData, vecData + size());
				vecAllocator.destroy(vecData);
				vecSize = n;
				vecCapacity = vecSize;
				vecData = tmp;
				//vecAllocator.destroy(tmp); 
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
				for (size_type i = 0; i < n; ++i)
					vecData[i] = val;
			}
				// range
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				{
					int i = 0;
					for (InputIterator it = first; it != last; ++it)
						vecData[i++] = *it;
				}
			// push_back
			void push_back (const value_type& val)
			{
				if (this->size() >= this->capacity())
				{
					pointer tmp;
					this->capacity = 2 * this->capacity;
					tmp = vecAllocator.allocate(this->capacity);
					
				}
			}
		}; // end vector class
}; // end namspace ft
#endif
 
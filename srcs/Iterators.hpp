#ifndef ITERATORS_HPP
#	define ITERATORS_HPP

#	include <cstddef>
namespace ft{
	/* iterator */

	template <class Category,
				class T,
				class Distance = ptrdiff_t,
				class Pointer = T*,
				class Reference = T&
				>
	class Iterator
	{
	public:
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
		typedef Category	iterator_category;
	}; // end Iterator

	/* iterator_traits */

	template <class Iterator>
	class IteratorTraits
	{
	public:
		typedef Iterator::value_type		value_type;
		typedef Iterator::pointer			pointer;
		typedef Iterator::reference			reference;
		typedef Iterator::difference_type	difference_type;
		typedef Iterator::iterator_category	iterator_category;
	}; // end class IteratorTraits

	template <class T>
	class IteratorTraits<T*>
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; //end class IteratorTraits<T*>

	template <class T>
	class IteratorTraits<const T*>
	{
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	}; // end IteratorTraits<const T*>

	/* reverse_iterator */

	template <class Iterator> 
	class ReverseIterator
	{
	public:
		typedef Iterator									iterator_type;
		typedef IteratorTraits<Iterator>::value_type		value_type;
		typedef IteratorTraits<Iterator>::pointer			pointer;
		typedef IteratorTraits<Iterator>::reference			reference;
		typedef IteratorTraits<Iterator>::difference_type	difference_type;
		typedef IteratorTraits<Iterator>::iterator_category	iterator_category;
	
	protected:
		iterator_type _it;

	public:
		// Member functions
		ReverseIterator() : _it(nullptr) {}
		ReverseIterator(iterator_type it) : _it(it) {}
		ReverseIterator(const ReverseIterator& oth) : _it(oth._it) {}
		iterator_type base() const { return _it; }
		reference operator*() const { return *_it; }
		// +
		ReverseIterator operator+ (difference_type off) const { return ReverseIterator(_it - off); }
		ReverseIterator & operator++() {
			_it--;
			return *this;
		}
		ReverseIterator operator++(int) {
			ReverseIterator tmp(*this);
			--*this;
			return tmp;
		}
		ReverseIterator& operator+= (difference_type off) {
			_it -= off;
			return *this;
		}
		// -
		ReverseIterator operator- (difference_type off) const { return ReverseIterator(this->_it + off); }
		ReverseIterator & operator--() {
			_it++;
			return *this;
		}
		ReverseIterator operator--(int) {
			ReverseIterator temp(*this);
			++*this;
			return temp;
		}
		ReverseIterator& operator-= (difference_type off) {
			_it += off;
			return *this;
		}
		// ->
		pointer operator->() const { return _it; }
		// []
		reference operator[] (difference_type idx) const { return *(*this + idx); }
	}; // end reverse_iterator class
	// Non-member function overloads
	template <class Iterator>
  	bool operator== (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
  	bool operator!= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Iterator>
  	bool operator<  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
  	bool operator<=  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator>  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator>
	bool operator>=  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	ReverseIterator<Iterator> operator+ (typename ReverseIterator<Iterator>::difference_type off, const ReverseIterator<Iterator>& rev_it)
	{
		return ReverseIterator(rev_it - off);
	}
	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type operator- (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	}
}; // end namespace ft
#endif
#ifndef ITERATORS_HPP
#	define ITERATORS_HPP

#	include <cstddef>

/* iterator */

template <class Category,
			class T,
			class Distance = ptrdiff_t,
			class Pointer = T*,
			class Reference = T&
			>
class Iterator
{
	typedef Category iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
};

/* iterator_traits */

template <class Iterator>
class IteratorTraits
{
	typedef Iterator::difference_type difference_type;
	typedef Iterator::value_type value_type;
	typedef Iterator::pointer pointer;
	typedef Iterator::reference reference;
	typedef Iterator::iterator_category iterator_category;
};

template <class T>
class IteratorTraits<T*>
{
	typedef Iterator::difference_type difference_type;
	typedef Iterator::value_type value_type;
	typedef Iterator::pointer pointer;
	typedef Iterator::reference reference;
	typedef Iterator::iterator_category iterator_category;
};

template <class T>
class IteratorTraits<const T*>
{
	typedef Iterator::difference_type difference_type;
	typedef Iterator::value_type value_type;
	typedef Iterator::pointer pointer;
	typedef Iterator::reference reference;
	typedef Iterator::iterator_category iterator_category;
};

/* reverse_iterator */

template <class Iterator> 
class ReverseIterator
{
	typedef Iterator iterator_type;
	typedef IteratorTraits<Iterator>::iterator_category iterator_category;
	typedef IteratorTraits<Iterator>::value_type value_type;
	typedef IteratorTraits<Iterator>::difference_type difference_type;
	typedef IteratorTraits<Iterator>::pointer pointer;
	typedef IteratorTraits<Iterator>::reference reference;
private:
	iterator_type _it;

public:
	ReverseIterator() : _it(nullptr) {}
	ReverseIterator(iterator_type x) : _it(x) {}
	ReverseIterator(const ReverseIterator& x) : _it(x._it) {}
	iterator_type base() const { return this->_it; }
	reference operator*() const { return *_it; }
	ReverseIterator operator+ (difference_type n) const { return ReverseIterator(this->_it - n); }
	ReverseIterator & operator++() {
		--(this->_it);
		return *this;
	}
	ReverseIterator operator++(int) {
		ReverseIterator tmp(*this);
		--(*this);
		return tmp;
	}
	ReverseIterator& operator+= (difference_type n) {
		this->_it -= n;
		return *this;
	}
	ReverseIterator operator- (difference_type n) const { return ReverseIterator(this->_it + n); }

	ReverseIterator & operator--() {
		++(this->_it);
		return *this;
	}
	ReverseIterator operator--(int) {
		ReverseIterator temp = *this;
		++(*this);
		return temp;
	}

	ReverseIterator& operator-= (difference_type n) {
		this->_it += n;
		return *this;
	}

	pointer operator->() const { return &(operator*()); }

	reference operator[] (difference_type n) const { return(base()[-n -1]); }
};

#endif
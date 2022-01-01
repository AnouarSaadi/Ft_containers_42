#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft {
	// pair template class
	template <class T1, class T2>
	class pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}

		pair (const first_type& _a, const second_type& _b) : first(_a), second(_b) {}

		template<class U, class V>
		pair (const pair<U, V>& _pr): first(_pr.first), second(_pr.second) {}

		pair& operator= (const pair& _pr)
		{
			if (this != &_pr)
			{
				this->first = _pr.first;
				this->second = _pr.second;
			}
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return _lhs.first == _rhs.first && _lhs.second == _rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return !(_lhs == _rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return _lhs.first < _rhs.first || (!(_rhs.first < _lhs.first) && _lhs.second < _rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return !(_rhs < _lhs); 
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return _rhs < _lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& _lhs, const pair<T1,T2>& _rhs)
	{
		return !(_lhs < _rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 _x, T2 _y)
	{
		return pair<T1,T2>(_x, _y);
	}
}

#endif
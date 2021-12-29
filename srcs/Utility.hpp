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

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

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
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs); 
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 _x, T2 _y)
	{
		return pair<T1,T2>(_x, _y);
	}
} // end namespace ft

#endif
#ifndef UTILS_HPP
# define UTILS_HPP

// type_traits

namespace ft {
	// enable_if
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// is_integral
	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};
		//bool
	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};
		// char
	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};
		// wchar_t
	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};
		// char16_t
	template <>
	struct is_integral<char16_t>
	{
		static const bool value = true;
	};
		// char32_t
	template <>
	struct is_integral<char32_t>
	{
		static const bool value = true;
	};
		// signed char
	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};
		// short int
	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};
		// int
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};
		// long int
	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};
		// long long int
	template <>
	struct is_integral<long long int>
	{
		static const bool value = true;
	};
		// unsigned  char
	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
		// unsigned short int
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};
		// unsigned int
	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};
		// unsigned long int
	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};
		// unsigned long long int
	template <>
	struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};

	// equal function
	 // equality
	template <class InputIterator1, class InputIterator2>
		bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}
	 // predicate
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  		bool equal (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1) {
			if (!pred(*first1,*first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

}

#endif
#ifndef MAP_HPP
# define MAP_HPP

#include <map>

# include <functional>
# include <memory>
# include "Utility.hpp"
# include "Tree.hpp"

namespace ft {
	template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                // map::key_compare
			class Alloc = std::allocator< ft::pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		typedef Key key_type;
		typedef T mapped_type;
		typedef typename ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		class value_compare
		{
			Compare _comp;
			value_compare(Compare _c) : _comp(_c) {}
		public:
			typedef bool result_type;
			typedef value_type first_type;
			typedef value_type second_type;
			result_type operator()(const value_type& _x,  const value_type& _y) const
			{
				return (_comp(_x.first, _y.second));
			}
		};
		typedef Alloc allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef typename ft::tree<value_type, key_compare, allocator_type> tree;
		typedef typename tree::iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::reverse_iterator reverse_iterator;
		typedef typename tree::const_reverse_iterator const_reverse_iterator;
		typedef iterator_traits<iterator>::difference_type difference_type;
		typedef typename ft::node<value_type> node;
		typedef node* nodePtr;
		typedef size_t	size_type;

	private:
		tree _tree;
		size_type _size;

	public:
		explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _tree(), _size(0)
		{
		}
		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type()): _tree(), _size(0)
		{
			for (InputIterator it = first; it != last; ++it) // ! need to check
			{
				this->insert(*it);
			}
		}

		map (const map& _m)
		{
			*this = _m;
		}

		map& operator=(const map& _m)
		{
			if (this != &_m)
			{
				this->clear();
				this->_size = _m._size;
				// this->insert(_m.begin(), _m.end());
			}
		}

		bool empty() const
		{
			return _size == 0;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		mapped_type& operator[] (const key_type& k)
		{
			value_type _x = make_pair(k, mapped_type());
			nodePtr _y = this->_tree.find(_x);
			if (_y != this->_tree.getEndNode())
				return _y->_data.second;
			else
			{
				return (*((this->insert(_x)).first)).second // insert must be reimplimented
			}
		}

		void clear()
		{
			if (this->_size)
			{
				this->_tree.clear();
				this->_size = 0;
			}
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			this->_tree.insert(val);
			_size++;
		}

		iterator insert (iterator position, const value_type& val)
		{
			
		}


	};
} // end namespace ft
#endif
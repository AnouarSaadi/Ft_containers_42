#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "Utility.hpp"
# include "Tree.hpp"
# include "Type_traits.hpp"

namespace ft {
	template < class T,
				class Compare = std::less<T>,
				class Alloc = std::allocator<T>
				>
	class set
	{	
	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::tree<value_type, value_compare, allocator_type> tree;
		typedef typename ft::node<value_type> node;
		typedef node* node_pointer;
		typedef tree_iterator<node_pointer, pointer> iterator;
		typedef tree_iterator<node_pointer, const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t	size_type;

	private:
		tree _tree;

		allocator_type _alloc;
		key_compare _comp;

	public:
		explicit set (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc),  _alloc(alloc), _comp(comp)
		{
		}
		template <class InputIterator>
  		set (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type()): _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp)
		{
			this->insert(first, last);
		}
		
		set (const set& _s) : _tree(value_compare(_s._comp), _s._alloc),  _alloc(_s._alloc), _comp(_s._comp)
		{
			*this = _s;
		}

		set& operator=(const set& _s)
		{
			if (this != &_s)
			{
				this->clear();
				this->_alloc = _s._alloc;
				this->_comp = _s._comp;
				this->insert(_s.begin(), _s.end());
			}
			return *this;
		}

		~set()
		{
		}

		iterator begin()
		{
			return iterator(_tree.begin());
		}
		const_iterator begin() const
		{
			return const_iterator(_tree.begin());
		}

		iterator end()
		{
			return iterator(_tree.end());
		}

		const_iterator end() const
		{
			return const_iterator(_tree.end());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}
		
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		bool empty() const
		{
			return size() == 0;
		}

		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size() const
		{
			return (std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max()));
		}

		void clear()
		{
			if (!empty())
				this->_tree.clear();
		}

		pair<iterator,bool> insert (const value_type& _val)
		{
			iterator _f = this->find(_val);
			if (_f == this->end())
			{
				this->_tree.insert(_val);
				_f = this->find(_val);
				return pair<iterator,bool>(_f, true);
			}
			return pair<iterator,bool>(_f, false);
		}

		iterator insert (iterator position, const value_type& _val)
		{
			position = this->find(_val);
			if (position != this->end())
				return (position);
			this->insert(_val);
			return (this->find(_val));
		}
		
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			for (; first != last; ++first)
				this->insert(*first);
		}

		void erase (iterator position)
		{
			if (this->find(*position) != this->end())
				this->_tree.erase(*position);
		}

		size_type erase (const value_type& _val)
		{
			iterator _f = this->find(_val);
			if (_f != this->end())
			{
				this->erase(_f);
				return (1);
			}
			return (0);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		const_iterator find (const value_type& _val) const
		{
			node_pointer _y = this->_tree.find(_val);
			if (_y == nullptr)
				return this->end();
			return const_iterator(_y);
		}

		void swap (set& _s)
		{
			_tree.swap(_s._tree);
			std::swap(this->_comp, _s._comp);
			std::swap(this->_alloc, _s._alloc);
		}

		key_compare key_comp() const
		{
			return this->_comp;
		}

		value_compare value_comp() const
		{
			return this->_comp;
		}

		size_type count (const value_type& _val) const
		{
			return (this->find(_val) != this->end());
		}
		
		const_iterator lower_bound (const value_type& _val) const
		{
			return _tree.lower_bound(_val);
		}

		const_iterator upper_bound (const value_type& _val) const
		{
			return _tree.upper_bound(_val);
		}

		pair<const_iterator,const_iterator> equal_range (const value_type& _val) const
		{
			return pair<const_iterator,const_iterator>(lower_bound(_val), upper_bound(_val));
		}

		allocator_type get_allocator() const
		{
			return  this->_alloc;
		}
	};
}
#endif
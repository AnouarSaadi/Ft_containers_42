#ifndef TREE_HPP
# define TREE_HPP

namespace ft {
	// Tree class
	template <class T, class Compare, class Alloc>
	class Tree
	{
	private:
		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef pointer		value_type*;
		typedef reference	value_type&;
		typedef struct node {
			value_type		key;
			value_type		value;
			struct node		*right;
			struct node		*left;
			struct node		*parent;
		} _Node;

		_Node<value_type> *root;
		pointer root;
		pointer end;

	public:
		Tree(/* args */);
		~Tree();
	};
}

#endif
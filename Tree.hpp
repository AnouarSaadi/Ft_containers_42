#ifndef TREE_HPP
# define TREE_HPP

namespace ft {
	template <class T, class , class Alloc>
	class Tree
	{
	private:
		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef pointer		value_type*;
		typedef reference	value_type&;
		typedef struct node {
			value_type		data;
			struct node		*right;
			struct node		*left;
			struct node		*parent;
			size_t			height;
		} _Node;

		pointer root;
		pointer end;

	public:
		Tree(/* args */);
		~Tree();
	};
}

#endif
#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"

namespace ft
{
template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<const Key, T>				value_type;
		typedef size_t								size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		//Constructors
		map() : tree_start(allocateNode()), tree_size(0) {}
		virtual ~map() {}

		//Operators
		T& operator[]( const Key& key ) {
			Node	*tmp = findNode( key );
			if (!tmp->pair)
				createPair(*tmp, *(myAllocate()));
			return tmp->pair->second;
		}

		//Functions
		void insert( const value_type& value ) {
			Node	*tmp = findNode( value.first );
			if (!tmp->pair)
				createPair(*tmp, value);
		}
		T& at( const Key& key ) {
			Node	*tmp = findNode(key);
			if (!tmp->pair || tmp->pair->first != key)
				throw std::out_of_range("map::at");
			return tmp->pair->second;
		}
		bool empty() const {
			if (!tree_start->pair)
				return true;
			return false;
		}
		size_type size() const {
			return (tree_size);
		}

		//this one seems too hard for now
/* 		size_type erase( const Key& key ) {
			Node* node = findNode(key);
			if (!node->pair)
				return 0;
			
		} */

	private:
		struct	Node {
			value_type	*pair;
			Node		*left;
			Node		*right;
			const Node	*parent;
		};
		Node		*tree_start;
		size_t		tree_size;
		Allocator	allocator;
		key_compare	comp;

		Node	*findNode(const key_type &key)
		{
			Node	*tmp;

			tmp = tree_start;
			while (tmp && tmp->pair)
			{
				if (key < tmp->pair->first)
				{
					if (!tmp->left)
					{
						tmp->left = createChildNode(*tmp);
						return tmp->left;
					}
					tmp = tmp->left;
				}
				else if (key > tmp->pair->first)
				{
					if (!tmp->right)
					{
						tmp->right = createChildNode(*tmp);
						return tmp->right;
					}
					tmp = tmp->right;
				}
				else
					return tmp;
			}
			return tmp;
		}
		Node	*createChildNode(const Node &parent)
		{
			Node *child = allocateNode();
			child->parent = &parent;
			return child;
		}
		Node	*allocateNode()
		{
			Node	*node = new Node();
			node->parent = NULL;
			node->right = NULL;
			node->left = NULL;
			node->pair = NULL;
			return (node);
		}
		pointer	createPair( Node &node, const value_type& value )
		{
			node.pair = myAllocate();
			myConstruct(node.pair, value);
			tree_size++;
			return node.pair;
		}
		pointer	myAllocate()
		{
			pointer result = allocator.allocate(1);
			allocator.construct(result, *(new value_type()));
			return result;
		}
		void	myDeallocate(pointer ptr, size_t size)
		{
			allocator.deallocate(ptr, size);
		}
		void	myConstruct(pointer ptr, const value_type &el)
		{
			allocator.construct(ptr, el);
		}
};
}

#endif

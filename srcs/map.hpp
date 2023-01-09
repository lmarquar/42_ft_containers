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
		explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : my_comp(comp), allocator(alloc) {}
		map( const map& other ) : tree_start(cloneAllNodes(NULL, *(other.tree_start))), tree_size(0), allocator(other.allocator), my_comp(other.my_comp) {}
		virtual ~map() {
			eraseAllNodes(tree_start);
		}

		//Operators
		map& operator=( const map& other )
		{
			eraseAllNodes(tree_start);
			tree_size = 0;
			allocator = other.allocator;
			my_comp = other.my_comp;
			tree_start = cloneAllNodes(NULL, *(other.tree_start));
			return (*this);
		}
		T& operator[]( const Key& key ) {
			Node	*tmp = findOrCreate( key );
			if (!tmp->pair)
				tmp->pair = createPair(*(myAllocate()));
			return tmp->pair->second;
		}

		//Functions
		void insert( const value_type& value ) {
			Node	*tmp = findOrCreate( value.first );
			if (!tmp->pair)
				tmp->pair = createPair(value);
		}
		T& at( const Key& key ) {
			Node	*tmp = findOrCreate(key);
			if (!tmp->pair || tmp->pair->first != key)
			{
				if (!strcmp(OS, "linux"))
					throw std::out_of_range("map::at");
				else
					throw std::out_of_range("map::at:  key not found");
			}
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
		size_type erase( const Key& key ) {
			Node* node = findOrCreate(key);
			if (!node->pair)
				return 0;
			Node* p = node->parent;
			if (p->right && p->right->pair && (p->right->pair->first == node->pair->first))
				p->right = NULL;
			else
				p->left = NULL;
			if (node->right)
				reimplementNode(&node->right);
			if (node->left)
				reimplementNode(&node->left);
			myDeallocate(node->pair, 1);
			free(node);
			tree_size--;
			return 1;
		}
		size_type max_size() const {
			return (allocator.max_size() / 2);
		}
		void clear() {
			eraseAllNodes(tree_start);
			tree_start = allocateNode();
			tree_size = 0;
		}
		void swap( map& other ) {
			Node		*tmpN = tree_start;
			size_t		tmp_size = tree_size;
			Allocator	tmp_alloc = allocator;
			key_compare	tmp_cmp = my_comp;

			tree_start = other.tree_start;
			tree_size = other.tree_size;
			allocator = other.allocator;
			my_comp = other.my_comp;
			other.tree_start = tmpN;
			other.tree_size = tmp_size;
			other.allocator = tmp_alloc;
			other.my_comp = tmp_cmp;
		}


	private:
		struct	Node {
			pointer	pair;
			Node	*left;
			Node	*right;
			Node	*parent;
		};
		Node		*tree_start;
		size_t		tree_size;
		Allocator	allocator;
		key_compare	my_comp;

		Node *cloneAllNodes(Node *parent, const Node &toBeCloned)
		{
			Node *clone = cloneAndReplaceParent(parent, toBeCloned);
			if (toBeCloned.left && toBeCloned.left->pair)
				clone->left = cloneAllNodes(clone, *(toBeCloned.left));
			if (toBeCloned.right && toBeCloned.right->pair)
				clone->right = cloneAllNodes(clone, *(toBeCloned.right));
			return clone;
		}
		Node *cloneAndReplaceParent(Node *parent, const Node &toBeCloned) {
			Node *clone = allocateNode();
			clone->parent = parent;
			clone->pair = createPair(*(toBeCloned.pair));
			return (clone);
		}
		void	eraseAllNodes(Node *top) {
			if (top->right)
				eraseAllNodes(top->right);
			if (top->left)
				eraseAllNodes(top->left);
			if (top->pair)
				myDeallocate(top->pair, 1);
			free(top);
		}
		Node	*findOrCreate(const key_type &key)
		{
			Node	*tmp;

			tmp = tree_start;
			while (tmp && tmp->pair && key != tmp->pair->first)
			{
				if (key < tmp->pair->first)
					tmp = createIfDoesNotExist(&tmp->left, tmp);
				else if (key > tmp->pair->first)
					tmp = createIfDoesNotExist(&tmp->right, tmp);
			}
			return tmp;
		}
		Node	*createIfDoesNotExist(Node **node, Node *parent)
		{
			if (!(*node))
				*node = createChildNode(*parent);
			return (*node);
		}
		Node	*createChildNode(Node &parent)
		{
			Node *child = allocateNode();
			child->parent = &parent;
			return child;
		}
		void	reassignAllButParent(Node *dest, const Node *src)
		{
			if (dest->left || dest->right || dest->pair)
				throw std::bad_exception();
			dest->right = src->right;
			dest->left = src->left;
			dest->pair = src->pair;
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
		void	reimplementNode(Node **toBeReimplemented)
		{
			Node *tmp = *toBeReimplemented;
			*toBeReimplemented = NULL;
			Node *npos = findOrCreate(tmp->pair->first);
			reassignAllButParent(npos, tmp);
		}
		pointer	createPair( const value_type& value )
		{
			value_type *pair = myAllocate();
			myConstruct(pair, value);
			tree_size++;
			return pair;
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

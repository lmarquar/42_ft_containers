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
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		//Constructors
		map() : tree_start(allocateNode()), tree_size(0) {
/* 			end_val = value_type();
			std::cout << "endType: " << end_val.first << std::endl; */
		}
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
			{
				tmp->pair = myAllocate();
				myConstruct(tmp->pair, std::make_pair(key, mapped_type()));
				tree_size++;
			}
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
			if (p->left_right[R] && p->left_right[R]->pair && (p->left_right[R]->pair->first == node->pair->first))
				p->left_right[R] = NULL;
			else
				p->left_right[L] = NULL;
			if (node->left_right[R])
				reimplementNode(&node->left_right[R]);
			if (node->left_right[L])
				reimplementNode(&node->left_right[L]);
			myDeallocate(node->pair, R);
			free(node);
			tree_size--;
			return 1;
		}
		size_type max_size() const {
			return ((size_t(-1) / sizeof(std::map<Key, mapped_type>)) / 3);
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
		size_type count( const Key& key ) const {
			//might be easier when find is implemented#
			(void) key;
			return (2);
		}
	private:
		struct	Node {
			pointer	pair;
			Node	*left_right[2];
			Node	*parent;
		};
//		static value_type	end_val;
		class BaseIterator
		{
			public:
				typedef typename std::iterator_traits<typename Allocator::pointer>::pointer pointer;
				typedef std::iterator_traits<pointer> traits;
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::reference reference;

				// Constructors
				BaseIterator(Node *pt = 0) : ptr(pt)
				{
				}
				BaseIterator(const BaseIterator& ref) : ptr(ref.ptr) {}

				// Destructors
				virtual ~BaseIterator()
				{
				}

				// Operators
				reference operator*() const
				{
					return (*ptr->pair);
				}
				virtual BaseIterator& operator++()
				{
					if (!ptr->left_right[R])
					{
						Node *tmp = ptr->parent;
/* 						if (tmp->left_right[L] != ptr->left_right[R])
							ptr = &end_val;
						else */
							ptr = tmp;
					}
					else {
						ptr = ptr->left_right[R];
						while (ptr->left_right[L])
							ptr = ptr->left_right[L];
					}
					return (*this);
				}
				bool operator==(const BaseIterator &cmp)
				{
					return (ptr == cmp.ptr);
				}

			private:
				Node	*ptr;
		};
	public:
		typedef typename std::iterator_traits<BaseIterator>::difference_type	difference_type;
		typedef BaseIterator													iterator;

		iterator begin() {
			return (iterator(getLeftmostNode()));
		}
		iterator end() {
			return (iterator(getRightmostNode()));
		}
	private:
		enum		Side{L, R};
		
		Node		*tree_start;
		size_t		tree_size;
		Allocator	allocator;
		key_compare	my_comp;
		Side		side;

		Node *cloneAllNodes(Node *parent, const Node &toBeCloned)
		{
			Node *clone = cloneAndReplaceParent(parent, toBeCloned);
			if (toBeCloned.left_right[0] && toBeCloned.left_right[0]->pair)
				clone->left_right[0] = cloneAllNodes(clone, *(toBeCloned.left_right[0]));
			if (toBeCloned.left_right[1] && toBeCloned.left_right[1]->pair)
				clone->left_right[1] = cloneAllNodes(clone, *(toBeCloned.left_right[1]));
			return clone;
		}
		Node *cloneAndReplaceParent(Node *parent, const Node &toBeCloned) {
			Node *clone = allocateNode();
			clone->parent = parent;
			clone->pair = createPair(*(toBeCloned.pair));
			return (clone);
		}
		void	eraseAllNodes(Node *top) {
			if (top->left_right[0])
				eraseAllNodes(top->left_right[0]);
			if (top->left_right[1])
				eraseAllNodes(top->left_right[1]);
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
					tmp = createIfDoesNotExist(&tmp->left_right[0], tmp);
				else if (key > tmp->pair->first)
					tmp = createIfDoesNotExist(&tmp->left_right[1], tmp);
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
			if (dest->left_right[0] || dest->left_right[1] || dest->pair)
				throw std::bad_exception();
			dest->left_right[0] = src->left_right[0];
			dest->left_right[1] = src->left_right[1];
			dest->pair = src->pair;
		}
		void	reimplementNode(Node **toBeReimplemented)
		{
			Node *tmp = *toBeReimplemented;
			*toBeReimplemented = NULL;
			Node *npos = findOrCreate(tmp->pair->first);
			reassignAllButParent(npos, tmp);
		}
		Node	*getLeftmostNode() {
			return (getBorderNode(L));
		}
		Node	*getRightmostNode() {
			return (getBorderNode(R));
		}
		Node	*getBorderNode(Side side) {
			Node *node = tree_start;
			while (node->left_right[side] && node->left_right[side]->pair)
				node = node->left_right[side];
			return node;
		}
		pointer	createPair(value_type value)
		{
			value_type *pair = myAllocate();
			myConstruct(pair, value);
			tree_size++;
			return pair;
		}
		Node	*allocateNode()
		{
			Node	*node = new Node();
			setAllElementsToNul(node);
			return (node);
		}
		Node	*setAllElementsToNul(Node *node)
		{
			node->parent = NULL;
			node->left_right[0] = NULL;
			node->left_right[1] = NULL;
			node->pair = NULL;
			return (node);
		}
		pointer	myAllocate()
		{
			pointer result = allocator.allocate(1);
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
template <typename Key, typename Value>
void swap(map<Key,Value>& a, map<Key,Value>& b)
{
	a.swap(b);
}
}
//template < typename Key, typename T > typename ::std::pair<const Key, T> ft::map< Key, T >::end_val = std::pair<const Key, T>;

#endif

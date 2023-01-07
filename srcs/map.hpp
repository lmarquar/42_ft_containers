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
		map() : tree_start(new Node) {}
		virtual ~map() {}

		//Functions
		void insert( const value_type& value )
		{
			Node	*tmp = findNode( value.first );
			tmp->pair = myAllocate();
			myConstruct(tmp->pair, value);
			return ;
		}
		T& at( const Key& key )
		{
			Node	*tmp = findNode(key);
			if (!tmp->pair || tmp->pair->first != key)
				throw std::out_of_range("map");
			return tmp->pair->second;
		}

	private:
		struct	Node {
			value_type	*pair;
			Node		*left;
			Node		*right;
		};
		Node		*tree_start;
		size_t		size;
		Allocator	allocator;

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
		Node	*findNode(const key_type &key)
		{
			Node	*tmp;

			tmp = tree_start;
			while (tmp && tmp->pair)
			{
				if (key < tmp->pair->first)
				{
					if (!tmp->left)
						tmp->left = new Node();
					tmp = tmp->left;
				}
				else if (key > tmp->pair->first)
				{
					if (!tmp->right)
						tmp->right = new Node();
					tmp = tmp->right;
				}
				else
					return tmp;
			}
			return tmp;
		}
};
}

#endif

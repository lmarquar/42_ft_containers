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
		map() : tree_start(allocator.allocate(1)) {}
		virtual ~map() {}

		//Functions
		void insert( const value_type& value )
		{
			myConstruct(tree_start, value);
			return ;
		}
		T& at( const Key& key )
		{
			if (tree_start->val.first != key)
				throw std::out_of_range("map");
			return tree_start->val.second;
		}

	private:
		struct	Node {
			value_type	val;
			Node		*left;
			Node		*right;
		};
		Node		*tree_start;
		size_t		size;
		Allocator	allocator;

		pointer	myAllocate(size_t size)
		{
			pointer result = allocator.allocate(size);
			return result;
		}
		void	myDeallocate(pointer ptr, size_t size)
		{
			allocator.deallocate(ptr, size);
		}
		void	myConstruct(pointer ptr, value_type el)
		{
			allocator.construct(ptr, el);
		}
};
}

#endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"

namespace ft
{
template<
	class T,
	class Allocator = std::allocator<T>
>
class vector
{
	public:
		// Variables
		typedef T						value_type;
		typedef Allocator				allocator_type;
		typedef size_t					size_type;
		typedef T&						reference;
		typedef const T&				const_reference;
		typedef T *						pointer;
		typedef const T *				const_pointer;

		// Constructors
		vector() : arr(myAllocate(0)), arr_capacity(0), arr_size(0){}
		vector(pointer range_start, pointer range_end) : arr(0), arr_capacity(0), arr_size(0)
		{
			size_t	i;

			i = (size_t)(range_end - range_start);
			if ((range_start + i) != range_end || i > alloc.max_size())
			{
				if (!strcmp(OS, "linux"))
					throw std::length_error("cannot create ft::vector larger than max_size()");
				else
					throw std::length_error("vector");
			}
			arr_capacity = i;
			arr_size = arr_capacity;
			arr = myAllocate(arr_capacity);
			myConstruct(arr, T());
			for (i = 1; i <= arr_capacity; i++)
				myConstruct(&arr[i], range_start[i - 1]);
		}
		vector(const vector &copy) : arr(clone(copy)) {}

		// Destructor
		~vector()
		{
			myDeallocate(arr, arr_capacity);
		}

		// Operators
		vector & operator=(const vector &assign)
		{
			clone(assign);
			return (*this);
		}
		reference operator[](size_t pos)
		{
			return (arr[pos + 1]);
		}
		bool operator==( const vector& rhs )
		{
			iterator	it_lhs = begin();
			iterator	it_rhs = rhs.begin();

			while (it_lhs != end() && it_rhs != rhs.end())
			{
                if (*it_lhs != *it_rhs)
					return false;
                ++it_lhs;
				++it_rhs;
			}
			return (it_lhs == end() && it_rhs == rhs.end());
		}
		bool operator!=( const vector& rhs )
        {
			return!(*this == rhs);
		}
		bool operator<( const vector& rhs )
        {
			iterator    it_lhs = begin();
			iterator    it_rhs = rhs.begin();

			while (it_lhs != end() && it_rhs != rhs.end())
			{
				if (*it_lhs < *it_rhs)
                    return true;
				else if (*it_lhs > *it_rhs)
                    return false;
				++it_lhs;
                ++it_rhs;
			}
			if (it_lhs == end() && it_rhs != rhs.end())
			    return true;
            else
                return false;
		}
		bool operator>( const vector& rhs )
        {
			iterator    it_lhs = begin();
			iterator    it_rhs = rhs.begin();

			while (it_lhs != end() && it_rhs != rhs.end())
			{
                if (*it_lhs > *it_rhs)
				    return true;
				else if (*it_lhs < *it_rhs)
                    return false;
				it_lhs++;
				it_rhs++;
			}
			if (it_lhs != end() && it_rhs == rhs.end())
			    return true;
            else
                return false;
		}
		bool operator<=( const vector& rhs )
        {
			return (!(*this > rhs));
		}
		bool operator>=( const vector& rhs )
        {
			return (!(*this < rhs));
		}
		// Functions
		size_t capacity() const
		{
			return arr_capacity;
		}
		size_t size() const
		{
			return arr_size;
		}
		size_t max_size() const
		{
			return (alloc.max_size());
		}
 		void push_back(T el)
		{
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				if (arr_capacity > alloc.max_size() / (size_t)2)
					throw std::out_of_range("vector");
				new_arr_capacity = (arr_capacity == 0 ? 1 : (arr_capacity * 2));
				new_arr = myAllocate(new_arr_capacity + 2);
				pasteAllInto(new_arr, arr_size);
				myDeallocate(arr, arr_capacity + 2);
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			myConstruct(&arr[++arr_size], el);
			myConstruct(&arr[arr_size + 1], T());
		}
		void	pop_back(void)
		{
			if (arr_size)
				arr_size--;
		}
		T at(size_t i) const
		{

			if (i >= arr_size)
			{
				if (!strcmp(OS, "linux"))
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << i << ") >= this->size() (which is " << arr_size << ")";
					std::string err_msg = ss.str();
					throw std::out_of_range(err_msg);
				}
				else
					throw std::out_of_range("vector");
			}
			return (arr[i + 1]);
		}
		T &front()
		{
			if (arr_capacity == 0)
				throw std::out_of_range("cannot access element of empty vector");
			return (arr[1]);
		}
		T &back()
		{
			if (arr_capacity == 0)
				throw std::out_of_range("cannot access element of empty vector");
			if (arr_size == 0)
				return (arr[1]);
			else
				return (arr[arr_size]);
		}
		void clear()
		{
			arr_size = 0;
			myConstruct(&arr[1], T());
		}
		bool empty() const
		{
			if (arr_size == 0)
				return (true);
			else
				return (false);
		}
		T*	data()
		{
			return (&arr[1]);
		}
		const T* data() const
		{
            return (&arr[1]);
        }
		allocator_type	get_allocator() const
		{
			return (alloc);
		}
		void	resize(size_type n, value_type val = value_type())
		{
			value_type	*new_arr;

			if (n < 0 || n > alloc.max_size())
				throw std::length_error("vector::_M_fill_insert");
			if (n > arr_size)
			{
				if (n > arr_capacity)
				{
					new_arr = myAllocate(n + 2);
					pasteAllInto(new_arr, arr_size);
					myDeallocate(arr, arr_capacity + 2);
					arr = new_arr;
					arr_capacity = n;
				}
				for (size_t i = (arr_size + 1); i <= n; i++)
					arr[i] = val;
			}
			arr_size = n;
		}
		void	reserve(size_t new_arr_capacity)
		{
			value_type *new_arr;

			if (new_arr_capacity <= alloc.max_size() && new_arr_capacity > arr_capacity)
			{
				new_arr = myAllocate(new_arr_capacity);
				pasteAllInto(new_arr, arr_size);
				arr_capacity = new_arr_capacity;
			}
		}
		void swap(vector<T, Allocator>& rhs)
		{
			pointer		tmp = arr;
			size_t		old_capa = arr_capacity;
			size_t		old_size = arr_size;

			arr = rhs.arr;
			arr_capacity = rhs.arr_capacity;
			arr_size = rhs.arr_size;
			rhs.arr = tmp;
			rhs.arr_capacity = old_capa;
			rhs.arr_size = old_size;
		}

		// Classes
		class BaseIterator
		{
			public:
				// Typedefs
				typedef typename std::iterator_traits<T*>::pointer pointer;
				typedef std::iterator_traits<pointer> traits;
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::reference reference;

				// Constructors
				BaseIterator(pointer pt = 0) : ptr(pt)
				{
				}
				BaseIterator(const BaseIterator& ref) : ptr(&(*ref)) {}

				// Destructors
				virtual ~BaseIterator()
				{
				}

				// Operators
				reference operator*() const
				{
					return (*ptr);
				}
				virtual BaseIterator& operator++()
				{
					++ptr;
					return (*this);
				}
				BaseIterator operator++(int)
				{
					BaseIterator iter(*this);
					operator++();
					return (iter);
				}
				virtual BaseIterator& operator--()
				{
					--ptr;
					return (*this);
				}
				BaseIterator operator--(int)
				{
					BaseIterator iter(*this);
					operator--();
					return (iter);
				}
				virtual BaseIterator & operator=(const BaseIterator & iter)
				{
					ptr = &(*iter);
					return (*this);
				}
				virtual BaseIterator & operator=(const pointer & iter)
				{
					ptr = iter;
					return (*this);
				}
				virtual BaseIterator & operator+=(int n)
				{
					ptr += n;
					return (*this);
				}
				virtual BaseIterator & operator-=(int n)
				{
					ptr -= n;
					return (*this);
				}
				virtual BaseIterator operator-(int n) const
				{
					BaseIterator iter(*this);
					for (int i = n; i > 0; i--)
						iter--;
					return (iter);
				}
				virtual BaseIterator operator+(int n) const
				{
					BaseIterator iter(*this);
					for (int i = n; i > 0; i--)
						iter++;
					return (iter);
				}
				bool operator==(const BaseIterator &cmp)
				{
					return (ptr == &(*cmp));
				}
				bool operator!=(const BaseIterator &cmp)
				{
					return (ptr != &(*cmp));
				}
				bool operator<(const BaseIterator &cmp)
				{
					return (ptr < &(*cmp));
				}
				bool operator<=(const BaseIterator &cmp)
				{
					return (ptr <= &(*cmp));
				}
				bool operator>(const BaseIterator &cmp)
				{
					return (ptr > &(*cmp));
				}
				bool operator>=(const BaseIterator &cmp)
				{
					return (ptr >= &(*cmp));
				}

				// Functions
				pointer base() const
				{
					return (ptr);
				}
			private:
				pointer	ptr;
		};
		class ConstBaseIterator : public BaseIterator
		{
			public:
				typedef typename std::iterator_traits<const T*>::pointer pointer;
				typedef std::iterator_traits<pointer> traits;
				typedef typename traits::iterator_category iterator_category;
				typedef typename traits::value_type value_type;
				typedef typename traits::difference_type difference_type;
				typedef typename traits::reference reference;
				// Constructors
				ConstBaseIterator(typename BaseIterator::pointer pt = 0) : BaseIterator(pt)
				{
				}
				ConstBaseIterator(const ConstBaseIterator& ref) : BaseIterator(ref)
				{
				}
				ConstBaseIterator(BaseIterator iter) : BaseIterator(iter) {}

				// Destructors
				virtual ~ConstBaseIterator()
				{
				}

				// Operators
				ConstBaseIterator & operator=(const BaseIterator & iter)
				{
					BaseIterator::operator=(iter);
					return (*this);
				}
				ConstBaseIterator & operator=(const pointer & iter)
				{
					BaseIterator::operator=(iter);
					return (*this);
				}
				const_reference operator*() const
				{
					return (BaseIterator::operator*());
				}
				ConstBaseIterator& operator++()
				{
					BaseIterator::operator++();
					return (*this);
				}
				ConstBaseIterator& operator--()
				{
					BaseIterator::operator--();
					return (*this);
				}
				ConstBaseIterator operator++(int)
				{
					ConstBaseIterator iter(*this);
					BaseIterator::operator++();
					return (iter);
				}
				ConstBaseIterator operator--(int)
				{
					ConstBaseIterator iter(*this);
					BaseIterator::operator--();
					return (iter);
				}

				// Functions
				const_pointer	base() const
				{
					return (BaseIterator::base());
				}
		};
	public:
	    typedef typename std::iterator_traits<BaseIterator>::difference_type	difference_type;
		typedef BaseIterator													iterator;
		typedef ConstBaseIterator												const_iterator;
		typedef typename std::reverse_iterator<iterator>						reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator>					const_reverse_iterator;

		// Functions you need the iterator for
		iterator begin()
		{
			return (iterator(&arr[1]));
		}
		iterator end()
		{
			return (iterator(&arr[size() + 1]));
		}
		const_iterator begin() const
		{
			return (iterator(&arr[1]));
		}
		const_iterator end() const
		{
			return (const_iterator(&arr[size() + 1]));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}
		iterator insert(const_iterator __pos, const T& el)
		{
			size_t	insert_pos = getIterPos(__pos);
			incrArrCapaIfNecessary(arr_size + 1);
			insertElAt(el, insert_pos);
			return (iterator(&arr[insert_pos]));
		}
		iterator insert( const_iterator pos, size_type count, const T& value )
		{
			size_t insert_pos = this->getIterPos(pos);
			incrArrCapaIfNecessary(arr_size + count);
			for (; count > 0; count--)
				insertElAt(value, insert_pos);
			return pos;
		}
		iterator insert( const_iterator pos, iterator first, iterator last )
		{
			size_t i_diff = 0;
			if (first > last)
				return pos;
			for (iterator tmp = last; tmp != first; tmp--)
				i_diff++;
			size_t insert_pos = getIterPos(pos);
			incrArrCapaIfNecessary(arr_size + i_diff);
			for (; i_diff > 0; i_diff--)
				insertElAt(*(--last), insert_pos);
			return (last);
		}
		iterator erase(iterator position)
		{
			iterator	it = findIterator(position);

			for (it++; it != end(); it++)
				*(it - 1) = *(it);
			arr_size--;
			return position;
		}
		iterator erase(iterator first, iterator last)
		{
			size_t		i = 0;
			iterator	itFirst = findIterator(first);
			iterator	itLast = itFirst;

			for (; (itLast != last) && (itLast != end()); itLast++)
				i++;
			if (itLast != last)
				throw std::runtime_error("vector: wrong input");
			for (; (itLast != end()); itLast++)
			{
				*itFirst = *itLast;
				itFirst++;
			}
			arr_size -= i;
			return last;
		}
		void assign( size_type count, const T& value )
		{
			incrArrCapaIfNecessary(count);
			for (size_type i = 1; i <= count; i++)
				myConstruct(&arr[i], value);
			arr_size = count;
		}
		void assign( iterator first, iterator last )
		{
			size_t i_diff = 0;
			if (first > last)
				return ;
			for (iterator tmp = last; tmp != first; tmp--)
				i_diff++;
			incrArrCapaIfNecessary(i_diff);
			for (size_t j = 1; j <= i_diff; j++, first++)
				myConstruct(&arr[j] , *first);
			arr_size = i_diff;
		}
	private:
		Allocator	alloc;
		pointer		arr;
		size_t		arr_capacity;
		size_t		arr_size;

		pointer clone(const vector &toBeCloned)
		{
			myDeallocate(arr, arr_capacity);
			arr = myAllocate(toBeCloned.capacity());
			arr_capacity = toBeCloned.capacity();
			for (size_t i = 1; i <= toBeCloned.size(); i++)
				myConstruct(&arr[i], toBeCloned.at(i - 1));
			arr_size = toBeCloned.size();
			return (arr);
		}
		iterator findIterator(iterator &needle)
		{
			iterator it = begin();

			for (; (it != needle) && (it != end()); it++)
				;
			if (it != needle)
				throw std::runtime_error("vector: wrong input");
			return (it);
		}
		size_t	getIterPos(iterator &__pos)
		{
			iterator	tmp;
			iterator	it_end;
			size_t		insert_pos;

			tmp = begin();
			it_end = end();
			for (insert_pos = 1; insert_pos <= arr_size; insert_pos++)
			{
				if (&(*tmp) == &(*__pos) || tmp == it_end)
					break;
				tmp++;
			}
			if (&(*tmp) != &(*__pos))
			{
				std::cerr << "vector: iterator position not found in vector" << std::endl;
				throw std::bad_exception();
			}
			return insert_pos;
		}
		pointer	myAllocate(size_t size)
		{
			pointer result = alloc.allocate(size + 2);
			return result;
		}
		void	myDeallocate(pointer ptr, size_t size)
		{
			alloc.deallocate(ptr, size + 2);
		}
		void	myConstruct(pointer ptr, T el)
		{
			alloc.construct(ptr, el);
		}
		void pasteAllInto(pointer buf, size_t buf_size)
		{
			for (size_t i = 1; i <= buf_size; i++)
				myConstruct(&buf[i], arr[i]);
		}
		void moveAllToRightByOne()
		{
			for (size_t i = (arr_size + 1); i > 1; i--)
				myConstruct(&arr[i], arr[i - 1]);
		}
		void incrArrCapaIfNecessary(size_t min_capa)
		{
			if (min_capa > arr_capacity)
				incrArrCapa(min_capa);
		}
		void	incrArrCapa(size_t min_capa)
		{
			size_t	capa_new = arr_capacity;

			if (capa_new == 0)
				capa_new = 1;
			while (capa_new < min_capa)
			{
				capa_new = capa_new * 2;
				if (capa_new > INT_MAX)
					throw std::out_of_range("vector size gets too big");
			}
			T*	new_arr = myAllocate(capa_new);
			for (size_t	i = 1; i <= arr_size; i++)
				myConstruct(&new_arr[i], arr[i]);
			myDeallocate(arr, arr_capacity);
			arr = new_arr;
			arr_capacity = capa_new;
		}
		void	insertElAt(const T& el, size_t insert_pos)
		{
			size_t	i = arr_size + 1;

			while (i > insert_pos)
			{
				myConstruct(&arr[i], arr[i - 1]);
				i--;
			}
			myConstruct(&arr[i], el);
			arr_size++;
		}
};
template <typename T>
void swap(vector<T>& a, vector<T>& b)
{
	a.swap(b);
}
template <typename T>
void operator==(const T& a, const T& b)
{
	return (a.operator==(b));
}
template <typename T>
void operator!=(const T& a, const T& b)
{
	return (a.operator!=(b));
}
template <typename T>
void operator<(const T& a, const T& b)
{
	return (a.operator<(b));
}
template <typename T>
void operator>(const T& a, const T& b)
{
	return (a.operator>(b));
}
template <typename T>
void operator<=(const T& a, const T& b)
{
	return (a.operator<=(b));
}
template <typename T>
void operator>=(const T& a, const T& b)
{
	return (a.operator>=(b));
}
}

#endif

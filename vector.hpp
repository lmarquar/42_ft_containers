#ifndef VECTOR_HPP
# define VECTOR_HPP

# define MAX_SIZE INT_MAX // (LONG_MAX / 2)

# include <iostream>
# include <string>
# include <stdexcept>

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
		typedef T&						reference;
		typedef &T						pointer;
		typedef size_t					size_type;
		typedef T						value_type;


		// Constructors
		vector()
		{
			arr_capacity = 0;
			arr_size = 0;
			arr = new T[arr_capacity];
		}
		vector(T *range_start, T *range_end)
		{
			size_t	i;

			i = (size_t)(range_end - range_start);
			std::cout << "Debugging: distance between range_inputs: " << i << std::endl;
			if ((range_start + i) != range_end || i > MAX_SIZE)
				throw std::length_error("cannot create ft::vector larger than max_size()");
			arr_capacity = i;
			arr = new T[arr_capacity];
			for (i = 0; range_start[i] != *range_end; i++)
				arr[i] = range_start[i];
			arr_size = i;
		}
		vector(const vector &copy)
		{
			*this = copy;
		}

		// Destructor
		~vector()
		{
			std::cout << "destructor of vector called" << std::endl;
			delete arr;
		}

		// Operators
		vector & operator=(const vector &assign)
		{
			arr_capacity = assign.capacity();
			arr_size = assign.size();
			return (*this);
		}
		reference operator[](size_t pos)
		{
			return (arr[pos]);
		}
		
		// Functions
		inline size_t capacity() const
		{
			return arr_capacity;
		}
		inline size_t size() const
		{
			return arr_size;
		}
		size_t max_size() const
		{
			return (MAX_SIZE);
		}
 		void push_back(T el)
		{
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				if (arr_capacity > MAX_SIZE / (size_t)2)
					throw std::out_of_range("vector");
				new_arr_capacity = (arr_capacity == 0 ? 1 : (arr_capacity * 2));
				new_arr = new T[new_arr_capacity];
				pasteAllInto(new_arr, new_arr_capacity);
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			arr[arr_size++] = el;
		}
		inline T at(size_t i) const
		{
			std::stringstream ss;
			ss << "vector::_M_range_check: __n (which is " << i << ") >= this->size() (which is " << arr_size << ")";
			std::string err_msg = ss.str();

			if (i + 1 > arr_size)
				throw std::out_of_range(err_msg);
			return (arr[i]);
		}
		inline T &front()
		{
			if (arr_capacity == 0)
				throw std::out_of_range("cannot access element of empty vector");
			return (arr[0]);
		}
		inline T &back()
		{
			if (arr_capacity == 0)
				throw std::out_of_range("cannot access element of empty vector");
			if (arr_size == 0)
				return (arr[0]);
			else
				return (arr[arr_size - 1]);
		}
		inline void clear()
		{
			delete arr;
			arr_size = 0;
			arr = new T[arr_capacity];
		}
		T*	data()
		{
			return (arr);
		}
		void	resize(size_type n, value_type val = value_type())
		{
			value_type	*new_arr;

			if (n < 0 || n > MAX_SIZE)
				throw std::length_error("vector::_M_fill_insert");
			if (arr_capacity < n)
				arr_capacity = n;
			arr_size = n;
			new_arr = new value_type[arr_capacity];
			pasteAllInto(new_arr, arr_size);
			for (size_t i = arr_size; i < arr_capacity; i++)
				new_arr[i] = val;
			delete arr;
			arr = new_arr;
		}
		void	reserve(size_t new_arr_capacity)
		{
			value_type *new_arr;

			if (new_arr_capacity <= MAX_SIZE && new_arr_capacity > arr_capacity)
			{
				new_arr = new value_type[new_arr_capacity];
				pasteAllInto(new_arr, arr_size);
				arr_capacity = new_arr_capacity;
			}
		}


		// Classes
		template <typename PointerType>
		class BaseIterator
		{
			public:
				// Constructors
				explicit BaseIterator()
				{
				}
				BaseIterator(const BaseIterator &ref)
				{
					ptr = &(*ref);
 				}

				// Destructors
				virtual ~BaseIterator()
				{
				}

				// Operators
				reference operator*() const
				{
					return (*ptr);
				}
				BaseIterator& operator++()
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
				BaseIterator& operator--()
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
				BaseIterator & operator=(const BaseIterator & iter)
				{
					this->setPtr(&(*iter));
					return (*this);
				}
				bool operator==(const BaseIterator &cmp)
				{
					return (ptr == &(*cmp));
				}

				// Getters and Setters
			protected:
				void setPtr(PointerType newPtr)
				{
					ptr = newPtr;
				}
				PointerType	getPtr()
				{
					return (ptr);
				}

			protected:
				PointerType	ptr;
		};
	private:
		template<typename PointerType>
		class iteratorParameterized : public iterator<PointerType>
		{
			public:
				// Constructors
				explicit iteratorParameterized(PointerType newPtr)
				{
					this->setPtr(newPtr);
				}

				// Destructors
				virtual ~iteratorParameterized()
				{
				}

				// Getters and Setters
		};
		
	public:
		typedef BaseIterator<pointer>		iterator;
		typedef BaseIterator<const pointer>	const_iterator;

		void insert(iterator __pos, T el)
		{
			iterator tmp;
			iterator it_end;
			iterator tmp_begin;

			size_t	i;

			tmp = begin();
			it_end = end();
			for (i = 0; i < INT_MAX; i++)
			{
				tmp++;
				if (&(*tmp) == &(*__pos) || tmp == it_end)
					break;
			}
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				new_arr_capacity = (arr_capacity == 0 ? 1 : (arr_capacity * 2));
				if (arr_capacity > INT_MAX)
					throw std::out_of_range("vector size gets too big");
				new_arr = new T[new_arr_capacity];
				for (size_t i = 0; i < arr_size - 1; i++)
					new_arr[i + 1] = arr[i];
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			tmp = end();
			tmp_begin = begin();
			i = size();
			while (&(*tmp) != &(*tmp_begin) && &(*tmp) != &(*__pos))
			{
				arr[i + 1] = arr[i];
				i--;
				tmp--;
			}
			arr[i + 1] = arr[i];
			if (arr[i] != *tmp && &(*tmp) != &(*tmp_begin))
			{
				std::cout << "i: " << i << std::endl;
				throw std::bad_exception();
			}
			arr[i] = el;
			arr_size++;
		}
		iterator begin()
		{
			iteratorParameterized it(arr);

			return (it);
		}
		iterator end()
		{
			iteratorParameterized it(&arr[size()]);

			return (it);
		}
		inline iterator erase(const iterator position)
		{
			iterator	it;
			size_t		i;

			i = 0;
			for (it = begin(); (it != position) && (it != end()); ++it)
				i++;
			if (it != position)
				throw std::runtime_error("vector: wrong input");
			

		}
	private:
		T		*arr;
		size_t	arr_capacity;
		size_t	arr_size;

		void pasteAllInto(T *buf, size_t buf_size)
		{
			for (size_t i = 0; i < buf_size; i++)
				buf[i] = arr[i];
		}
		void moveAllToRightByOne()
		{
			for (size_t i = arr_size; i > 0; i--)
				arr[i] = arr[i - 1];
		}
};
}

#endif

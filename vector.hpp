#ifndef VECTOR_HPP
# define VECTOR_HPP

# define MAX_SIZE INT_MAX

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
		typedef T&               reference;

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
			std::cout << "distance between range_inputs: " << i << std::endl;
			if ((range_start + i) != range_end || i > MAX_SIZE)
				throw std::length_error("vector");
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
			if (i + 1 > arr_size)
				throw std::out_of_range("vector");
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


		// Classes
		class iterator
		{
			public:
				// Constructors
				explicit iterator()
				{
				}
				iterator(iterator &ref)
				{
					*this = ref;
				}

				// Destructors
				~iterator()
				{
				}

				// Operators
				reference operator*() const
				{
					return (*ptr);
				}
				iterator& operator++()
				{
					++ptr;
					return (*this);
				}
				iterator operator++(int)
				{
					iterator iter(*this);
					operator++();
					return (iter);
				}
				iterator& operator--()
				{
					--ptr;
					return (*this);
				}
				iterator operator--(int)
				{
					iterator iter(*this);
					operator--();
					return (iter);
				}
				iterator & operator=(const iterator & iter)
				{
					ptr = iter.getPtr();
					return (*this);
				}

				// Getters and Setters
				T*	getPtr() const
				{
					return (ptr);
				}
				void setPtr(T *_ptr)
				{
					ptr = _ptr;
				}

			private:
				T*	ptr;
		};
/* 		void insert(iterator __pos, T el)
		{
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				new_arr_capacity = (arr_capacity == 0 ? 1 : (arr_capacity * 2));
				if (arr_capacity > INT_MAX)
					throw std::out_of_range("vector size gets too big");
				new_arr = new T[new_arr_capacity];
				pasteAllInto(new_arr, new_arr_capacity);
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			
			arr_size++;
		} */
		vector::iterator begin()
		{
			iterator it;

			it.setPtr(arr);
			return (it);
		}
		vector::iterator end()
		{
			iterator it;

			it.setPtr(arr[arr_size - 1]);
			return (it);
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

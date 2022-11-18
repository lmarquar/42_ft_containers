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
			std::cout << "Debugging: distance between range_inputs: " << i << std::endl;
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
				virtual ~iterator()
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
					std::cout << "equals operator got called" << std::endl;
					ptr = &(*iter);
					return (*this);
				}

				// Getters and Setters
			protected:
				void setPtr(T *newPtr)
				{
					ptr = newPtr;
				}
				T *getPtr()
				{
					return (ptr);
				}

			protected:
				T*	ptr;
		};
	private:
<<<<<<< HEAD
		class iteratorPrivate : public iterator
		{
			public:
				// Constructors
				explicit iteratorPrivate(T *newPtr)
=======
		class iteratorParameterized : public iterator
		{
			public:
				// Constructors
				explicit iteratorParameterized(T *newPtr)
>>>>>>> 4add10839cc9671971fdd36171dbc83b5887d5ca
				{
					this->setPtr(newPtr);
				}

				// Destructors
<<<<<<< HEAD
				virtual ~iteratorPrivate()
=======
				virtual ~iteratorParameterized()
>>>>>>> 4add10839cc9671971fdd36171dbc83b5887d5ca
				{
				}

				// Getters and Setters
		};
		
	public:
		void insert(iterator __pos, T el)
		{
			iterator tmp;
			iterator tmp_begin;

			size_t	i;

			tmp = begin();
			for (i = 0; i < INT_MAX; i++)
			{
				tmp++;
				if (&(*tmp) == &(*__pos))
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
				throw std::error_code();
			}
			arr[i] = el;
			arr_size++;
		}
		vector::iterator begin()
		{
<<<<<<< HEAD
			iteratorPrivate itPriv(arr);

			return (itPriv);
		}
		vector::iterator end()
		{
			iteratorPrivate itPriv(&(arr[arr_size]));

			return (itPriv);
=======
			iteratorParameterized it(arr);

			return (it);
		}
		vector::iterator end()
		{
			iteratorParameterized it(&arr[size()]);

			return (it);
>>>>>>> 4add10839cc9671971fdd36171dbc83b5887d5ca
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

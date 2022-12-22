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
		typedef const T&				const_reference;
		typedef T *						pointer;
		typedef const T *				const_pointer;
		typedef size_t					size_type;
		typedef T						value_type;

		// Constructors
		vector() : arr(new T[0]), arr_capacity(0), arr_size(0)
		{
			setOs();
		}
		vector(pointer range_start, pointer range_end) : arr(0), arr_capacity(0), arr_size(0)
		{
			setOs();
			size_t	i;

			i = (size_t)(range_end - range_start);
			if ((range_start + i) != range_end || i > MAX_SIZE)
			{
				if (os == "linux")
					throw std::length_error("cannot create ft::vector larger than max_size()");
				else
					throw std::length_error("vector");
			}
			arr_capacity = i;
			arr_size = arr_capacity;
			arr = new T[arr_capacity];
			for (i = 0; i < arr_capacity; i++)
				arr[i] = range_start[i];
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
			for (size_t i = 0; i < arr_size; i++)
				arr[i] = assign.at(i);
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
				pasteAllInto(new_arr, arr_size);
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			arr[arr_size++] = el;
		}
		inline T at(size_t i) const
		{

			if (i + 1 > arr_size)
			{
				if (os == "linux")
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << i << ") >= this->size() (which is " << arr_size << ")";
					std::string err_msg = ss.str();
					throw std::out_of_range(err_msg);
				}
				else
					throw std::out_of_range("vector");
			}
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
				return (arr[1]);
			else
				return (arr[arr_size - 1]);
		}
		inline void clear()
		{
			arr_size = 0;
			arr[1] = T();
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
			return (arr);
		}
		void	resize(size_type n, value_type val = value_type())
		{
			value_type	*new_arr;

			std::cout << val << std::endl;
			if (n < 0 || n > MAX_SIZE)
				throw std::length_error("vector::_M_fill_insert");
			if (n > arr_size)
			{
				if (n > arr_capacity)
				{
					new_arr = new value_type[n];
					pasteAllInto(new_arr, arr_size);
					delete arr;
					arr = new_arr;
					arr_capacity = n;
				}
				for (size_t i = arr_size; i < n; i++)
					arr[i] = val;
			}
			arr_size = n;
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
		class BaseIterator
		{
			public:
				// Constructors
				explicit BaseIterator(pointer pt = 0) : ptr(pt)
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
					ptr = &(*iter);
					return (*this);
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
			private:
				pointer	ptr;
		};
		class ConstBaseIterator : public BaseIterator
		{
			public:
				// Constructors
				explicit ConstBaseIterator(pointer pt = 0) : BaseIterator(pt)
				{
				}
				ConstBaseIterator(const ConstBaseIterator& ref) : BaseIterator(ref)
				{
				}

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
				bool operator==(const BaseIterator &cmp)
				{
					return (BaseIterator::operator==(cmp));
				}
				bool operator!=(const BaseIterator &cmp)
				{
					return (BaseIterator::operator!=(cmp));
				}
				bool operator<(const BaseIterator &cmp)
				{
					return (BaseIterator::operator<(cmp));
				}
				bool operator<=(const BaseIterator &cmp)
				{
					return (BaseIterator::operator<=(cmp));
				}
				bool operator>(const BaseIterator &cmp)
				{
					return (BaseIterator::operator>(cmp));
				}
				bool operator>=(const BaseIterator &cmp)
				{
					return (BaseIterator::operator>=(cmp));
				}
		};
	public:
		typedef BaseIterator		iterator;
		typedef ConstBaseIterator	const_iterator;

		void insert(iterator __pos, T el)
		{
			iterator tmp;
			iterator it_end;

			size_t	i;
			size_t	insert_pos;

			tmp = begin();
			it_end = end();
			i = 0;
			for (insert_pos = 0; insert_pos < arr_size; insert_pos++)
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
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				new_arr_capacity = (arr_capacity == 0 ? 1 : (arr_capacity * 2));
				if (arr_capacity > INT_MAX)
					throw std::out_of_range("vector size gets too big");
				new_arr = new T[new_arr_capacity];
				for (i = 0; i <= arr_size; i++)
					new_arr[i] = arr[i];
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			i = size();
			while (i > insert_pos)
			{
				arr[i] = arr[i - 1];
				i--;
			}
			arr[i] = el;
			arr_size++;
		}
		iterator begin()
		{
			BaseIterator it(arr);

			return (it);
		}
		const_iterator begin() const
		{
			ConstBaseIterator it(arr);

			return (it);
		}
		iterator end()
		{
			BaseIterator it(&arr[size()]);

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
		pointer		arr;
		size_t		arr_capacity;
		size_t		arr_size;
		std::string	os;

		void pasteAllInto(pointer buf, size_t buf_size)
		{
			for (size_t i = 0; i < buf_size; i++)
				buf[i] = arr[i];
		}
		void moveAllToRightByOne()
		{
			for (size_t i = arr_size; i > 0; i--)
				arr[i] = arr[i - 1];
		}
		void setOs()
		{
			#ifdef __linux__
				os = "linux";
			#else
				os = "mac";
			#endif
		}
};
}

#endif

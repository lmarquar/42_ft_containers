#ifndef VECTOR_HPP
# define VECTOR_HPP

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
		// Constructors
		vector()
		{
			arr_capacity = 0;
			arr_capacity = 0;
			arr = new T[arr_size];
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
		
		// Getters / Setters
		inline size_t capacity() const
		{
			return arr_capacity;
		}
		inline size_t size() const/*  noexcept */
		{
			return arr_size;
		}
 		void push_back(T el)
		{
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				new_arr_capacity = arr_capacity * 2;
				if (arr_capacity > INT_MAX)
					throw std::out_of_range("vector size gets too big");
				new_arr = new int((int)new_arr_capacity);
				pasteAllInto(new_arr, new_arr_capacity);
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			arr[arr_size++] = el;
			std::cout << "test" << std::endl;
		}
		void push_front(T el)
		{
			if (arr_size == arr_capacity)
			{
				T *new_arr;
				size_t new_arr_capacity;

				new_arr_capacity = arr_capacity * 2;
				if (arr_capacity > INT_MAX)
					throw std::out_of_range("vector size gets too big");
				new_arr = new int((int)new_arr_capacity);
				pasteAllInto(new_arr, new_arr_capacity);
				delete arr;
				arr = new_arr;
				arr_capacity = new_arr_capacity;
			}
			moveAllToRightByOne();
			arr[0] = el;
		}
		inline T at(int i) const
		{
			return (arr[i]);
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

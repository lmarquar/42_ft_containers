#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

template<
	class T
>
typedef struct s_list
{
	T el;
	t_list *next;
} t_list;

template<
	class T,
	class Allocator = std::allocator<T>
>
class vector
{
	public:
		// Constructors
		vector();
		vector(const vector &copy);
		
		// Destructor
		~vector();
		
		// Operators
		vector & operator=(const vector &assign);
		
		// Getters / Setters
		
	private:
		
};

#endif

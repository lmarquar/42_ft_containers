#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

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

#include "vector.hpp"

// Constructors
vector::vector()
{
	std::cout << "\e[0;33mDefault Constructor called of vector\e[0m" << std::endl;
}

vector::vector(const vector &copy)
{
	std::cout << "\e[0;33mCopy Constructor called of vector\e[0m" << std::endl;
}



// Destructor
vector::~vector()
{
	std::cout << "\e[0;31mDestructor called of vector\e[0m" << std::endl;
}


// Operators
vector & vector::operator=(const vector &assign)
{
	return *this;
}


// Getters / Setters


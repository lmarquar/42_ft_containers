#include "Allocation.hpp"

int main()
{
	std::allocator<std::string> alloc;

	alloc.allocate(1);
/* 	Allocation<std::string> allocation("string");
	allocation.printPointer();
 *///	Allocation<int> alloc(1);
//	alloc.printPointer();
	return (0);
}

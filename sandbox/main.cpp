#include "Allocation.hpp"

int main()
{
/* 	Allocation<std::string> allocation("string");
	allocation.printPointer();
 */	Allocation<int> allocation(1);
	allocation.printPointer();
	return (0);
}
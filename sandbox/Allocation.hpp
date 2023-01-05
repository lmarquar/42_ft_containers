# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <iomanip>
# include <cassert>
# include <climits>
# include <stdexcept>
# include <cstring>
# include <memory>

template<
	class T,
	class Allocator = std::allocator<T>
>
class Allocation
{
	public:
	Allocation() : ptr(0) {}
	Allocation( T somevalue)
	{
		ptr = alloc.allocate(1);
//		*ptr = somevalue;
	}
	void printPointer() const { std::cout << *ptr << std::endl; }
	private:
	Allocator alloc;
	T *ptr;
};
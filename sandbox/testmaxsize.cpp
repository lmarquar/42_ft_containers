#include "Allocation.hpp"
#include <map>
#include <cmath>

int main()
{
	std::allocator<std::string> alloc;
	std::map<int, std::string> map;
	std::map<int, std::string>::allocator_type alloc_type = map.get_allocator();
	std::vector<int> vec;
	
	std::cout << "vec.all.size: " << vec.max_size() << std::endl;
	std::vector<int>::allocator_type a_type_vec;
	std::cout << "a_type.size: " << a_type_vec.max_size() << std::endl;
	std::cout << "vec.size mathematical: " << static_cast<size_t>((pow(2, 64 - sizeof(int)) - 1)) << std::endl;
	std::cout << std::endl << "map part: " << std::endl;
	std::map<int, std::string>::allocator_type a_type_map;
	std::cout << map.max_size() << std::endl;
	std::cout << static_cast<size_t>((size_t(-1) / sizeof(std::map<int, std::string>)) / 3) << std::endl;
	std::cout << a_type_map.max_size() << std::endl;
	std::cout << alloc_type.max_size() << std::endl;
	std::cout << static_cast<size_t>(pow(2, 63) / sizeof(std::map<int, std::string>) - 2) << std::endl;
	alloc.allocate(1);
/* 	Allocation<std::string> allocation("string");
	allocation.printPointer();
 *///	Allocation<int> alloc(1);
//	alloc.printPointer();
	return (0);
}

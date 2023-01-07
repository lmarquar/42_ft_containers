#ifndef MAPTEST_HPP
# define MAPTEST_HPP

# include "MyTester.hpp"

template< template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > class Map >
void MyTester::mapTest()
{
	Map<int, std::string> my_map;
	int i = 1;
	my_map.insert(std::pair<int, std::string>(i, "hello"));
	oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
	i = 2;
	try{
		oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
	} catch (std::out_of_range& e) {
		oStream << e.what() << std::endl;
	}
	my_map.insert(std::pair<int, std::string>(i, "there"));
	oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
}

#endif

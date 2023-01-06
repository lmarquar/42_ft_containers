#ifndef MAPTEST_HPP
# define MAPTEST_HPP

# include "MyTester.hpp"

template< template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > class Map >
void MyTester::mapTest()
{
	Map<int, std::string> my_map;
	int i = 1;
	my_map.insert(std::pair<int, std::string>(i, "hello"));
	oStream << "key: " << 1 << " value: " << my_map.at(i) << std::endl;
}

#endif

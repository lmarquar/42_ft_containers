#ifndef MAPTEST_HPP
# define MAPTEST_HPP

# include "MyTester.hpp"

template< template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > class Map >
void MyTester::mapTest()
{
	Map<int, std::string> my_map;
	int i = 1;
	oStream << "map empty?: " << my_map.empty() << std::endl;
	my_map.insert(std::pair<int, std::string>(i, "hello"));
	oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
	i = 2;
	my_map.insert(std::pair<int, std::string>(i, "there"));
	oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
	i = 0;
	my_map.insert(std::pair<int, std::string>(i, "what's up ?"));
	oStream << "key: " << i << " value: " << my_map[i] << std::endl;
	i = 5;
	oStream << my_map[5] << std::endl;
	oStream << "map empty?: " << my_map.empty() << std::endl;
	oStream << "map size: " << my_map.size() << std::endl;
	my_map.erase(i = 0);
	try{
		oStream << "key: " << i << " value: " << my_map.at(i) << std::endl;
	} catch (std::out_of_range& e) {
		oStream << e.what() << std::endl;
	}
	oStream << "key: " << (i = 2) << " value: " << my_map.at(i) << std::endl;
	Map<int, std::string> my_clone(my_map);
	oStream << "key: " << (i = 2) << " value: " << my_clone.at(i) << std::endl;
}

#endif

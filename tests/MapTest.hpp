#ifndef MAPTEST_HPP
# define MAPTEST_HPP

# include "MyTester.hpp"

template< template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > > class Map >
void MyTester::mapTest()
{
	typedef typename Map<int, std::string>::iterator iterator;
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
	my_map.insert(std::pair<int, std::string>(4, "my origin is my_map"));
	oStream << "key: " << (i = 1) << " value: " << my_clone.at(i) << std::endl;
	oStream << "key: " << (i = 2) << " value: " << my_clone.at(i) << std::endl;
	oStream << my_map[4] << std::endl;
	oStream << my_clone[4] << std::endl;
	oStream << "clone size: " << my_map.size() << std::endl;
	oStream << "max_size(): " << my_map.max_size() << std::endl;
	my_clone.clear();
	oStream << my_clone[1] << std::endl;
	my_clone = my_map;
	oStream << my_clone[1] << std::endl;
	oStream << sizeof(typename Map<int, std::string>::value_type) << std::endl;
	my_clone[3] = "just a random string";
	oStream << "Descr.: swap test" << std::endl;
	my_clone.swap(my_map);
	oStream << "clone size: " << my_map.size() << std::endl;
	oStream << "after swap: " << my_map.at(3) << std::endl;
	swap(my_map, my_clone);
	oStream << "after second swap: " << my_map[3] << std::endl;
	oStream << "after second swap: " << my_clone.at(3) << std::endl;
	iterator it = my_map.begin();
	for (typename Map<int,std::string>::size_type i = 0; i < my_map.size(); i++) {
		oStream << "*it: " << (*it).second << std::endl;
		++it;
	}
	Map<int, std::string> empty_map;
	oStream << (empty_map.begin() == empty_map.end()) << std::endl;
//	oStream << "map_end: " << (*my_map.end()).first << (*my_map.end()).second << std::endl;
//	oStream << (it == my_map.end()) << std::endl;
}

#endif

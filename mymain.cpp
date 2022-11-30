#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <climits>
#include "vector.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[4;34m"
#define CYANUSCR "\033[4;36m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

class A {public: A(){a = 1;} int a;};

template <typename Vector>
void printVector(std::ostream& oStream, Vector &v)
{
    oStream << "v = { ";
    for (unsigned long n = 0; n < v.size(); n++)
        oStream << v.at(n) << ", ";
    oStream << "}; \n";
}

//implement begin and end function for iterator
template <typename Vector>
void test(std::ostream& oStream)
{
	std::stringstream sstream;
	int i_tmp;

	oStream << "GIVEN TESTS:" << std::endl;
    typename Vector::iterator iter;

     // Create a vector containing integers
    int arr[4] = {7, 5, 16, 8};
    Vector v(arr, arr+4);
    Vector empty;

    oStream << v.size() << std::endl;
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);

    oStream << "v:back1: " << v.back() << std::endl;
    v.clear();
    oStream << "v:back2: " << v.back() << std::endl;
    oStream << "v.capa: " << v.capacity() << std::endl;
    oStream << "v.size: " << v.size() << std::endl;
    oStream << empty.capacity() << std::endl;
 
    // Print out the vector
	printVector(oStream, v);


	oStream << std::endl << "MY TESTS: " << std::endl;
    int arr1[6] = {1, 2, 3, 4, 3, 2};
    int arr2[2] = {5, 6};
    try {
        Vector t_wrong(arr1, arr2);
    } catch (std::exception &e)
    {
        oStream << "caught length_error of type: " << e.what() << std::endl;
    }
    Vector t(arr1, arr1+6);
    t.push_back(2);
    t.push_back(3);
    oStream << "size:     " << t.size() << std::endl;
    oStream << "max_size: " << "not identical, that's why not displayed"/*<< t.max_size()*/ << std::endl;
    for(size_t i = 0; i < t.size(); i++)
        oStream << t.at(i) << std::endl;
    oStream << "vector[size() - 1]: " << t[t.size() - 1] << std::endl;
    oStream << "end of array" << std::endl;
    oStream << "back(): " << t.back() << std::endl;

    oStream << "iterator tests:" << std::endl;
    iter = t.begin();
    t.insert(t.begin(), 20);
    t.insert(++iter, 10);
	t.insert(t.end(), 30);
    --iter;
    typename Vector::iterator iterCpy;
	oStream << "size: " << t.size() << std::endl;
	oStream << "capacity: " << t.capacity() << std::endl;
	t.resize(t.size() - 2);
	oStream << "size: " << t.size() << std::endl;
	oStream << "capacity: " << t.capacity() << std::endl;
	iter = t.begin();
    for(size_t i = 0; i < t.size(); i++)
    {
        oStream << *iter << std::endl;
        iter++;
    }
	t.resize(t.size() + 2);
    oStream << "*(--iterator)" << *(--iter) << std::endl;
    oStream << "*(--iterator)" << *(--iter) << std::endl;
    oStream << "*(++iterator)" << *(++iter) << std::endl;
    oStream << "*(iterator--)" << *(iter--) << std::endl;
    oStream << "*(iterator++)" << *(iter++) << std::endl;

    iter = t.end();
    iter--;
	oStream << "t.size(): " << t.size() << std::endl;
	for(size_t i = t.size() - 1; i > 0; i--)
    {
        oStream << "iter: " << *iter << std::endl;
        iter--;
    }
    iterCpy = iter;
    oStream << "iter:    " << *iter << std::endl;
    oStream << "iterCpy: " << *iterCpy << std::endl;
    oStream << "*(--iterCpy): " << *(--iterCpy) << std::endl;
	i_tmp = -1;
	sstream << "Descr.: trying resize with argument " << i_tmp << ":";
	oStream << sstream.str() <<  std::endl;
	try {
		t.resize(-1);
	} catch (std::length_error &e) {
		oStream << "Error: " << e.what() << std::endl;
	}
	t.clear();
    try{
        for(size_t i = 0; i < 4; i++)
            oStream << t.at(i) << std::endl;
    } catch (std::out_of_range &e)
    {
        oStream << "catched Exception: " << e.what() << std::endl;
    }
    oStream << "capacity(): " << t.capacity() << std::endl;
    oStream << "size(): " << t.size() << std::endl;
	int onetothree[3] = {1, 3, 3};
	std::vector<int> test_vec(onetothree, onetothree+3);
	test_vec.insert(test_vec.end(), 4);
	test_vec.resize(test_vec.size() - 1);
	test_vec.reserve(10);
	test_vec.reserve(4);
	oStream << "capacity(): " << test_vec.capacity() << std::endl;
	printVector(oStream, test_vec);
}

std::string equalizeDifferences(std::string buf_mine)
{
	std::string buf_mine_adjusted;

	buf_mine_adjusted = buf_mine;
	for (size_t pos = 0; pos < buf_mine_adjusted.length(); pos++)
	{
		pos = buf_mine_adjusted.find("ft::", pos);
		if (pos == std::string::npos)
			break;
		buf_mine_adjusted.replace(pos, 4, "std::");
	}
	return (buf_mine_adjusted);
}

void toOutput(std::string first, std::string second, int width, std::string color)
{
	if (first.substr(0, 7) == "Descr.:")
		std::cout << CYANUSCR << std::setw(width) << std::left
			<< first.substr(8, first.length()) << RESET
			<< "│" << CYANUSCR << std::setw(width) << std::left
			<< second.substr(8, second.length()) << RESET << std::endl;
	else
		std::cout << GREEN << std::setw(width) << std::left
			<< first << RESET << "│" << color << second << RESET << std::endl;
}

int main()
{
    std::stringstream ss_v_mine;
    std::stringstream ss_v_real;
    std::string buf_mine;
	std::string buf_mine_adjusted;
    std::string buf_real;

/*     std::cout << "test for ft::vector: " << std::endl;
    test(v_mine, std::cout);
    std::cout << std::endl << "test for std::vector: " << std::endl;
    test(v_real, std::cout); */

//    test<ft::vector<int> >(std::cout);
    int width;
	size_t length_min;
    width = 50;
    test<ft::vector<int> >(ss_v_mine);
    test<std::vector<int> >(ss_v_real);

    std::cout << BLUE << std::setw(width + 1) << std::left << "real vector: " << "my vector: " << RESET << std::endl;
    while(std::getline(ss_v_mine, buf_mine) && std::getline(ss_v_real, buf_real))
    {
		buf_mine_adjusted = equalizeDifferences(buf_mine);
		length_min = std::min(buf_mine.length(), buf_real.length());
        if (buf_mine_adjusted == buf_real)
		{
			for (size_t i = 0; i < length_min; i = i + width - 1)
				toOutput(buf_real.substr(i, width - 1), buf_mine.substr(i, width - 1), width, GREEN);
		}
		else
		{
			for (size_t i = 0; i < length_min; i = i + width - 1)
				toOutput(buf_real.substr(i, width - 1), buf_mine.substr(i, width - 1), width, RED);
		}
	}
	buf_mine = equalizeDifferences(ss_v_mine.str());
	buf_real = ss_v_real.str();
    assert(buf_mine == buf_real);
    std::cout << std::endl << GREEN << "✔ all tests for vector pass" << RESET << std::endl;
	std::cout << "Some additional tests: " << std::endl;
	std::vector<int> test_vec;
	std::vector<int> test_vec2;

	test_vec2.push_back(2);
	test_vec.push_back(1);
	test_vec.push_back(2);
	test_vec.push_back(3);
	std::cout << "size(): " << test_vec.size() << std::endl;
	std::cout << "capacity(): " << test_vec.capacity() << std::endl;
	test_vec.erase(test_vec2.begin());
	std::cout << std::endl << "after erase(): " << std::endl;
	std::cout << "size(): " << test_vec.size() << std::endl;
	std::cout << "capacity(): " << test_vec.capacity() << std::endl;
	printVector(std::cout, test_vec);
}

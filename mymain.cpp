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
#define BLUE "\033[4;34m"
#define RESET "\033[0m"

class A {public: A(){a = 1;} int a;};

//implement begin and end function for iterator
template <typename Vector>
void test(std::ostream& oStream)
{
    int arr[6] = {1, 2, 3, 4, 3, 2};
    int arr2[2] = {5, 6};
    try {
        Vector t_wrong(arr, arr2);
    } catch (std::exception &e)
    {
        oStream << "caught length_error of type: " << e.what() << std::endl;
    }
    Vector t(arr, arr+6);
    t.push_back(2);
    t.push_back(3);
    oStream << "size: " << t.size() << std::endl;
    for(size_t i = 0; i < t.size(); i++)
        oStream << t.at(i) << std::endl;
    oStream << "vector[size() - 1]: " << t[t.size() - 1] << std::endl;
    oStream << "end of array" << std::endl;
    oStream << "back(): " << t.back() << std::endl;

    typename Vector::iterator iter;
    iter = t.begin();
     for(size_t i = 0; i < t.size(); i++)
    {
        oStream << *iter << std::endl;
        iter++;
    }
    oStream << "*(--iterator)" << *(--iter) << std::endl;
    oStream << "*(--iterator)" << *(--iter) << std::endl;
    oStream << "*(++iterator)" << *(++iter) << std::endl;
    oStream << "*(iterator--)" << *(iter--) << std::endl;
    oStream << "*(iterator++)" << *(iter++) << std::endl;

    iter = t.end();
/*     for(size_t i = t.size() - 1; i >= 0; i++)
    {
        oStream << *iter << std::endl;
        iter--;
    } */

    typename Vector::iterator iterCpy;
    iterCpy = iter;
    oStream << "iterCpy: " << *iterCpy << std::endl;
    oStream << "*(--iterCpy): " << *(--iterCpy) << std::endl;
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

}

int main()
{
	std::cout << INT_MAX << std::endl;
    int i;
    ft::vector<int> v_mine;
    std::vector<int> v_real;
    std::stringstream ss_v_mine;
    std::stringstream ss_v_real;
    std::string buf_mine;
    std::string buf_real;
    int width;
	size_t length_min;

	(void)i;
    i = 10;
    width = 40;
/*     std::cout << "test for ft::vector: " << std::endl;
    test(v_mine, std::cout);
    std::cout << std::endl << "test for std::vector: " << std::endl;
    test(v_real, std::cout); */

    test<ft::vector<int> >(std::cout);
    test<ft::vector<int> >(ss_v_mine);
    test<std::vector<int> >(ss_v_real);

    std::cout << BLUE << std::setw(width) << std::left << "real vector: " << "my vector: " << RESET << std::endl;
    while(std::getline(ss_v_mine, buf_mine) && std::getline(ss_v_real, buf_real))
    {
		length_min = std::min(buf_mine.length(), buf_real.length());
        if (buf_mine == buf_real)
		{
			for (size_t i = 0; i < length_min; i = i + width - 2)
				std::cout << GREEN << std::setw(width) << std::left
					<< buf_real.substr(i, width - 2)
					<< buf_mine.substr(i, width - 2) << RESET << std::endl;
		}
		else
		{
			for (size_t i = 0; i < length_min; i = i + width - 2)
				std::cout << RED << std::setw(width) << std::left
					<< buf_real.substr(i, width - 2)
					<< buf_mine.substr(i, width - 2) << RESET << std::endl;
		}
	}

    assert(ss_v_mine.str() == ss_v_real.str());
    std::cout << GREEN << "all tests for vector pass" << RESET << std::endl;

    std::cout << std::endl << std::endl;
    v_real.insert(v_real.begin(), 10);
    std::vector<int>::iterator iter;

    std::cout << "start of real vector" << std::endl;
     // Create a vector containing integers
    int arr[4] = {7, 5, 16, 8};
    std::vector<int> v(arr, arr+4);
    std::vector<int> empty;

    std::cout << v.size() << std::endl;
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);

    std::cout << "v:back1: " << v.back() << std::endl;
    v.clear();
    std::cout << "v:back2: " << v.back() << std::endl;
    std::cout << "v.capa: " << v.capacity() << std::endl;
    std::cout << "v.size: " << v.size() << std::endl;
    std::cout << empty.capacity() << std::endl;
 
    // Print out the vector
    std::cout << "v = { ";
    for (unsigned long n = 0; n < v.size(); n++)
        std::cout << v.at(n) << ", ";
    std::cout << "}; \n";
}

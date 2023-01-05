#ifndef MYTESTER_HPP
# define MYTESTER_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <iomanip>
# include <cassert>
# include <climits>
# include "../srcs/map.hpp"
# include "../srcs/vector.hpp"
# include "../srcs/stack.hpp"

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[4;34m"
# define CYANUSCR "\033[4;36m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

class MyTester
{
	public:
	MyTester();
	int run(char kind);

	
	private:
	int		comparisonTest(void (MyTester::*myContainerTest)(), void (MyTester::*stdContainerTest)())
	{
		std::stringstream ss_v_mine;
		std::stringstream ss_v_real;
		std::string buf_mine;
		std::string buf_mine_adjusted;
		std::string buf_real;
		size_t width;
		size_t length_min;

		width = 50;
		(this->*stdContainerTest)();
		ss_v_real << oStream.str();
		oStream.str("");
		(this->*myContainerTest)();
		ss_v_mine << oStream.str();
		std::cout << BLUE << std::setw((int)width + 1) << std::left << "real vector: " << "my vector: " << RESET << std::endl;
		while(std::getline(ss_v_mine, buf_mine) && std::getline(ss_v_real, buf_real))
		{
			buf_mine_adjusted = equalizeDifferences(buf_mine);
			length_min = std::min(buf_mine.length(), buf_real.length());
			if (buf_mine_adjusted == buf_real)
			{
				for (size_t i = 0; i < length_min; i = i + (width - 1))
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
		if (buf_mine == buf_real)
			std::cout << std::endl << GREEN << "✔ all tests for vector passed" << RESET << std::endl;
		else
		{
			std::cout << std::endl << RED << "✘ some tests for vector failed" << RESET << std::endl;
			return (0);
		}
		return (1);
	}
	template <template <class T, class Allocator = std::allocator<T> > class Vector > void vectorTest();
	template <typename Vector>
	void printVector(Vector &v, std::ostream &os) const
	{
	    os << "v = { ";
	    for (unsigned long n = 0; n < v.size(); n++)
	        os << v.at(n) << ", ";
	    os << "}; \n";
	}
	template <typename Vector>
	void compareVectors(Vector &v1, Vector &v2)
	{
	    printVector(v1, oStream);
	    printVector(v2, oStream);
	    oStream << "(v1 == v2): " << (v1 == v2) << std::endl;
	    oStream << "(v1 != v2): " << (v1 != v2) << std::endl;
	    oStream << "(v1 < v2): " << (v1 < v2) << std::endl;
	    oStream << "(v1 > v2): " << (v1 > v2) << std::endl;
	    oStream << "(v1 <= v2): " << (v1 <= v2) << std::endl;
	    oStream << "(v1 >= v2): " << (v1 >= v2) << std::endl;
	}
    template <typename T>
    void execOnlyOnLinux(T arg)
    {
		(void) arg;
        #ifdef __linux__
            oStream << "v:back2: " << arg << std::endl;
        #else
            oStream << "this test only works on linux" << std::endl;
        #endif
    }
	template<typename T>
	struct is_const_pointer { static const bool value = false; };

	template<typename T>
	struct is_const_pointer<const T*> { static const bool value = true; };

	template <typename TIterator>
	struct is_const_iterator
	{
	    typedef typename std::iterator_traits<TIterator>::pointer pointer;
	    static const bool value = is_const_pointer<pointer>::value;
	};

	std::stringstream oStream;
	std::string equalizeDifferences(std::string buf_mine);
    void toOutput(std::string first, std::string second, size_t width, std::string color);

	class A {public: A(){a = 1;} int a;};
};

#include "VectorTester.hpp"

#endif

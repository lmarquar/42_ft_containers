#ifndef MYTESTER_HPP
# define MYTESTER_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <iomanip>
# include <cassert>
# include <climits>
# include "vector.hpp"

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
	
	private:
	template <typename Vector>
    void test()
    {
    //	Vector v_real;
        oStream << "GIVEN TESTS:" << std::endl;
    //    v_real.insert(v_real.begin(), 10);
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
/*         #ifdef __linux__
            oStream << "v:back2: " << v.back() << std::endl;
        #else
            oStream << "this test only works on linux" << std::endl;
        #endif */
        execOnlyOnLinux(v.back());
        oStream << "v.capa: " << v.capacity() << std::endl;
        oStream << "v.size: " << v.size() << std::endl;
        oStream << empty.capacity() << std::endl;
    
        // Print out the vector
        printVector(v);


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

        oStream << "Descr.: iterator tests:" << std::endl;
        iter = t.begin();
        t.insert(t.begin(), 20);
        t.insert(++iter, 10);
        t.insert(t.end(), 30);
        --iter;
        typename Vector::iterator iterCpy;
        oStream << "size: " << t.size() << std::endl;
        t.resize(t.size() - 1);
        oStream << "size: " << t.size() << std::endl;
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
        iter--;
    /*     for(size_t i = t.size() - 1; i >= 0; i++)
        {
            oStream << *iter << std::endl;
            iter--;
        } */
        iterCpy = iter;
        oStream << "iter:    " << *iter << std::endl;
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
	class A {public: A(){a = 1;} int a;};
	template <typename Vector>
    void printVector(Vector &v)
    {
        oStream << "v = { ";
        for (unsigned long n = 0; n < v.size(); n++)
            oStream << v.at(n) << ", ";
        oStream << "}; \n";
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
	public:
	int run();

	private:
	std::stringstream oStream;
	std::string equalizeDifferences(std::string buf_mine);
    void toOutput(std::string first, std::string second, size_t width, std::string color);
};

#endif
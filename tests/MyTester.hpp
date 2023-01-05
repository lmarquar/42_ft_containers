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
	template <template <class T, class Allocator = std::allocator<T> > class Vector >
    void test()
    {
		using std::swap;
		typedef typename Vector<int>::iterator iterator;
		typedef typename Vector<int>::const_iterator const_iterator;
		typedef typename Vector<int>::reverse_iterator reverse_iterator;
		typedef typename Vector<int>::const_reverse_iterator const_reverse_iterator;
        oStream << "Descr.: GIVEN TESTS:" << std::endl;
        typename Vector<int>::iterator iter;
		typename Vector<int>::iterator iter2;
        // Create a vector containing integers
        int arr[4] = {7, 5, 16, 8};
        Vector<int> v(arr, arr+4);
        iter = v.begin();
        Vector<int> empty;
        oStream << v.size() << std::endl;
        // Add two more integers to vector
        v.push_back(25);
        v.push_back(13);

        oStream << std::endl << "Descr.: MY TESTS: " << std::endl;
		oStream << *(v.data()) << std::endl;
        Vector<int> v2(arr, arr+3);
        oStream << "v2.capa(): " << v2.capacity() << std::endl;
        oStream << "Descr.: testing front and back function: " << std::endl;
        oStream << "front(): " <<  v.front() << std::endl;
        oStream << "back(): " << v.back() << std::endl;
        oStream << "clear()" << std::endl;
        v.clear();
        v.resize(20);
        oStream << "front(): " <<  v.front() << std::endl;
        oStream << "back(): " << v.back() << std::endl;
        oStream << v.capacity() << std::endl;
        oStream << v.size() << std::endl;
        v.clear();
        v.back();
        oStream << "v.capa: " << v.capacity() << std::endl;
        oStream << "v.size: " << v.size() << std::endl;
        oStream << empty.capacity() << std::endl;
        printVector(v, oStream);
        oStream << "Descr.: range input" << std::endl;
        int arr1[6] = {1, 2, 3, 4, 3, 2};
        int arr2[2] = {5, 6};
        try {
            Vector<int> t_wrong(arr1, arr2);
        } catch (std::length_error &e)
        {
            oStream << "caught length_error of type: " << e.what() << std::endl;
        }
        Vector<int> t(arr1, arr1+5);
        t.push_back(2);
        t.push_back(3);
        oStream << "size:     " << t.size() << std::endl;
        oStream << "capa: " << t.capacity() << std::endl;
        oStream << "max_size: " << "not identical, that's why not displayed" << std::endl;
        for(size_t i = 0; i < t.size(); i++)
            oStream << t.at(i) << std::endl;
        oStream << "vector[size() - 1]: " << t[t.size() - 1] << std::endl;
        oStream << "end of array" << std::endl;
        oStream << "back(): " << t.back() << std::endl;
        t.push_back(10);
        t.push_back(20);
        t.push_back(30);
        oStream << "Descr.: =operator():" << std::endl;
        Vector<int> vec;
        v = t;
        v.push_back(1);
        v.push_back(2);
        vec = v;
        oStream << vec.front() << std::endl;
        oStream << v.front() << std::endl;
        oStream << vec.back() << std::endl;
        oStream << v.back() << std::endl;
        oStream << v.at(0) << std::endl;
        oStream << v.at(1) << std::endl;
        oStream << v.at(2) << std::endl;
		v.push_back(1);
        oStream << v.back() << std::endl;
        oStream << vec.back() << std::endl;

        oStream << "Descr.: iterator tests:" << std::endl;
        iter = t.begin();
        --iter;
        typename Vector<int>::iterator iterCpy;
        oStream << "size: " << t.size() << std::endl;
        t.resize(t.size() - 1);
        oStream << "size: " << t.size() << std::endl;
        iter = t.begin();
        for(size_t i = 0; i < t.size(); i++)
        {
            oStream << *iter << " == " << t.at(i) << std::endl;
            iter++;
        }
        oStream << "*(--iterator)" << *(--iter) << std::endl;
        oStream << "*(--iterator)" << *(--iter) << std::endl;
        oStream << "*(++iterator)" << *(++iter) << std::endl;
        oStream << "*(iterator--)" << *(iter--) << std::endl;
        oStream << "*(iterator++)" << *(iter++) << std::endl;

        iter = t.end();
        iter--;
        iterCpy = iter;
        oStream << "iter:    " << *iter << std::endl;
        oStream << "iterCpy: " << *iterCpy << std::endl;
        oStream << "*(--iterCpy): " << *(--iterCpy) << std::endl;
        t.clear();
        try{
            for(size_t i = 0; i < 4; i++)
			{
                oStream << t.at(i) << std::endl;
			}
		} catch (std::out_of_range &e)
        {
            oStream << "catched Exception: " << e.what() << std::endl;
        }
        oStream << "capacity(): " << t.capacity() << std::endl;
        oStream << "size(): " << t.size() << std::endl;
        printVector(v, oStream);
		oStream << "is_const_iterator ? (iterator): " << is_const_iterator<iterator>::value << std::endl;
        iter = v.begin();
        oStream << *iter << std::endl;
        *iter = 100;
        oStream << *iter << std::endl;
        oStream << *(++iter) << std::endl;
        oStream << *(--iter) << std::endl;
		iter = v.end();
		oStream << *iter << std::endl;
		iter = v.begin() + 2;
		oStream << *iter << std::endl;
		oStream << *(iter.base()) << std::endl;
        oStream << "Descr.: const_iterator:" << std::endl;
		oStream << "is_const_iterator ? (const_iterator): " << is_const_iterator<const_iterator>::value << std::endl;
        const_iterator it_const;
        it_const = v.end();
        it_const--;
        oStream << *it_const << std::endl;
		oStream << *iter << std::endl;
		oStream << "test comparisons:" << std::endl;
		oStream << (it_const == iter) << std::endl;
		oStream << (it_const < iter) << std::endl;
		it_const = iter;
		oStream << (it_const == iter) << std::endl;
		oStream << (iter != it_const) << std::endl;
		oStream << *it_const << std::endl;
		oStream << "Descr.: reverse_iterator:" << std::endl;
		oStream << "is_const_iterator ? (reverse_iterator): " << is_const_iterator<reverse_iterator>::value << std::endl;
		reverse_iterator it_rev;
		printVector(v, oStream);
		it_rev = v.rbegin();
        oStream << *it_rev << std::endl;
        it_rev++;
        oStream << *it_rev << std::endl;
        it_rev = v.rend();
		oStream << *(v.data()) << std::endl;
        it_rev--;
		oStream << *it_rev << std::endl;
		it_rev--;
        oStream << *it_rev << std::endl;
		it_rev = it_rev - 1;
		oStream << *it_rev << std::endl;
        it_rev += 2;
        oStream << *it_rev << std::endl;
		it_rev = v.rbegin() + 1;
		oStream << "v.rbegin() + 1: " << *it_rev << std::endl;
		oStream << *(--it_rev) << "==" << *(v.rbegin()) << std::endl;
		oStream << *it_rev << std::endl;
		iter = it_rev.base();
		oStream << *iter << std::endl;
		reverse_iterator it_rev2(it_rev);
        oStream << *it_rev2 << std::endl;
		oStream << "Descr.: const_reverse_iterator:" << std::endl;
		oStream << "is_const_iterator ? (const_reverse_iterator): " << is_const_iterator<const_reverse_iterator>::value << std::endl;
		const_reverse_iterator it_const_rev = v.rbegin();
		oStream << *it_const_rev << std::endl;
		it_const_rev++;
		oStream << *it_const_rev << std::endl;
		it_const_rev = it_rev + 1;
		oStream << *it_const_rev << std::endl;
		oStream << "Descr.: iterator mixtures: " << std::endl;
		oStream << *it_const.base() << std::endl;
		it_const = it_const_rev.base();
		oStream << *it_const << std::endl;
		it_const++;
		oStream << *it_const << std::endl;
		it_const = it_const - 2;
		iter = v.begin();
		oStream << (it_const < iter) << std::endl;
		oStream << (it_const > iter) << std::endl;
		oStream << (it_const_rev < it_rev) << std::endl;
		it_const_rev++;
		oStream << (it_const_rev < it_rev) << std::endl;
		oStream << (it_const_rev != it_rev) << std::endl;
		it_const_rev -= 2;
		oStream << (it_const_rev == it_rev) << std::endl;
        oStream << "Descr.: more function Tests ^<^" << std::endl;
        oStream << "Descr.: insert()" << std::endl;
        iter = t.begin();
        t.insert(iter, 22);
        t.insert(++iter, 11);
        iter = t.insert(t.end(), 33);
		oStream << *iter << std::endl;
        printVector(t, oStream);
		t.insert((t.begin() + 1), 3, 87);
        printVector(t, oStream);
		printVector(v, oStream);
        t.insert(t.end(), v.begin(), (v.end() - 1));
        printVector(t, oStream);
        oStream << "Descr.: empty():" << std::endl;
        oStream << t.empty() << std::endl;
        oStream << vec.empty() << std::endl;
        oStream << v.empty() << std::endl;
        v.push_back(1);
        oStream << v.empty() << std::endl;
        v.clear();
        v.resize(1);
        oStream << v.empty() << std::endl;
		oStream << "Descr.: erase()" << std::endl;
        v.push_back(1);
        v.push_back(2);
		v.push_back(3);
		printVector(v, oStream);
        oStream << *(v.end() - 1) << std::endl;
		iter = v.erase(v.begin() + 1);
		oStream << *iter << std::endl;
		printVector(v, oStream);
		iter = v.erase(v.end() - 1);
		oStream << *iter << std::endl;
		printVector(v, oStream);
		v.push_back(2);
		v.push_back(3);
		iter = v.begin();
		iter2 = v.begin() + 2;
		iter = v.erase(iter, iter2);
		oStream << *iter << std::endl;
		printVector(v, oStream);
		iter = v.erase(v.begin(), v.end());
		oStream << *iter << std::endl;
		printVector(v, oStream);
		v = Vector<int>(arr, arr + 4);
		v.push_back(20);
		printVector(v, oStream);
        oStream << "Descr.: all the operators" << std::endl;
        compareVectors(v, v2);
        v2.clear();
        v2.insert(v2.begin(), v.begin(), v.end());
        compareVectors(v, v2);
		oStream << "Descr.: small functions" << std::endl;
		v.pop_back();
		printVector(v, oStream);
		v.swap(t);
		printVector(v, oStream);
		printVector(t, oStream);
		swap(t, v);
		oStream << v.max_size() << std::endl;
        t.assign(0, 10);
        printVector(t, oStream);
        t.assign(v.begin(), v.end());
        printVector(t, oStream);
 		oStream << "Descr.: trying with strings instead of numbers" << std::endl;
		std::string values[] = {"hello", "there"};
		Vector<std::string> strings(values, values + 1);
		strings.push_back("hellohello");
		strings.push_back("world");
		printVector(strings, oStream);
		strings.clear();
		printVector(strings, oStream);
    }

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

#endif

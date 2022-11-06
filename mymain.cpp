#include <iostream>
#include <vector>
#include "vector.hpp"

class A {public: A(){a = 1;} int a;};

template <typename Vector>
void test(Vector &t)
{
    t.push_back(2);
    t.push_back(3);
    std::cout << "size: " << t.size() << std::endl;
    for(size_t i = 0; i < t.size(); i++)
        std::cout << t.at(i) << std::endl;
    std::cout << "end of array" << std::endl;
    t.clear();
    try{
        for(size_t i = 0; i < 4; i++)
            std::cout << t.at(i) << std::endl;
    } catch (std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "back(): " << t.back() << std::endl;
    std::cout << "capacity(): " << t.capacity() << std::endl;
    std::cout << "size(): " << t.size() << std::endl;
    typename Vector::iterator iter;
    iter = t.begin();
    std::cout << *iter << std::endl;
}

int main()
{
    int i;
    ft::vector<int> v_mine;
    std::vector<int> v_real;

    i = 10;
    std::cout << "test for ft::vector: " << std::endl;
    test(v_mine);
    std::cout << std::endl << "test for std::vector: " << std::endl;
    test(v_real);
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

#include <iostream>
#include <vector>
#include "vector.hpp"

class A {public: A(){a = 1;} int a;};

/* template <typename Vector>
void test(Vector t)
{
    (void) t;
    t.push_back(2);
//    std::cout << t.at(0) << std::endl;
} */

int main()
{
    int i;
    ft::vector<int> v1;

    i = 10;
    test(v1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_front(1);
    for(size_t i = 0; i < v1.size(); i++)
        std::cout << v1.at((int)i) << std::endl;
    v1.clear();
    for(size_t i = 0; i < 4; i++)
        std::cout << v1.at((int)i) << std::endl;
    std::cout << "back(): " << v1.back() << std::endl;
    std::cout << "capacity(): " << v1.capacity() << std::endl;
    std::cout << "size(): " << v1.size() << std::endl;

    std::vector<A> v2;
    A a;
    a.a = 2;
    v2.push_back(a);
    v2.clear();
    std::cout << "A: " << v2.back().a << std::endl;

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

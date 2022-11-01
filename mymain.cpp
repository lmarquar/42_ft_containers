#include <iostream>
#include <vector>
#include "vector.hpp"
 
int main()
{
    ft::vector<int> v1;

    std::cout << v1.capacity() << std::endl;
    v1.push_back(10);
    std::cout << v1.size() << std::endl;
    

    std::cout << "start of real vector" << std::endl;
     // Create a vector containing integers
    int arr[4] = {7, 5, 16, 8};
    std::vector<int> v(arr, arr+4);
    std::vector<int> empty;

    std::cout << empty.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);
 
    // Print out the vector
    std::cout << "v = { ";
    for (unsigned long n = 0; n < v.size(); n++)
        std::cout << v.at(n) << ", ";
    std::cout << "}; \n";
}

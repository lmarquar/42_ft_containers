#include <iostream>
#include <vector>
 
int main()
{
    // Create a vector containing integers
    int arr[4] = {7, 5, 16, 8};
    std::vector<int> v(arr, arr+4);
 
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);
 
    // Print out the vector
    std::cout << "v = { ";
    for (unsigned long n = 0; n < v.size(); n++)
        std::cout << v.at(n) << ", ";
    std::cout << "}; \n";
}

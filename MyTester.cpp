#include "MyTester.hpp"

MyTester::MyTester()
{}

std::string MyTester::equalizeDifferences(std::string buf_mine)
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

int MyTester::run()
{
    std::cout << INT_MAX << std::endl;
    std::stringstream ss_v_mine;
    std::stringstream ss_v_real;
    std::string buf_mine;
    std::string buf_mine_adjusted;
    std::string buf_real;
/*     std::cout << "test for ft::vector: " << std::endl;
    test(v_mine, std::cout);
    std::cout << std::endl << "test for std::vector: " << std::endl;
    test(v_real, std::cout); */
    test<ft::vector<int> >();
    std::cout <<  oStream.str();
    oStream.clear();
    size_t width;
    size_t length_min;
    width = 50;
    test<ft::vector<int> >();
    ss_v_mine << oStream.str();
    oStream.clear();
    test<std::vector<int> >();
    ss_v_real << oStream.str();
    std::cout << BLUE << std::setw((int)width) << std::left << "real vector: " << "my vector: " << RESET << std::endl;
    while(std::getline(ss_v_mine, buf_mine) && std::getline(ss_v_real, buf_real))
    {
        buf_mine_adjusted = equalizeDifferences(buf_mine);
        length_min = std::min(buf_mine.length(), buf_real.length());
        if (buf_mine_adjusted == buf_real)
        {
            for (size_t i = 0; i < length_min; i = i + width - 2)
                std::cout << GREEN << std::setw((int)width) << std::left
                    << buf_real.substr(i, width - 2)
                    << buf_mine.substr(i, width - 2) << RESET << std::endl;
        }
        else
        {
            for (size_t i = 0; i < length_min; i = i + width - 2)
                std::cout << RED << std::setw((int)width) << std::left
                    << buf_real.substr(i, width - 2)
                    << buf_mine.substr(i, width - 2) << RESET << std::endl;
        }
    }
    buf_mine = equalizeDifferences(ss_v_mine.str());
    buf_real = ss_v_real.str();
    assert(buf_mine == buf_real);
    std::cout << std::endl << GREEN << "✔ all tests for vector pass" << RESET << std::endl;
    std::cout << "Some additional tests: " << std::endl;
    int onetothree[3] = {1, 2, 3};
    std::vector<int> test_vec(onetothree, onetothree+3);
    test_vec.insert(test_vec.end(), 4);
    test_vec.resize(test_vec.size() - 1);
    printVector(test_vec);
    return (0);
}


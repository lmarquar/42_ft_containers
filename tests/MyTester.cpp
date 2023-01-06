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

int MyTester::run(char kind)
{
	if (kind == 's')
	{
    	vectorTest<std::vector>();
    	std::cout <<  oStream.str();
    	oStream.str("");
    	std::cout << BLUE << "end for only std::vector testrun" << RESET << std::endl;
	}
	else if (kind == 'f')
	{
		vectorTest<ft::vector>();
		std::cout <<  oStream.str();
		oStream.str("");
		std::cout << BLUE << "end for only ft::vector testrun" << RESET << std::endl;
	}
	else
	{
		std::cout << BLUE << "VectorTest: " << RESET << std::endl;
		comparisonTest(&MyTester::vectorTest<ft::vector>, &MyTester::vectorTest<std::vector>);
		std::cout << BLUE << "MapTest: " << RESET << std::endl;
		comparisonTest(&MyTester::mapTest<ft::map>, &MyTester::mapTest<ft::map>);
	}
    return (0);
}

void MyTester::toOutput(std::string first, std::string second, size_t width, std::string color)
{
	if (first.substr(0, 7) == "Descr.:")
		std::cout << CYANUSCR << std::setw((int)width) << std::left
			<< first.substr(8, first.length()) << RESET
			<< "│" << CYANUSCR << std::setw((int)width) << std::left
			<< second.substr(8, second.length()) << RESET << std::endl;
	else
		std::cout << GREEN << std::setw((int)width) << std::left
			<< first << RESET << "│" << color << second << RESET << std::endl;
}

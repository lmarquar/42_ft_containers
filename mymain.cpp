#include "MyTester.hpp"

void toOutput(std::string first, std::string second, int width, std::string color)
{
	if (first.substr(0, 7) == "Descr.:")
		std::cout << CYANUSCR << std::setw(width) << std::left
			<< first.substr(8, first.length()) << RESET
			<< "│" << CYANUSCR << std::setw(width) << std::left
			<< second.substr(8, second.length()) << RESET << std::endl;
	else
		std::cout << GREEN << std::setw(width) << std::left
			<< first << RESET << "│" << color << second << RESET << std::endl;
}

int main()
{
	MyTester tester;

    tester.run();
	return (0);
}

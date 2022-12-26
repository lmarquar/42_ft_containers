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
    std::stringstream ss_v_mine;
    std::stringstream ss_v_real;
    std::string buf_mine;
    std::string buf_mine_adjusted;
    std::string buf_real;
	if (kind == 's')
	{
    	test<std::vector>();
    	std::cout <<  oStream.str();
    	oStream.str("");
    	std::cout << BLUE << "end for only std::vector testrun" << RESET << std::endl;
	}
	else if (kind == 'f')
	{
		test<ft::vector>();
		std::cout <<  oStream.str();
		oStream.str("");
		std::cout << BLUE << "end for only ft::vector testrun" << RESET << std::endl;
	}
	else
	{
		size_t width;
		size_t length_min;
		width = 50;
		test<std::vector>();
		ss_v_real << oStream.str();
		oStream.str("");
		test<ft::vector>();
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
		std::cout << "Some additional tests: " << std::endl;
		int onetothree[3] = {1, 2, 3};
		std::vector<int> test_vec(onetothree, onetothree+3);
		test_vec.insert(test_vec.end(), 4);
		test_vec.resize(test_vec.size() - 1);
		printVector(test_vec);
		std::vector<int> test_vec2;
		test_vec2.insert(test_vec2.begin(), 10);
		std::vector<int>::const_iterator it_const;
		std::vector<int>::iterator it;
		it = test_vec2.begin();
		it_const = test_vec2.begin();
		it_const = test_vec2.end();
		it_const--;
		std::cout << *it_const << std::endl;
		std::cout << *(++it_const) << std::endl;
		std::cout << (it_const > it) << std::endl;
		std::vector<int>::reverse_iterator it_rev;
		it_rev = std::vector<int>::reverse_iterator(it);
		std::cout << *it_rev << std::endl;
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


#include "MyTester.hpp"

int main(int argc, char **argv)
{
	MyTester tester;

	if (argc == 2)
    	tester.run(argv[1][0]);
	else
		tester.run('a');
	return (0);
}

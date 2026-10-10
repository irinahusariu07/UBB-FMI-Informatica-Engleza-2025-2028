#include "tests.h"

void testAdd()
{
	Repo r;
	Service s{ r };
	//Protein p{ "human", "abcd", "ab" };
	s.addProtein("human", "abcd", "ab");
	Protein* all = s.listAll();
	assert(all[1].getName() == "abcd");
}

void testAll()
{
	testAdd(); 
	std::cout << "TESTS PASSED!";
}

#include "tests.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	
#ifdef DEBUG
    std::cout << "Starging... (Debugging is enabled!)" << std::endl;
#endif

    Tests::test_everything();
    
	return 0;
}

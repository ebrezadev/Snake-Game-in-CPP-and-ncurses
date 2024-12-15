#include <iostream>
#ifdef __linux__
#include <cstring>
#include "engine.h"
#include "error.h"

int main()
{
	Engine &engine = Engine::getInstance();

	engine.execute();

	return 0;
}

#else
#ifdef __GNUC__
#warning "COMPILE ON LINUX"
#endif

int main()
{
	std::cout << "This program is written using 'ncurses.h'. Please compile and run on Linux." << std::endl;
	return 0;
}

#endif
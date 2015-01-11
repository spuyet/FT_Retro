#include <cstdlib>
#include <ctime>
#include "Core.hpp"
#include "MainMenu.hpp"

int
main()
{
	Core	core;

	std::srand(std::time(0));
	core.switchState(new MainMenu);
	core.run();
	return 0;
}
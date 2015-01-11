#include <cstdlib>
#include <ctime>
#include "Core.hpp"
#include "MainMenu.hpp"

int
main()
{
	Core		core;
	MainMenu*	menu;

	std::srand(std::time(0));
	menu = new MainMenu();
	menu->readScore();
	core.switchState(menu);
	core.run();
	return 0;
}
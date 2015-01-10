#include "Core.hpp"
#include "MainMenu.hpp"

int
main()
{
	Core	core;

	core.switchState(new MainMenu);
	core.run();
	return 0;
}
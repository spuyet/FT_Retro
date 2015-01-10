#include "MainMenu.hpp"
#include "Core.hpp"

MainMenu::MainMenu()
{

}

void
MainMenu::handleEvent(int ch)
{
	if (ch == '\033')
		Core::get().quit();
}

void
MainMenu::update()
{

}

void
MainMenu::render() const
{

}

MainMenu::~MainMenu()
{

}

MainMenu::MainMenu(const MainMenu& rhs)
{
	(void)rhs;
}

MainMenu&
MainMenu::operator=(const MainMenu& rhs)
{
	(void)rhs;
	return *this;
}

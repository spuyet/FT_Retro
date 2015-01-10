#include <ncurses.h>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Core.hpp"

Game::Game()
{

}

void
Game::handleEvent(int ch)
{
	if (ch == 27 && getch() == ERR)
		Core::get().switchState(new MainMenu);
}

void
Game::update()
{

}

void
Game::render() const
{

}

Game::~Game()
{

}

Game::Game(const Game& rhs)
{
	(void)rhs;
}

Game&
Game::operator=(const Game& rhs)
{
	(void)rhs;
	return *this;
}

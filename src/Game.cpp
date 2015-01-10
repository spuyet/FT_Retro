#include <ncurses.h>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Core.hpp"

Game::Game()
: _cooldown(0)
{

}

void
Game::handleEvent(int ch)
{
	switch (ch)
	{
		case 27:
			if (getch() == ERR)
				Core::get().switchState(new MainMenu);
			break;
		case KEY_DOWN:
			move(0, 1);
			break;
		case KEY_UP:
			move(0, -1);
			break;
		case KEY_RIGHT:
			move(1, 0);
			break;
		case KEY_LEFT:
			move(-1, 0);
			break;
	}
}

void
Game::move(int x, int y)
{
	if (_cooldown)
		return;
	_cooldown = 4;
	_player.setPos(_player.getX() + x, _player.getY() + y);
}

void
Game::update()
{
	_player.update();
	if (_cooldown)
		_cooldown--;
}

void
Game::render() const
{
	_player.render();
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

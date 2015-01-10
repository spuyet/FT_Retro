#include <ncurses.h>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Core.hpp"

Game::Game()
: _player(WIDTH / 8, HEIGHT / 2)
, _cooldown(0)
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
	int nx = _player.getX() + x;
	int ny = _player.getY() + y;
	if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
		return;
	_player.setPos(nx, ny);
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
	int x = COLS / 2 - (WIDTH + 4) / 2;
	int y = LINES / 2 - (HEIGHT + 2) / 2;
	attrset(COLOR_P(0, COLOR_WHITE));
	::move(y, x);
	hline(' ', WIDTH + 4);
	vline(' ', HEIGHT + 2);
	::move(y, x + 1);
	vline(' ', HEIGHT + 2);
	::move(y + HEIGHT + 1, x);
	hline(' ', WIDTH + 4);
	::move(y, WIDTH + 2 + x);
	vline(' ', HEIGHT + 2);
	::move(y, WIDTH + 3 + x);
	vline(' ', HEIGHT + 2);
	_player.render(x, y);
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

#include <ncurses.h>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Bullet.hpp"
#include "Core.hpp"

Game::Game()
: _player(WIDTH / 8, HEIGHT / 2)
, _mvCooldown(0)
, _shootCooldown(0)
{
	for (int i = 0; i < MAX_ENT; i++)
		_entities[i] = 0;
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
		case ' ':
			shoot();
			break;
	}
}

void
Game::move(int x, int y)
{
	if (_mvCooldown)
		return;
	_mvCooldown = 4;
	int nx = _player.getX() + x;
	int ny = _player.getY() + y;
	if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
		return;
	_player.setPos(nx, ny);
}

void
Game::shoot()
{
	if (_shootCooldown)
		return;
	_shootCooldown = 6;
	AEntity* bullet = spawn(new Bullet(_player.getX() + 1, _player.getY()));
	if (bullet)
		bullet->setSpeed(1.0f, 0.0f);
}

AEntity*
Game::spawn(AEntity* entity)
{
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i] == 0)
		{
			_entities[i] = entity;
			return entity;
		}
	}
	delete entity;
	return NULL;
}

void
Game::update()
{
	_player.update();
	if (_mvCooldown)
		_mvCooldown--;
	if (_shootCooldown)
		_shootCooldown--;
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i])
		{
			_entities[i]->update();
			const int x = _entities[i]->getX();
			const int y = _entities[i]->getY();
			if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			{
				delete _entities[i];
				_entities[i] = 0;
			}
		}
	}
}

void
Game::render() const
{
	const int x = COLS / 2 - (WIDTH + 4) / 2;
	const int y = LINES / 2 - (HEIGHT + 2) / 2;
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
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i])
			_entities[i]->render(x, y);
	}
	_player.render(x, y);
}

Game::~Game()
{
	for (int i = 0; i < MAX_ENT; i++)
		delete _entities[i];
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

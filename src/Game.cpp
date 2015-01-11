#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Bullet.hpp"
#include "Core.hpp"

Game::Game()
: _player(0, WIDTH / 8, HEIGHT / 2)
, _mvCooldown(0)
, _shootCooldown(0)
, _over(false)
, _difficulty(1)
, _nextWave(60)
{
	_player.setTeam(1);
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
	if (_mvCooldown || _over)
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
	if (_shootCooldown || _over)
		return;
	_shootCooldown = 6;
	AEntity* bullet = spawn(new Bullet(_player.getX() + 1, _player.getY()));
	if (bullet)
	{
		bullet->setSpeed(1.0f, 0.0f);
		bullet->setTeam(1);
	}
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
Game::destroy(int i)
{
	delete _entities[i];
	_entities[i] = 0;
}

void
Game::gameOver()
{
	_over = true;
}

void
Game::wave()
{
	if (_nextWave > 0)
	{
		_nextWave--;
		return;
	}
	int nbSpawn = _difficulty + std::rand() % (4 + _difficulty);
	while (nbSpawn--)
		spawnFoe();
	_nextWave = 60 + std::rand() % 120;
}

void
Game::spawnFoe()
{
	AEntity* foe = new Ship(1, WIDTH - 1, std::rand() % HEIGHT);
	foe->setSpeed(-0.3f, 0.0f);
	spawn(foe);
}

void
Game::update()
{
	if (_over)
		return;
	wave();
	_player.update();
	if (_mvCooldown)
		_mvCooldown--;
	if (_shootCooldown)
		_shootCooldown--;
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i] && _player.getTeam() != _entities[i]->getTeam()
			&& _player.getX() == _entities[i]->getX()
			&& _player.getY() == _entities[i]->getY())
		{
			destroy(i);
			gameOver();
		}
	}
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i])
		{
			bool alive = true;

			_entities[i]->update();
			_entities[i]->ai(this, &_player);
			for (int j = i + 1; j < MAX_ENT; j++)
			{
				if (!_entities[j])
					continue;
				if (_entities[i]->getTeam() != _entities[j]->getTeam()
					&& _entities[i]->getX() == _entities[j]->getX()
					&& _entities[i]->getY() == _entities[j]->getY())
				{
					alive = false;
					destroy(i);
					destroy(j);
				}
				if (!alive)
					break;
			}
			if (!alive)
				continue;
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
	if (!_over)
		_player.render(x, y);
	else
	{
		attrset(COLOR_P(COLOR_RED, 0) | A_BOLD);
		const char* str = "GAME OVER";
		::move(LINES / 2, COLS / 2 - std::strlen(str) / 2);
		addstr(str);
	}
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

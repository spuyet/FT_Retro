#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Bullet.hpp"
#include "Core.hpp"

Game::Game()
: _player(0, WIDTH / 8, HEIGHT / 2)
, _mvCooldown(0)
, _shootCooldown(0)
, _over(false)
, _difficulty(0)
, _timer(0)
, _nextWave(60)
, _score(0)
, _acc(0)
, _ultra(3000)
, _ultraDuration(0)
, _lives(2)
, _spawnDuration(0)
, _kills(0)
, _mul(1)
, _timeElapsed(0)
, _boss(CLEAR)
, _bossLife(0)
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
				goToMenu();
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
		case 'x':
		case 'u':
			ultra();
			break ;
	}
}

void
Game::move(int x, int y)
{
	if (_mvCooldown > (y ? 0 : 2) || _over || _ultraDuration || _spawnDuration > 4 * 60)
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
	if (_shootCooldown || _over || _ultraDuration || _spawnDuration)
		return;
	_shootCooldown = 6;
	AEntity* bullet = spawn(new Bullet(0, _player.getX(), _player.getY()));
	if (bullet)
	{
		bullet->setSpeed(0.99f, 0.0f);
		bullet->setTeam(1);
	}
}

void
Game::ultra()
{
	if (_ultra < 3000 || _over || _spawnDuration)
		return ;
	_ultra = 0;
	_ultraDuration = 180;
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
	int oldScore = _score;
	int points = _entities[i]->getScore();
	if (points)
	{
		if (_boss == SPAWNED)
		{
			_bossLife--;
			if (_bossLife)
				return;
			_boss = CLEAR;
			for (int i = 0; i < MAX_ENT; i++)
			{
				delete _entities[i];
				_entities[i] = 0;
			}
			return;
		}
		_kills++;
	}
	if (_kills >= 10 * _mul)
	{
		_kills = 0;
		_mul++;
	}
	_score += points * _mul;
	if (oldScore / 5000 != _score / 5000)
		_lives++;
	if (_score > _best)
		_best = _score;
	delete _entities[i];
	_entities[i] = 0;
}

void
Game::gameOver()
{
	if (_spawnDuration)
		return ;
	_ultraDuration = 0;
	if (_lives)
	{
		_lives--;
		_spawnDuration = 5 * 60;
		_player.setPos(WIDTH / 8, HEIGHT / 2);
		_mul = 1;
		_kills = 0;
		_ultra = 3000;
	}
	else
		_over = true;
}

void
Game::wave()
{
	if (_boss)
		return;
	if (_nextWave > 0)
	{
		_nextWave--;
		return;
	}
	int nbSpawn = 1 + std::rand() % 3 + std::rand() % 3;
	while (nbSpawn--)
		spawnFoe();
	_nextWave = (120 + std::rand() % 140) / (_difficulty * 0.4f);
}

void
Game::spawnFoe()
{
	AEntity* foe = new Ship(Ship::pickShip(), WIDTH - 1, std::rand() % HEIGHT);
	foe->setSpeed(-0.3f, 0.0f);
	spawn(foe);
}

void
Game::update()
{
	if (_over)
	{
		_acc++;
		return;
	}
	if (_boss == WAITING && canBossSpawn())
		spawnBoss();
	_timeElapsed++;
	if (_ultra < 3000 && _ultraDuration == 0)
		_ultra++;
	if (_ultraDuration)
		_ultraDuration--;
	if (_spawnDuration)
		_spawnDuration--;
	if (_timer)
	{
		if (!_boss)
			_timer--;
	}
	else
	{
		_difficulty++;
		_timer = 800 * _difficulty;
		if (_difficulty % 1 == 0)
			_boss = WAITING;
	}
	wave();
	_player.update();
	if (_mvCooldown)
		_mvCooldown--;
	if (_shootCooldown)
		_shootCooldown--;
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (!_entities[i])
			continue;
		if (_ultraDuration && _entities[i]->getX() > _player.getX()
			&& _entities[i]->getY() >= _player.getY() - 1
			&& _entities[i]->getY() <= _player.getY() + 1)
		{
			if (_boss != SPAWNED || _entities[i]->getScore() == 0 || _timeElapsed % 20 == 0)
				destroy(i);
			continue;
		}
		if (_player.getTeam() != _entities[i]->getTeam()
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
			for (int j = 0; j < MAX_ENT; j++)
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
	for (int i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i])
			_entities[i]->render(x, y);
	}
	if (!_over && _spawnDuration <= 4 * 60 && (~_spawnDuration & (1 << 5)
		|| _spawnDuration == 0))
		_player.render(x, y);
	else if (_over)
	{
		attrset(COLOR_P(COLOR_RED, 0) | A_BOLD);
		const char* str = "GAME OVER";
		::move(LINES / 2, COLS / 2 - std::strlen(str) / 2);
		addstr(str);
	}
	attrset(COLOR_P(COLOR_YELLOW, 0));
	::move(y + HEIGHT + 2, x);
	printw("SCORE %08lld", _score);
	::move(y + HEIGHT + 3, x);
	printw("BEST  %08lld", _best);
	if (_mul > 1)
	{
		attrset(A_BOLD | COLOR_P(0, 0));
		::move(y + HEIGHT + 2, x + 15);
		printw("x%d", _mul);
	}
	attrset(COLOR_P(COLOR_WHITE, 0) | A_BOLD);
	::move(y + HEIGHT + 2, x + 20);
	printw("LEVEL %2d", _difficulty);
	::move(y + HEIGHT + 3, x + 20);
	int s = std::ceil(_timer / 60.0f);
	if (!_boss)
		printw("NEXT IN %02d:%02d", s / 60, s % 60);
	else
		addstr("NEXT IN --:--");
	::move(y + HEIGHT + 2, x + WIDTH - 24);
	addstr("ULTRA |                    |");
	::move(y + HEIGHT + 3, x + WIDTH - 6);
	printw("LIVES %4d", _lives);
	attrset(COLOR_P(0, COLOR_CYAN));
	::move(y + HEIGHT + 2, x + WIDTH - 17);
	hline(' ', _ultra * 20 / 3000);

	if (_ultraDuration)
	{
		::move(y + _player.getY() + 1, x + _player.getX() + 3);
		attrset(COLOR_P(0, COLOR_WHITE));
		hline(' ', WIDTH - _player.getX() - 1);
		attrset(COLOR_P(0, COLOR_CYAN));
		::move(y + _player.getY(), x + _player.getX() + 3);
		hline(' ', WIDTH - _player.getX() - 1);
		::move(y + _player.getY() + 2, x + _player.getX() + 3);
		hline(' ', WIDTH - _player.getX() - 1);
	}
	if (_over && _best == _score && _best)
	{
		const char* str = "NEW  HIGHSCORE!";
		::move(LINES / 2 + 1, COLS / 2 - std::strlen(str) / 2);
		attrset(COLOR_P(COLOR_YELLOW, 0) | A_BOLD);
		if (_acc & (1 << 5))
			addstr(str);
	}

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

	attron(A_BOLD);
	::move(y + HEIGHT + 1, x + WIDTH / 2 - 2);
	printw("%02d:%02d", _timeElapsed / 3600, (_timeElapsed / 60) % 60);

	if (_boss == SPAWNED)
	{
		const char* str1 = "BOSS";
		const char* str2 = "|                                        |";

		attrset(COLOR_P(COLOR_WHITE, 0) | A_BOLD);
		::move(y + HEIGHT + 2, x + WIDTH / 2 - std::strlen(str1) / 2);
		addstr(str1);
		::move(y + HEIGHT + 3, x + WIDTH / 2 - std::strlen(str2) / 2);
		addstr(str2);
		attrset(COLOR_P(0, COLOR_RED));
		::move(y + HEIGHT + 3, x + WIDTH / 2 - std::strlen(str2) / 2 + 1);
		hline(' ', _bossLife * 40 / (_difficulty * 15));
	}
}

void
Game::setBest(long long score)
{
	_best = score;
}

void
Game::goToMenu()
{
	MainMenu* menu = new MainMenu();

	menu->setHighScore(_best);
	Core::get().switchState(menu);
}

bool
Game::canBossSpawn() const
{
	for (size_t i = 0; i < MAX_ENT; i++)
	{
		if (_entities[i] && _entities[i]->getScore())
			return false;
	}
	return true;
}

void
Game::spawnBoss()
{
	AEntity* boss = new Ship(7, WIDTH - 30, HEIGHT / 2);

	spawn(boss);
	_boss = SPAWNED;
	_bossLife = _difficulty * 15;
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

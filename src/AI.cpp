#include <cstdlib>
#include <cmath>
#include "AI.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"

void
ai::dumbShip(Game* game, Ship* player, AEntity* me)
{
	(void)player;
	int acc = me->getAcc();
	acc--;
	if (acc <= 0)
	{
		acc = 80 + std::rand() % 120;
		AEntity* bullet = new Bullet(1, me->getX(), me->getY());
		bullet->setSpeed(-0.99f, 0.0f);
		game->spawn(bullet);
	}
	me->setAcc(acc);
}

void
ai::station(Game* game, Ship* player, AEntity* me)
{
	(void)player;
	if (me->getState() == 0)
	{
		me->setState(1);
		me->setSpeed(-0.1f, 0);
	}
	if (me->getAcc() == 150)
	{
		me->setAcc(0);
		for (int i = 0; i < 3; i++)
		{
			AEntity* b = new Bullet(2, me->getX() - i, me->getY());
			b->setSpeed(-3, 0);
			game->spawn(b);
		}
	}
	else
		me->setAcc(me->getAcc() + 1);
}

void
ai::asteroid(Game* game, Ship* player, AEntity* me)
{
	float	alpha;

	(void)game;
	(void)player;
	if (me->getState() == 0)
	{
		me->setState(1);
		alpha = ((std::rand() % 100) - 50) * 0.01f;
		me->setSpeed(-std::cos(alpha) * 0.1f, std::sin(alpha) * 0.1f);
	}
}

void
ai::ghost(Game* game, Ship* player, AEntity* me)
{
	(void)game;
	if (me->getState() == 0)
	{
		me->setState(1);
		float alpha = ((std::rand() % 100) - 50) * 0.01f;
		me->setSpeed(-std::cos(alpha) * 0.3f, std::sin(alpha) * 0.3f);
	}
	float dx = player->getX() - me->getX();
	float dy = player->getY() - me->getY();
	float d = dx * dx + dy * dy;
	float sx = me->getSpeedX() + (0.2f / d) * dx;
	float sy = me->getSpeedY() + (0.2f / d) * dy;
	float m = std::sqrt(sx * sx + sy * sy);
	sx /= m;
	sy /= m;
	me->setSpeed(sx * 0.5f, sy * 0.5f);
}

void
ai::poseidon(Game* game, Ship* player, AEntity* me)
{
	(void)player;
	int acc = me->getAcc();
	acc--;
	if (acc <= 0)
	{
		acc = 100 + std::rand() % 140;
		AEntity* bullet = new Bullet(1, me->getX(), me->getY());
		AEntity* up = new Bullet(3, me->getX(), me->getY());
		AEntity* down = new Bullet(4, me->getX(), me->getY());
		bullet->setSpeed(-0.99f, 0.0f);
		up->setSpeed(-0.65f, -0.25f);
		down->setSpeed(-0.65f, 0.25f);
		game->spawn(bullet);
		game->spawn(up);
		game->spawn(down);
	}
	me->setAcc(acc);
}

void
ai::lord(Game* game, Ship* player, AEntity* me)
{
	(void)player;
	if (me->getX() < WIDTH / 2)
	{
		if (me->getState() == 0)
		{
			AEntity* left = new Bullet(5, me->getX() - 1, me->getY());
			AEntity* right = new Bullet(6, me->getX() + 1, me->getY());
			game->spawn(left);
			game->spawn(right);
			me->setState(1);
		}
		me->setSpeed(0, 0);
		int acc = me->getAcc() + 1;
		if (acc >= 256)
			acc = 0;
		me->setAcc(acc);
		AEntity* bullet = new Bullet(2, me->getX(), me->getY());
		float a = (M_PI * acc / 128.0f);
		bullet->setSpeed(std::cos(a), std::sin(a));
		game->spawn(bullet);
	}
	else
		me->setSpeed(-0.5f, 0);
}

static void
bossCreateShield(Game* game)
{
	for (int x = 0; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
			game->spawn(new Ship(9, WIDTH - 33 + x, HEIGHT / 2 + y));
	}
}

void
ai::boss(Game* game, Ship* player, AEntity* me)
{
	(void)player;
	if (me->getState() == 0)
	{
		me->setState(1);
		game->spawn(new Ship(8, WIDTH - 1, 0));
		game->spawn(new Ship(8, WIDTH - 1, HEIGHT - 1));
		bossCreateShield(game);
	}
	int acc = me->getAcc() + 1;
	if (acc % 60 == 0)
	{
		int y = std::rand() % 3 - 1;
		me->setPos(WIDTH - 30, HEIGHT / 2 + y);
	}
	if (acc == 240)
	{
 		acc = 0;
 		int st = me->getState();
 		switch (st)
 		{
 			case 1:
 			case 5:
 			case 7:
 				for (int i = 0; i < 4; i++)
 					game->spawn(new Ship(10, me->getX(), me->getY()));
 				break;
 			case 2:
 			case 9:
 				for (int i = -1; i <= 1; i++)
 					game->spawn(new Ship(11, WIDTH - 30, HEIGHT / 2 + i));
 				break;
 			case 3:
 			case 8:
 				bossCreateShield(game);
 				break;
 			case 4:
 			case 6:
 				for (int i = 0; i < 64; i++)
 				{
 					float a = M_PI * i / 32.0f;
 					game->spawn(new Ship(9, player->getX() + std::cos(a) * 8, player->getY() + std::sin(a) * 4));
 				}
 		}
 		st++;
 		if (st > 9)
 			st = 1;
 		me->setState(st);
	}
	me->setAcc(acc);
}

void
ai::bossShield(Game* game, Ship* player, AEntity* me)
{
	(void)game;
	(void)player;
	(void)me;
}

void
ai::bossBomb(Game* game, Ship* player, AEntity* me)
{
	(void)game;
	if (me->getState() == 0)
	{
		me->setState(1);
		float alpha = ((std::rand() % 100) - 50) * 0.01f;
		me->setSpeed(-std::cos(alpha) * 0.3f, std::sin(alpha) * 0.3f);
		me->setAcc(120 + std::rand() % 60);
	}
	me->setAcc(me->getAcc() - 1);
	if (me->getAcc() == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			float a = (M_PI * i / 4.0f);
			AEntity* b = new Bullet(2, me->getX(), me->getY());
			b->setSpeed(std::cos(a), std::sin(a));
			game->spawn(b);
		}
	}
	float dx = player->getX() - me->getX();
	float dy = player->getY() - me->getY();
	float d = dx * dx + dy * dy;
	float sx = me->getSpeedX() + (0.2f / d) * dx;
	float sy = me->getSpeedY() + (0.2f / d) * dy;
	float m = std::sqrt(sx * sx + sy * sy);
	sx /= m;
	sy /= m;
	me->setSpeed(sx * 0.6f, sy * 0.6f);
}

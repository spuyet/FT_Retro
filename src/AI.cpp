#include <cstdlib>
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
		AEntity* bullet = new Bullet(me->getX(), me->getY());
		bullet->setSpeed(-0.99f, 0.0f);
		game->spawn(bullet);
	}
	me->setAcc(acc);
}

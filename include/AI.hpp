#ifndef AI_H
#define AI_H

class Game;
class Ship;
class AEntity;

namespace ai
{
	typedef void (*func)(Game*, Ship*, AEntity*);

	// Ships

	void	dumbShip(Game* game, Ship* player, AEntity* me);
}

#endif
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
	void	station(Game* game, Ship* player, AEntity* me);
	void	asteroid(Game* game, Ship* player, AEntity* me);
	void	ghost(Game* game, Ship* player, AEntity* me);
	void	poseidon(Game* game, Ship* player, AEntity* me);
	void	lord(Game* game, Ship* player, AEntity* me);
}

#endif
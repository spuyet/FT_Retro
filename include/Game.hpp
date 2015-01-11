#ifndef GAME_H
#define GAME_H

#define WIDTH	(120)
#define	HEIGHT	(30)

#define MAX_ENT	(256)

#include "IGameState.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"

class Game : public IGameState
{

public:

	Game();

	void		handleEvent(int ch);
	void		move(int x, int y);
	void		shoot();
	AEntity*	spawn(AEntity* entity);
	void		destroy(int i);
	void		gameOver();
	void		wave();
	void		spawnFoe();
	void		update();
	void		render() const;

	~Game();

private:

	Game(const Game& rhs);
	Game&	operator=(const Game& rhs);

	Ship		_player;
	AEntity*	_entities[MAX_ENT];
	int			_mvCooldown;
	int			_shootCooldown;
	bool		_over;
	int			_difficulty;
	int			_nextWave;
};

#endif
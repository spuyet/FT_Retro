#ifndef GAME_H
#define GAME_H

#define WIDTH	(120)
#define	HEIGHT	(30)

#define MAX_ENT	(2048)

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
	void		ultra();
	AEntity*	spawn(AEntity* entity);
	void		destroy(int i);
	void		gameOver();
	void		wave();
	void		spawnFoe();
	void		update();
	void		render() const;
	void		setBest(long long score);
	void		goToMenu();
	bool		canBossSpawn() const;
	void		spawnBoss();

	~Game();

private:

	Game(const Game& rhs);
	Game&	operator=(const Game& rhs);

	enum boss_t
	{
		CLEAR = 0,
		WAITING,
		SPAWNED
	};

	Ship		_player;
	AEntity*	_entities[MAX_ENT];
	int			_mvCooldown;
	int			_shootCooldown;
	bool		_over;
	int			_difficulty;
	int			_timer;
	int			_nextWave;
	long long	_score;
	long long	_best;
	int			_acc;
	int			_ultra;
	int			_ultraDuration;
	int			_lives;
	int			_spawnDuration;
	int			_kills;
	int			_mul;
	int			_timeElapsed;
	boss_t		_boss;
	int			_bossLife;
};

#endif
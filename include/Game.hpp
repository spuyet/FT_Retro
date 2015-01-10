#ifndef GAME_H
#define GAME_H

#include "IGameState.hpp"
#include "Ship.hpp"

class Game : public IGameState
{

public:

	Game();

	void	handleEvent(int ch);
	void	move(int x, int y);
	void	update();
	void	render() const;

	~Game();

private:

	Game(const Game& rhs);
	Game&	operator=(const Game& rhs);

	Ship	_player;
	int		_cooldown;

};

#endif
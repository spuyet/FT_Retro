#ifndef GAME_H
#define GAME_H

#include "IGameState.hpp"

class Game : public IGameState
{

public:

	Game();

	void	handleEvent(int ch);
	void	update();
	void	render() const;

	~Game();

private:

	Game(const Game& rhs);
	Game&	operator=(const Game& rhs);

};

#endif
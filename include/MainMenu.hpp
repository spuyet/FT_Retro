#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <cstdlib>
#include "IGameState.hpp"

class MainMenu : public IGameState
{
public:
	MainMenu();

	void	handleEvent(int ch);
	void	update();
	void	render() const;
	void	action();
	void	setHighScore(long long score);

	~MainMenu();

private:
	MainMenu(const MainMenu& rhs);
	MainMenu&	operator=(const MainMenu& rhs);

	size_t		_select;
	int			_color;
	long long 	_highScore;
};

#endif
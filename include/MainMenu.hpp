#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "IGameState.hpp"

class MainMenu : public IGameState
{
public:
	MainMenu();

	void	handleEvent(int ch);
	void	update();
	void	render() const;

	~MainMenu();

private:
	MainMenu(const MainMenu& rhs);
	MainMenu&	operator=(const MainMenu& rhs);

};

#endif
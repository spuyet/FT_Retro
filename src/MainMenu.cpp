#include <cstring>
#include <ncurses.h>
#include <fstream>
#include "MainMenu.hpp"
#include "Game.hpp"
#include "Core.hpp"

MainMenu::MainMenu()
: _select(0)
, _color(1)
{

}

void
MainMenu::handleEvent(int ch)
{
	switch (ch)
	{
		case 27:
			if (getch() == ERR)
				Core::get().quit();
			break;
		case KEY_UP:
		case KEY_DOWN:
			_select = 1 - _select;
			break;
		case '\n':
			action();
			break;
	}
}

void
MainMenu::update()
{
	_color++;
	if (_color > 6)
		_color = 1;
}

void
MainMenu::render() const
{
	static const char* menu[] = {
		" New Game ",
		" Quit "
	};

	static const char* title[] = {
		"********************************************",
		"**                                        **",
		"**    ### ###   #### ### ### #### ####    **",
		"**    #    #    #  # #    #  #  # #  #    **",
		"**    ##   #    ###  ##   #  ###  #  #    **",
		"**    #    #    #  # #    #  #  # #  #    **",
		"**    #    #    #  # ###  #  #  # ####    **",
		"**                                        **",
		"********************************************"
	};

	size_t maxTitle = sizeof(title) / sizeof(title[0]);
	for (size_t i = 0; i < maxTitle; i++)
	{
		move(6 + i, COLS / 2 - std::strlen(title[i]) / 2);
		for (size_t j = 0; j < std::strlen(title[i]); j++)
		{
			if (title[i][j] == '#')
				attrset(COLOR_P(0, _color));
			else if (title[i][j] == '*')
				attrset(COLOR_P(0, COLOR_WHITE));
			else
				attrset(COLOR_P(0, COLOR_BLACK));
			addch(' ');
		}
	}

	attrset(COLOR_P(COLOR_YELLOW, 0) | A_BOLD);

	move(LINES - 3, COLS / 2 - 7);
	printw("HIGHSCORE %08lld", _highScore);

	attrset(COLOR_PAIR(0));

	size_t max = sizeof(menu) / sizeof(menu[0]);
	for (size_t i = 0; i < max; i++)
	{
		move(LINES / 2 - max / 2 + i, COLS / 2 - std::strlen(menu[i]) / 2);
		_select == i ? attron(A_REVERSE) : attroff(A_REVERSE);
		addstr(menu[i]);
	}
}

void
MainMenu::action()
{
	if (_select == 0)
	{
		Game* game = new Game();

		game->setBest(_highScore);
		Core::get().switchState(game);
	}
	else
		Core::get().quit();
}

void
MainMenu::setHighScore(long long highScore)
{
	_highScore = highScore;
	saveScore();
}

void
MainMenu::readScore()
{
	std::ifstream f("ft_retro.sav");
	f >> _highScore;
}

void
MainMenu::saveScore() const
{
	std::ofstream f("ft_retro.sav");
	f << _highScore;
}

MainMenu::~MainMenu()
{

}

MainMenu::MainMenu(const MainMenu& rhs)
{
	(void)rhs;
}

MainMenu&
MainMenu::operator=(const MainMenu& rhs)
{
	(void)rhs;
	return *this;
}

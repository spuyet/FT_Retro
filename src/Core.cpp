#include <ctime>
#include <cstring>
#include <unistd.h>
#include <ncurses.h>
#include "Core.hpp"
#include "Game.hpp"
#include "IGameState.hpp"

Core::Core()
: _running(false)
, _state(0)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
	keypad(stdscr, TRUE);
	ESCDELAY = 5;
	start_color();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			init_pair(COLOR(i, j), i, j);
	}
	_coreSingleton = this;
}

void
Core::run()
{
	const int timePerFrame = 1000000 / 60;
	if (_state == 0)
		return;
	_running = true;
	while (_running)
	{
		clock_t before = clock();	
		int ch;
		if (0 && (COLS < WIDTH + 4 || LINES < HEIGHT + 5))
		{
			askResize();
			continue;
		}
		while ((ch = getch()) != ERR)
			_state->handleEvent(ch);
		_state->update();
		erase();
		_state->render();
		refresh();
		clock_t after = clock();
		int elapsed = after - before;
		mvprintw(0, 0, ""); // Dummy write to update buffer.
		if (elapsed < timePerFrame)
			usleep(timePerFrame - elapsed);
	}
}

void
Core::quit()
{
	_running = false;
}

void
Core::switchState(IGameState* state)
{
	delete _state;
	_state = state;
}

void
Core::askResize()
{
	const char* str = "RESIZE (MOTHERFUCKER) !";
	erase();
	attrset(COLOR_P(COLOR_RED, 0) | A_BOLD);
	move(LINES / 2, COLS / 2 - std::strlen(str) / 2);
	addstr(str);
	refresh();
}

Core::~Core()
{
	delete _state;
	endwin();
}

Core&
Core::get()
{
	return *_coreSingleton;
}

Core::Core(const Core& rhs)
{
	(void)rhs;
}

Core&
Core::operator=(const Core& rhs)
{
	(void)rhs;
	return *this;
}

Core*	Core::_coreSingleton = 0;
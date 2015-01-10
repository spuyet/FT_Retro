#include <ctime>
#include <unistd.h>
#include <ncurses.h>
#include "Core.hpp"
#include "IGameState.hpp"

Core::Core()
: _running(false)
, _state(0)
{
	initscr();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	ESCDELAY = 5;
	_coreSingleton = this;
}

void
Core::run()
{
	const float timePerFrame = 1.0f / 60.0f;
	if (_state == 0)
		return;
	_running = true;
	while (_running)
	{
		clock_t before = clock();	
		int ch;
		while ((ch = getch()) != ERR)
			_state->handleEvent(ch);
		_state->update();
		_state->render();
		clock_t after = clock();
		float elapsed = static_cast<float>(after - before) / CLOCKS_PER_SEC;
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

Core::~Core()
{
	endwin();
	delete _state;
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
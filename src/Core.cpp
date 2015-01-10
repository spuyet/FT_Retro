#include "Core.hpp"
#include "IGameState.hpp"

Core::Core()
: _running(false)
, _state(0)
{

}

void
Core::run()
{
	if (_state == 0)
		return;
	_running = true;
	while (_running)
	{

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
	_state = state;
}

Core::~Core()
{
	delete _state;
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
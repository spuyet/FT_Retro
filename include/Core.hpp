#ifndef CORE_H
#define CORE_H

class IGameState;

class Core
{
public:

	Core();

	void	run();
	void	quit();
	void	switchState(IGameState* state);

	~Core();

	static Core&	get();

private:

	Core(const Core& rhs);
	Core&	operator=(const Core& rhs);

	bool			_running;
	IGameState*		_state;
	static Core*	_coreSingleton;

};

#endif
#ifndef IGAME_STATE_H
#define IGAME_STATE_H

class IGameState 
{

public:

	virtual void	handleEvent(int ch) = 0;
	virtual void	update() = 0;
	virtual void	render() const = 0;

	virtual ~IGameState(){};

};

#endif
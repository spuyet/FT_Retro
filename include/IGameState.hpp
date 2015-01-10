#ifndef IGAME_STATE_H
#define IGAME_STATE_H

class IGameState 
{

public:

	virtual handleEvent(int ch) = 0;
	virtual update() = 0;
	virtual render() const = 0;

	virtual ~IGameState(){};

};

#endif
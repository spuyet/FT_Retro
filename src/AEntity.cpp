#include <ncurses.h>
#include "AEntity.hpp"
#include "Game.hpp"

AEntity::AEntity()
: _x(0)
, _y(0)
, _speedX(0)
, _speedY(0)
, _team(0)
{

}

AEntity::AEntity(float x, float y)
: _x(x)
, _y(y)
, _speedX(0)
, _speedY(0)
, _team(0)
{

}

AEntity::AEntity(const AEntity& rhs)
: _x(rhs._x)
, _y(rhs._y)
, _speedX(rhs._speedX)
, _speedY(rhs._speedY)
, _team(rhs._team)
{

}

AEntity&
AEntity::operator=(const AEntity& rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_speedX = rhs._speedX;
	_speedY = rhs._speedY;
	_team = rhs._team;
	return *this;
}

int
AEntity::getX() const
{
	return _x;
}

int
AEntity::getY() const
{
	return _y;
}

float
AEntity::getSpeedX() const
{
	return _speedX;
}

float
AEntity::getSpeedY() const
{
	return _speedY;
}

int
AEntity::getTeam() const
{
	return _team;
}

void
AEntity::setPos(float x, float y)
{
	_x = x;
	_y = y;
}

void
AEntity::setSpeed(float x, float y)
{
	_speedX = x;
	_speedY = y;
}

void
AEntity::setTeam(int team)
{
	_team = team;
}

void
AEntity::update()
{
	_x += _speedX;
	_y += _speedY;
}

void
AEntity::render(int x, int y) const
{
	if (_x < 0 || _x >= WIDTH || _y < 0 || _y >= HEIGHT)
		return;
	move(_y + y + 1, _x + x + 2);
	attrset(getAttr());
	addch(getCh());
}

AEntity::~AEntity()
{

}

#include <ncurses.h>
#include "AEntity.hpp"

AEntity::AEntity()
: _x(0)
, _y(0)
, _speedX(0)
, _speedY(0)
{

}

AEntity::AEntity(float x, float y)
: _x(x)
, _y(y)
, _speedX(0)
, _speedY(0)
{

}

AEntity::AEntity(const AEntity& rhs)
: _x(rhs._x)
, _y(rhs._y)
, _speedX(rhs._speedX)
, _speedY(rhs._speedY)
{

}

AEntity&
AEntity::operator=(const AEntity& rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_speedX = rhs._speedX;
	_speedY = rhs._speedY;
	return *this;
}

float
AEntity::getX() const
{
	return _x;
}

float
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
AEntity::update()
{
	_x += _speedX;
	_y += _speedY;
}

void
AEntity::render(int x, int y) const
{
	move(_y + y + 1, _x + x + 2);
	attrset(getAttr());
	addch(getCh());
}

AEntity::~AEntity()
{

}

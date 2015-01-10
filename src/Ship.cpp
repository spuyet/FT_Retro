#include <ncurses.h>
#include "Ship.hpp"
#include "Core.hpp"

Ship::Ship()
{

}

Ship::Ship(float x, float y)
: AEntity(x, y)
{

}

Ship::Ship(const Ship& rhs)
: AEntity(rhs)
{

}

Ship&
Ship::operator=(const Ship& rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_speedX = rhs._speedX;
	_speedY = rhs._speedY;
	return *this;
}

int
Ship::getAttr() const
{
	return A_BOLD | COLOR_P(COLOR_WHITE, COLOR_BLACK);
}

int
Ship::getCh() const
{
	return '>';
}

Ship::~Ship()
{

}

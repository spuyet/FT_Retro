#include <ncurses.h>
#include "Ship.hpp"
#include "Core.hpp"

Ship::Ship()
: AEntity()
, _index(0)
{

}

Ship::Ship(int index, float x, float y)
: AEntity(x, y)
, _index(index)
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
	return _ships[_index].attr;
}

int
Ship::getCh() const
{
	return _ships[_index].ch;
}

int
Ship::getScore() const
{
	return _ships[_index].score;
}

void
Ship::ai(Game* game, Ship* player)
{
	_ships[_index].ai(game, player, this);
}

Ship::~Ship()
{

}

ShipData	Ship::_ships[2] = {
	ShipData('>', A_BOLD | COLOR_P(COLOR_WHITE, COLOR_BLACK), 1.0f, 0, 0),
	ShipData('<', A_BOLD | COLOR_P(COLOR_RED, COLOR_BLACK), 1.0f, 25, ai::dumbShip)
};
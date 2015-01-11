#include <ncurses.h>
#include <cstdlib>
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

int
Ship::pickShip()
{
	int r = std::rand() % ShipData::sumOfProba + 1;
	int k = 0;

	for (int i = 0; i < ShipData::count; i++)
	{
		k += _ships[i].proba;
		if (r <= k)
			return i;
	}
	return ShipData::count - 1;
}

ShipData	Ship::_ships[] = {
	ShipData('>', A_BOLD | COLOR_P(COLOR_WHITE, COLOR_BLACK), 0, 0, 0),
	ShipData('<', A_BOLD | COLOR_P(COLOR_RED, COLOR_BLACK), 25, 250, ai::dumbShip),
	ShipData('O', A_BOLD | COLOR_P(COLOR_BLACK, COLOR_BLACK), 1, 50, ai::asteroid),
	ShipData('{',          COLOR_P(COLOR_WHITE, COLOR_BLACK), 50, 30, ai::station),
	ShipData('%', A_BOLD | COLOR_P(COLOR_MAGENTA, COLOR_BLACK), 100, 20, ai::ghost),
	ShipData('@', A_BOLD | COLOR_P(COLOR_GREEN, COLOR_BLACK), 40, 50, ai::poseidon),
	ShipData('&', A_BOLD | COLOR_P(COLOR_WHITE, COLOR_BLACK), 300, 3, ai::lord)
};
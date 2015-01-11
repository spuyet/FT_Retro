#ifndef SHIP_H
#define SHIP_H

#include "AEntity.hpp"
#include "ShipData.hpp"

class Ship : public AEntity
{
public:
	Ship();
	Ship(int index, float x, float y);
	Ship(const Ship& rhs);
	Ship&	operator=(const Ship& rhs);

	int		getAttr() const;
	int		getCh() const;
	int		getScore() const;
	void	ai(Game* game, Ship* player);

	~Ship();

private:

	int					_index;
	static ShipData		_ships[2];

};

#endif
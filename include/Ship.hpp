#ifndef SHIP_H
#define SHIP_H

#include "AEntity.hpp"

class Ship : public AEntity
{
public:
	Ship();
	Ship(float x, float y);
	Ship(const Ship& rhs);
	Ship&	operator=(const Ship& rhs);

	int		getAttr() const;
	int		getCh() const;

	~Ship();

private:

};

#endif
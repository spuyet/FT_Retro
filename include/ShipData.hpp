#ifndef SHIP_DATA_H
#define SHIP_DATA_H

#include "AI.hpp"

struct ShipData
{
	ShipData();
	ShipData(int ch, int attr, float speed, ai::func ai);
	ShipData(const ShipData&);

	ShipData& operator=(const ShipData&);

	~ShipData();

	int			ch;
	int			attr;
	float		speed;
	ai::func	ai;
};

#endif
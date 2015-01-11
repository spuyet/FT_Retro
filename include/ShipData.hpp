#ifndef SHIP_DATA_H
#define SHIP_DATA_H

struct ShipData
{
	ShipData();
	ShipData(int ch, int attr, float speed);
	ShipData(const ShipData&);

	ShipData& operator=(const ShipData&);

	~ShipData();

	int		ch;
	int		attr;
	float	speed;
};

#endif
#include "ShipData.hpp"

ShipData::ShipData()
{

}

ShipData::ShipData(int ch, int attr, float speed)
: ch(ch)
, attr(attr)
, speed(speed) 
{

}

ShipData::ShipData(const ShipData& s)
: ch(s.ch)
, attr(s.attr)
, speed(s.speed)
{

}

ShipData&
ShipData::operator=(const ShipData& s)
{
	ch = s.ch;
	attr = s.attr;
	speed = s.speed;
	return *this;
}

ShipData::~ShipData()
{

}
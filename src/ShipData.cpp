#include "ShipData.hpp"

ShipData::ShipData()
{

}

ShipData::ShipData(int ch, int attr, float speed, ai::func ai)
: ch(ch)
, attr(attr)
, speed(speed)
, ai(ai)
{

}

ShipData::ShipData(const ShipData& s)
: ch(s.ch)
, attr(s.attr)
, speed(s.speed)
, ai(s.ai)
{

}

ShipData&
ShipData::operator=(const ShipData& s)
{
	ch = s.ch;
	attr = s.attr;
	speed = s.speed;
	ai = s.ai;
	return *this;
}

ShipData::~ShipData()
{

}
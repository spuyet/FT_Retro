#include "ShipData.hpp"

ShipData::ShipData()
{

}

ShipData::ShipData(int ch, int attr, int score, ai::func ai)
: ch(ch)
, attr(attr)
, score(score)
, ai(ai)
{

}

ShipData::ShipData(const ShipData& s)
: ch(s.ch)
, attr(s.attr)
, score(s.score)
, ai(s.ai)
{

}

ShipData&
ShipData::operator=(const ShipData& s)
{
	ch = s.ch;
	attr = s.attr;
	score = s.score;
	ai = s.ai;
	return *this;
}

ShipData::~ShipData()
{

}
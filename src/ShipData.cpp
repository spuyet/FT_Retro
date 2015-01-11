#include "ShipData.hpp"

ShipData::ShipData()
{

}

ShipData::ShipData(int ch, int attr, int score, int proba, ai::func ai)
: ch(ch)
, attr(attr)
, score(score)
, proba(proba)
, ai(ai)
{
	sumOfProba += proba;
	count++;
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

int	ShipData::sumOfProba = 0;
int ShipData::count = 0;
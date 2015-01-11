#include "BulletData.hpp"

BulletData::BulletData()
: ch(0)
, attr(0)
{

}

BulletData::BulletData(int ch, int attr)
: ch(ch)
, attr(attr)
{

}

BulletData::BulletData(const BulletData& rhs)
: ch(rhs.ch)
, attr(rhs.attr)
{

}

BulletData&
BulletData::operator=(const BulletData& rhs)
{
	ch = rhs.ch;
	attr = rhs.attr;
	return *this;
}

BulletData::~BulletData()
{

}

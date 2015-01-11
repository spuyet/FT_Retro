#include "Bullet.hpp"
#include "Core.hpp"

Bullet::Bullet()
: AEntity()
, _index(0)
{

}

Bullet::Bullet(int index, float x, float y)
: AEntity(x, y)
, _index(index)
{


}

Bullet::Bullet(const Bullet& rhs)
: AEntity(rhs)
, _index(rhs._index)
{

}

Bullet&
Bullet::operator=(const Bullet& rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_speedX = rhs._speedX;
	_speedY = rhs._speedY;
	_index = rhs._index;
	return *this;
}

int
Bullet::getAttr() const
{
	return _bullets[_index].attr;
}

int
Bullet::getCh() const
{
	return _bullets[_index].ch;
}

void
Bullet::ai(Game* game, Ship* player)
{
	(void)game;
	(void)player;
}

Bullet::~Bullet()
{

}

BulletData Bullet::_bullets[] = {
	BulletData('-', A_BOLD | COLOR_P(COLOR_GREEN, 0)),
	BulletData('-', COLOR_P(COLOR_WHITE, 0)),
	BulletData('.', A_BOLD | COLOR_P(COLOR_CYAN, 0)),
	BulletData('\\', COLOR_P(COLOR_WHITE, 0)),
	BulletData('/', COLOR_P(COLOR_WHITE, 0)),
	BulletData('(', A_BOLD | COLOR_P(COLOR_BLUE, 0)),
	BulletData(')', A_BOLD | COLOR_P(COLOR_BLUE, 0)),
};
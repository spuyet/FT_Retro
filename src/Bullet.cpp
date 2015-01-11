#include "Bullet.hpp"
#include "Core.hpp"

Bullet::Bullet()
: AEntity()
{

}

Bullet::Bullet(float x, float y)
: AEntity(x, y)
{


}

Bullet::Bullet(const Bullet& rhs)
: AEntity(rhs)
{

}

Bullet&
Bullet::operator=(const Bullet& rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	_speedX = rhs._speedX;
	_speedY = rhs._speedY;
	return *this;
}

int
Bullet::getAttr() const
{
	return A_BOLD | COLOR_P(COLOR_GREEN, COLOR_BLACK);
}

int
Bullet::getCh() const
{
	return '-';
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

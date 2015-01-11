#ifndef BULLET_H
#define BULLET_H

#include "AEntity.hpp"

class Bullet : public AEntity
{

public:

	Bullet();
	Bullet(float x, float y);
	Bullet(const Bullet& rhs);
	Bullet& operator=(const Bullet& rhs);

	int		getAttr() const;
	int		getCh() const;
	void	ai(Game* game, Ship* player);

	~Bullet();


};

#endif
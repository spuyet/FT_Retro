#ifndef BULLET_DATA_H
#define BULLET_DATA_H

struct BulletData
{
	BulletData();
	BulletData(int ch, int attr);
	BulletData(const BulletData& rhs);
	BulletData&		operator=(const BulletData& rhs);
	~BulletData();

	int		ch;
	int		attr;
};

#endif
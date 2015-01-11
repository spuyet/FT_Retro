#ifndef AENTITY_H
#define AENTITY_H

class AEntity
{

public:

	AEntity();
	AEntity(float x, float y);
	AEntity(const AEntity& rhs);
	AEntity& operator=(const AEntity& rhs);

	int				getX() const;
	int				getY() const;
	float			getSpeedX() const;
	float			getSpeedY() const;
	int				getTeam() const;
	void			setPos(float x, float y);
	void			setSpeed(float x, float y);
	void			setTeam(int team);
	virtual int		getAttr() const = 0;
	virtual int		getCh() const = 0;
	virtual void	update();
	virtual void	render(int x, int y) const;

	virtual ~AEntity();

protected:

	float	_x;
	float	_y;
	float	_speedX;
	float	_speedY;
	int		_team;
};

#endif
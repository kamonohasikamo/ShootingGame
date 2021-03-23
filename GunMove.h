#include "Pos.h"

class GunMove
{
private:
	Pos gunPos;
	bool isShot;
public:
	void move()
	{
		if (isShot)
		{
			gunPos.y -= 3;
		}

		if (gunPos.y < 0)
		{
			setIsShot(false);
		}
	}

	void setGunPos(Pos pos)
	{
		gunPos = pos;
	}

	void setIsShot(bool flag)
	{
		isShot = flag;
	}

	bool getIsShot()
	{
		return isShot;
	}

	Pos getGunPos()
	{
		return gunPos;
	}
};
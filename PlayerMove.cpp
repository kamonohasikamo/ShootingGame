#include "DxLib.h"
#include <string>
#include "Pos.h"
#include "Define.h"

using namespace std;

class PlayerMove
{
private:
	Pos playerPos;
	Define DEFINE;
public:
	Pos getPlayerPos()
	{
		return playerPos;
	}

	void setPlayerPos(Pos pos)
	{
		playerPos = pos;
	}

	void setPlayerPoxX(double x)
	{
		playerPos.x = x;
	}

	void setPlayerPosY(double y)
	{
		playerPos.y = y;
	}

	void moveLeftX()
	{
		if (playerPos.x > 3)
		{
			playerPos.x -= 3;
		}
	}

	void moveRightX()
	{
		if (playerPos.x + DEFINE.PLAYER_WIDTH < DEFINE.WIDTH)
		{
			playerPos.x += 3;
		}
	}
};
#include "DxLib.h"
#include <string>
#include "Pos.cpp"

using namespace std;

class PlayerMove
{
private:
	Pos* playerPos;
public:
	PlayerMove()
	{
		playerPos = new Pos(0, 0);
	}

	Pos getPlayerPos()
	{
		return *playerPos;
	}


};
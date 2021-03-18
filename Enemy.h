#include "Pos.h"
#include <iostream>
#include "DxLib.h"
#include <string>
#pragma once

using namespace std;

class Enemy
{
protected:
	Pos enemyPos;
	int enterTime;
	int stopTime;
	int backTime;
	bool isShow;
public:
	virtual void move(int frame)
	{
		if (enterTime <= frame && frame < stopTime)
		{
			isShow = true;
			enemyPos.y += 3;
		}
		else if (backTime <= frame)
		{
			if (enemyPos.y < -100)
			{
				isShow = false;
				return;
			}
			enemyPos.y -= 3;
		}
	};

	void setIsShow(bool flag)
	{
		isShow = flag;
	}

	bool getIsShow()
	{
		return isShow;
	}

	virtual void createEnemy(int enter, int stop, int back)
	{
		enterTime = enter;
		stopTime = stop;
		backTime = back;
	};

	void setEnemyPos(Pos pos)
	{
		enemyPos = pos;
	}

	Pos getEnemyPos()
	{
		return enemyPos;
	}
};
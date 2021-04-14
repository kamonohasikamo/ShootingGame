#include "Pos.h"
#include <iostream>
#include "DxLib.h"
#include <string>
#pragma once

using namespace std;

enum class ENEMYTYPE
{
	nomal,
	strong,
};

enum class MOVETYPE
{
	nomal,
};

enum class SHOTPATTERN
{
	nomal,
};

struct EnemyGun
{
	bool isShot;
	Pos gunPos;
	SHOTPATTERN pattern;
	double speed;
};

class Enemy
{
protected:
	Pos enemyPos;
	ENEMYTYPE type;

	int enterTime;
	int stopTime;
	int shotTime;
	int backTime;
	bool isShow;
	bool isDead;
public:
	EnemyGun gunData[30];
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

	virtual void createEnemy(int enter, int stop, int back, int shot, ENEMYTYPE initType)
	{
		type = initType;
		enterTime = enter;
		stopTime = stop;
		backTime = back;
		shotTime = shot;
	};

	void setShotData(SHOTPATTERN shotPattern, double shotSpeed)
	{
		for (int i = 0; i < 30; i++)
		{
			gunData[i].isShot = false;
			gunData[i].gunPos = enemyPos;
			gunData[i].pattern = shotPattern;
			gunData[i].speed = shotSpeed;
		}
	}

	void shotGun(int frame)
	{
		if (frame > shotTime)
		{
			if (frame % 10 == 0)
			{
				for (int i = 0; i < 30; i++)
				{
					if (!gunData[i].isShot)
					{
						gunData[i].isShot = true;
						gunData[i].gunPos = enemyPos;
					}
				}
			}
		}

		//int shotGunNum = 0;

		for (int i = 0; i < 30; i++)
		{
			if (gunData[i].isShot)
			{
				gunData[i].gunPos.y += gunData[i].speed;
				if (gunData[i].gunPos.x < -30
					|| gunData[i].gunPos.x > 500
					|| gunData[i].gunPos.y < -30
					|| gunData[i].gunPos.y > 700)
				{
					gunData[i].isShot = false;
					continue;
				}
				//shotGunNum++;
			}
		}

//		if (shotGunNum == 0 && isDead)
//		{

//		}
	}

	void setIsDead()
	{
		isDead = true;
	}

	bool getIsDead()
	{
		return isDead;
	}

	void setEnemyPos(Pos pos)
	{
		enemyPos = pos;
	}

	Pos getEnemyPos()
	{
		return enemyPos;
	}
};
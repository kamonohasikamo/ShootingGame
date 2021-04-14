#include "DxLib.h"
#include "PlayerMove.cpp"
#include "GunMove.h"
#include "Collision.h"
#include "Enemy.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <vector>

using namespace std;

PlayerMove playerMove;
vector<Enemy> enemy(5);
Define DEFINE;
vector<GunMove> gun(DEFINE.MAX_GUN_NUM);
Collision col; // 当たり判定クラスのインスタンス

int gunImage = -1;
int playerImage = -1;
int nomalEnemyImage = -1;
int strongEnemyImage = -1;
int enemyGunImage = -1;

bool isGameOver = false;

// init function
void Init()
{
	Pos playerInitPos;
	playerInitPos.x = (DEFINE.WIDTH / 2);
	playerInitPos.y = (DEFINE.HEIGHT - 50);
	playerMove.setPlayerPos(playerInitPos);
	gunImage = LoadGraph("image/gun.png");
	playerImage = LoadGraph("image/player.png");
	nomalEnemyImage = LoadGraph("image/NomalEnemy.png");
	strongEnemyImage = LoadGraph("image/StrongEnemy.png");
	enemyGunImage = LoadGraph("image/EnemyGun.png");
	for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
	{
		gun[i].setIsShot(false);
	}

	ifstream ifs("EnemyData/EnemyData.txt");
	string str;
	if (ifs.fail())
	{
		for (int i = 0; i < 5; i++)
		{
			enemy[i].createEnemy(60 * (i + 1), 80 * (i + 1), 300 * (i + 1), 90 * (i + 1), ENEMYTYPE::nomal);
			Pos nEnemyInitPos;
			nEnemyInitPos.x = 50 * (i + 1);
			nEnemyInitPos.y = -40;
			enemy[i].setEnemyPos(nEnemyInitPos);
			enemy[i].setShotData(SHOTPATTERN::nomal, 5.0);
		}
	}
	else
	{
		int index = -2;
		while (getline(ifs, str))
		{
			index++;
			if (index == -1) continue; // first line is comment
			if (index > 4) break; // enemy num over is break;
			auto list = vector<int>();
			stringstream ss{str};
			string buf;
			while(getline(ss, buf, ','))
			{
				list.push_back(stod(buf));
			}
			enemy[index].createEnemy(list[0], list[1], list[2], list[3], ENEMYTYPE::nomal);
			Pos nEnemyInitPos;
			nEnemyInitPos.x = 50 * (index + 1);
			nEnemyInitPos.y = -40;
			enemy[index].setEnemyPos(nEnemyInitPos);
			enemy[index].setShotData(SHOTPATTERN::nomal, 5.0);
		}
	}
}

// MainWindow 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// set Window size
	SetGraphMode(DEFINE.WIDTH, DEFINE.HEIGHT, 16);
	
	// no full screen
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)	// if DxLib_Init error return -1
	{
		return -1;	// error exit
	}

	// set back screen
	SetDrawScreen(DX_SCREEN_BACK);
	
	Init();
	int Key;
	int roopCount = 0;
	
	// GameMainRoop
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// set key data
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// if right key pressed
		if (Key & PAD_INPUT_RIGHT)
		{
			playerMove.moveRightX();
			// string tmp = to_string(playerMove.getPlayerPos().x) + "," + to_string(playerMove.getPlayerPos().y) + "\n";
			// OutputDebugString(tmp.c_str());
		}

		// if left key pressed
		if (Key & PAD_INPUT_LEFT)
		{
			playerMove.moveLeftX();
		}

		// if space key pressed
		if (Key & PAD_INPUT_10)
		{
			if (roopCount % 6 == 0)
			{
				for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
				{
					if (!gun[i].getIsShot())
					{
						gun[i].setIsShot(true);
						Pos gunInitPos = playerMove.getPlayerPos();
						gunInitPos.x += (DEFINE.PLAYER_WIDTH / 2);
						gun[i].setGunPos(gunInitPos);
						break;
					}
				}
			}
		}

		// clear screen
		ClearDrawScreen();

		// show Player
		for (int i = 0; i < 5; i++)
		{
			enemy[i].setPlayerPos(playerMove.getPlayerPos());
			if (enemy[i].getIsHit())
			{
				isGameOver = true;
				break;
			}
		}

		if (!isGameOver)
		{
			DrawGraph(playerMove.getPlayerPos().x, playerMove.getPlayerPos().y, playerImage, true);
			// move Player gun
			for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
			{
				if (gun[i].getIsShot())
				{
					for (int j = 0; j < 5; j++)
					{
						if (col.isCollision(gun[i].getGunPos(), enemy[j].getEnemyPos(), DEFINE.GUN_HEIGHT, DEFINE.ENEMY_HEIGHT))
						{
							enemy[j].setIsDead();
						}
					}
					gun[i].move();
					Pos gunPos = gun[i].getGunPos();
					DrawGraph(gunPos.x, gunPos.y, gunImage, true);
				}
			}
		}

		// show and move enemy and enemy gun
		for (int i = 0; i < 5; i++)
		{
			enemy[i].move(roopCount);
			enemy[i].shotGun(roopCount);
			if (!enemy[i].getIsDead() && enemy[i].getIsShow())
			{
				Pos enemyPos = enemy[i].getEnemyPos();
				DrawGraph(enemyPos.x, enemyPos.y, nomalEnemyImage, true);
			}
			for (int j = 0; j < 30; j++)
			{
				if (!enemy[i].getIsDead() && enemy[i].gunData[j].isShot)
				{
					DrawGraph(enemy[i].gunData[j].gunPos.x, enemy[i].gunData[j].gunPos.y, enemyGunImage, true);
				}
			}
		}

		ScreenFlip();

		roopCount++;
	}

	DxLib_End();
	return 0; // exit
}
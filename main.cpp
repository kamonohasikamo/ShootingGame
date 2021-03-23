#include "DxLib.h"
#include "PlayerMove.cpp"
#include "GunMove.h"
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

int gunImage = -1;
int playerImage = -1;
int nomalEnemyImage = -1;
int strongEnemyImage = -1;
int enemyGunImage = -1;

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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(DEFINE.WIDTH, DEFINE.HEIGHT, 16);
	
	// window���[�h�Ftrue
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	
	Init();
	int Key;
	int roopCount = 0;
	
	// GameMainRoop
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �L�[���͎擾
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// �E�������Ă�����E�ɐi��
		if (Key & PAD_INPUT_RIGHT)
		{
			playerMove.moveRightX();
			// string tmp = to_string(playerMove.getPlayerPos().x) + "," + to_string(playerMove.getPlayerPos().y) + "\n";
			// OutputDebugString(tmp.c_str());
		}

		// ���������Ă����獶�ɐi��
		if (Key & PAD_INPUT_LEFT)
		{
			playerMove.moveLeftX();
		}

		// SPACE�L�[����������e����
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

		// ��ʂ�����������
		ClearDrawScreen();

		// show Player
		DrawGraph(playerMove.getPlayerPos().x, playerMove.getPlayerPos().y, playerImage, true);

		// �e�̈ړ��ƕ\��
		for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
		{
			if (gun[i].getIsShot())
			{
				gun[i].move();
				Pos gunPos = gun[i].getGunPos();
				DrawGraph(gunPos.x, gunPos.y, gunImage, true);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			enemy[i].move(roopCount);
			enemy[i].shotGun(roopCount);
			if (enemy[i].getIsShow())
			{
				Pos enemyPos = enemy[i].getEnemyPos();
				DrawGraph(enemyPos.x, enemyPos.y, nomalEnemyImage, true);
			}
			for (int j = 0; j < 30; j++)
			{
				if (enemy[i].gunData[j].isShot)
				{
					DrawGraph(enemy[i].gunData[j].gunPos.x, enemy[i].gunData[j].gunPos.y, enemyGunImage, true);
				}
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		roopCount++;
	}

	DxLib_End();
	return 0; // �\�t�g�̏I��
}
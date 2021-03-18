#include "DxLib.h"
#include "PlayerMove.cpp"
#include "GunMove.cpp"
#include "NomalEnemy.cpp"
#include "StrongEnemy.cpp"
#include <iostream>
#include <vector>

using namespace std;

PlayerMove playerMove;
vector<NomalEnemy> nEnemy(5);
vector<StrongEnemy> sEnemy(1);
Define DEFINE;
vector<GunMove> gun(DEFINE.MAX_GUN_NUM);

int gunImage = -1;
int playerImage = -1;
int nomalEnemyImage = -1;
int strongEnemyImage = -1;

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
	for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
	{
		gun[i].setIsShot(false);
	}

	for (int i = 0; i < 5; i++)
	{
		nEnemy[i].createEnemy(60 * (i + 1), 80 * (i + 1), 300 * (i + 1));
		Pos nEnemyInitPos;
		nEnemyInitPos.x = 50 * (i + 1);
		nEnemyInitPos.y = -40;
		nEnemy[i].setEnemyPos(nEnemyInitPos);
	}

	sEnemy[0].createEnemy(2000, 2600, 32000);
	Pos sEnemyInitPos;
	sEnemyInitPos.x = (DEFINE.WIDTH / 2);
	sEnemyInitPos.y = -40;
	sEnemy[0].setEnemyPos(sEnemyInitPos);
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
			nEnemy[i].move(roopCount);
			if (nEnemy[i].getIsShow())
			{
				Pos enemyPos = nEnemy[i].getEnemyPos();
				DrawGraph(enemyPos.x, enemyPos.y, nomalEnemyImage, true);
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		roopCount++;
	}

	DxLib_End();
	return 0; // �\�t�g�̏I��
}
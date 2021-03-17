#include "DxLib.h"
#include "PlayerMove.cpp"
#include "GunMove.cpp"
#include <iostream>
#include <vector>

using namespace std;

PlayerMove playerMove;
Define DEFINE;
vector<GunMove> gun(DEFINE.MAX_GUN_NUM);

int gunImage = -1;
int playerImage = -1;

void Init()
{
	Pos playerInitPos;
	playerInitPos.x = (DEFINE.WIDTH / 2);
	playerInitPos.y = (DEFINE.HEIGHT - 50);
	playerMove.setPlayerPos(playerInitPos);
	gunImage = LoadGraph("image/gun.png");
	playerImage = LoadGraph("image/player.png");
	for (int i = 0; i < DEFINE.MAX_GUN_NUM; i++)
	{
		gun[i].setIsShot(false);
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
						gun[i].setGunPos(playerMove.getPlayerPos());
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
				DrawGraph(gun[i].getGunPos().x, gun[i].getGunPos().y, gunImage, true);
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		roopCount = (roopCount > 600) ? 0 : roopCount + 1;
	}

	DxLib_End();
	return 0; // �\�t�g�̏I��
}
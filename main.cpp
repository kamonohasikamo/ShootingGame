#include "DxLib.h"
#include "PlayerMove.cpp"
#include <iostream>

using namespace std;

PlayerMove playerMove;
Define DEFINE;

void Init()
{
	Pos playerInitPos;
	playerInitPos.x = (DEFINE.WIDTH / 2);
	playerInitPos.y = (DEFINE.HEIGHT - 50);
	playerMove.setPlayerPos(playerInitPos);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードのセット
	SetGraphMode(DEFINE.WIDTH, DEFINE.HEIGHT, 16);
	
	// windowモード：true
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	
	Init();
	int playerImage = LoadGraph("image/player.png");
	int Key;
	
	// GameMainRoop
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// キー入力取得
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// 右を押していたら右に進む
		if (Key & PAD_INPUT_RIGHT)
		{
			playerMove.moveRightX();
			// string tmp = to_string(playerMove.getPlayerPos().x) + "," + to_string(playerMove.getPlayerPos().y) + "\n";
			// OutputDebugString(tmp.c_str());
		}

		// 左を押していたら左に進む
		if (Key & PAD_INPUT_LEFT)
		{
			playerMove.moveLeftX();
		}

		// 画面を初期化する
		ClearDrawScreen();

		// show Player
		DrawGraph(playerMove.getPlayerPos().x, playerMove.getPlayerPos().y, playerImage, true);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();
	return 0; // ソフトの終了
}
#include "GameOverScene.h"
#include <DxLib.h>
#include "Screen.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void GameOverScene::Draw()
{
	const char* titleText = "配信が終了しました";

	// フォントサイズを大きく設定
	SetFontSize(64);

	// テキストの幅を取得
	int textW = GetDrawStringWidth(titleText, strlen(titleText));

	// 画面中央に配置
	int x = (Screen::WIDTH - textW) / 2;
	int y = Screen::HEIGHT / 3;
	// 描画
	DrawString(x, y, titleText, GetColor(255, 255, 255));

	// フォントサイズを元に戻す
	SetFontSize(16);

	DrawString(0, 0, "GAMEOVER SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}

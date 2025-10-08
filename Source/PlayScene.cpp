#include "PlayScene.h"
#include <DxLib.h>
#include "Screen.h"
#include "Stage.h"

PlayScene::PlayScene()
{
	new Stage();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_G)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
	if (CheckHitKey(KEY_INPUT_C)) {
		SceneManager::ChangeScene("CLEAR");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [G]Key To Title", GetColor(255, 255, 255));
	DrawString(100, 500, "Push [C]Key To Title", GetColor(255, 255, 255));
	

	// ‘¾‚³1‚Ì˜g
	//DrawBox(Screen::startX, Screen::startY, Screen::endX, Screen::endY, GetColor(255, 0, 0), FALSE);

}

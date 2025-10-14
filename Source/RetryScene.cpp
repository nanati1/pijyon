#include "RetryScene.h"
#include "background.h"

RetryScene::RetryScene()
{
	new BackGround();
}

RetryScene::~RetryScene()
{
}

void RetryScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_G)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void RetryScene::Draw()
{
	DrawString(0, 0, "RETRY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(100, 500, "Push [G]Key To GameOver", GetColor(255, 255, 255));
}

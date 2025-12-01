#include "RetryScene.h"
#include "background.h"
#include"CommentArea.h"
#include "Screen.h"

RetryScene::RetryScene()
{
	//new BackGround();
	new CommentArea();
	bg = FindGameObject<BackGround>();
	Screen::startTime = GetNowCount();  // シーン開始時に時刻を記録
}

RetryScene::~RetryScene()
{
}

void RetryScene::Update()
{
	
	int now = GetNowCount();

	// 3秒経過したらシーン変更
	if (now - Screen::startTime >= 3000) {   // ← 3000ミリ秒
		SceneManager::ChangeScene("PLAY");
	}


	//if (CheckHitKey(KEY_INPUT_P)) {
	//	SceneManager::ChangeScene("PLAY");
	//}
	//if (CheckHitKey(KEY_INPUT_G)) {
	//	SceneManager::ChangeScene("GAMEOVER");
	//}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void RetryScene::Draw()
{
	/*DrawString(0, 0, "RETRY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(100, 500, "Push [G]Key To GameOver", GetColor(255, 255, 255));*/
}

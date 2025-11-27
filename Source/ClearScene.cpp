#include "ClearScene.h"
#include <DxLib.h>
#include "Screen.h"

ClearScene::ClearScene()
{
	Screen::startTime = GetNowCount();  // シーン開始時に時刻を記録
}

ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
	int now = GetNowCount();

	// 3秒経過したらシーン変更
	if (now - Screen::startTime >= 3000) {   // ← 3000ミリ秒
		SceneManager::ChangeScene("TITLE");
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void ClearScene::Draw()
{
	DrawString(0, 0, "CLEAR SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}

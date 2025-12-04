#include "ClearScene.h"
#include"CommentArea.h"
#include <DxLib.h>
#include "Screen.h"
#include "../Library/Input.h"
#include "Time.h"

ClearScene::ClearScene()
{
	Input::Initialize();
	Time::startTime = GetNowCount();  // シーン開始時に時刻を記録
}

ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
	Input::Update();
	int now = GetNowCount();

	// 3秒経過したらシーン変更
	if (now - Time::startTime >= 20000) {   // ← 3000ミリ秒
		SceneManager::ChangeScene("TITLE");
	}

	if (Input::IsKeyDown(KEY_INPUT_SPACE)) {   // ← 3000ミリ秒
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

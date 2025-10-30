#include "TitleScene.h"
#include <DxLib.h>
#include"Time.h"

TitleScene::TitleScene()
{
	static bool sTimeInited = false;
	if (!sTimeInited) {
		Time::Init();
		sTimeInited = true;
	}
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	Time::Refresh();
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}

#include "TitleScene.h"
#include <DxLib.h>
#include"Time.h"
#include <assert.h>
#include "Screen.h"

TitleScene::TitleScene()
{
	static bool sTimeInited = false;
	if (!sTimeInited) {
		Time::Init();
		sTimeInited = true;
	}

	hImage = LoadGraph("data/image/Title.png");
	assert(hImage > 0);

}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	Time::Refresh();
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawExtendGraph(Screen::startX, Screen::startY, Screen::WIDTH, Screen::HEIGHT, hImage, 0);
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [SPACE]Key To Play", GetColor(255, 255, 255));
}

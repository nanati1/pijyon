#include "LoadScene.h"
#include <assert.h>

LoadScene::LoadScene()
{
	hImage = LoadGraph("data/image/load.png");
	assert(hImage > 0);
	Time::startTime = GetNowCount();  // シーン開始時に時刻を記録
}

LoadScene::~LoadScene()
{
}

void LoadScene::Update()
{
	int now = GetNowCount();

	// 3秒経過したらシーン変更
	if (now - Time::startTime >= 5000) {   // ← 3000ミリ秒
		SceneManager::ChangeScene("PLAY");
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void LoadScene::Draw()
{
	DrawExtendGraph(0, 0, 1920, 1080, hImage, 0);
}

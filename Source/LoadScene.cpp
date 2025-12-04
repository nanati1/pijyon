#include "LoadScene.h"
#include <assert.h>

LoadScene::LoadScene()
{
	hImage = LoadGraph("data/image/kibodo.png");
	assert(hImage > 0);
}

LoadScene::~LoadScene()
{
}

void LoadScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void LoadScene::Draw()
{
	DrawExtendGraph(320, 180, 1600, 640, hImage, 0);
}

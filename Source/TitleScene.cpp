#include "TitleScene.h"
#include <DxLib.h>
#include"Time.h"
#include <assert.h>
#include "Screen.h"
#include "../Library/Input.h"

TitleScene::TitleScene()
{
	Input::Initialize();
	ObjectManager::DeleteForceAllGameObject();
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
	Input::Update();
	Time::Refresh();
	if (Input::IsKeyDown(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("LOAD");
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawExtendGraph(Screen::startX, Screen::startY, Screen::WIDTH, Screen::HEIGHT, hImage, 0);

	static int counter = 0;
	counter++;

	// 点滅速度（小さいほど速い）
	const int blinkSpeed = 100;

	// 一定時間ごとに点滅（半分表示・半分非表示）
	bool visible = (counter / blinkSpeed) % 2 == 0;

	const char* titleText = "SPACE";

	// フォントサイズ変更
	SetFontSize(200);

	// テキスト幅
	int textW = GetDrawStringWidth(titleText, strlen(titleText));

	// 位置
	int x = (Screen::WIDTH - textW) / 2;
	int y = Screen::HEIGHT - 400;

	// 点滅中なら描画する
	if (visible) {
		DrawString(x, y, titleText, GetColor(255, 0, 0));
	}

	// フォントサイズ戻す
	SetFontSize(16);

	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	//DrawString(100, 400, "Push [SPACE]Key To Play", GetColor(255, 255, 255));
}

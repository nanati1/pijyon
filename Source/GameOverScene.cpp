#include "GameOverScene.h"
#include <DxLib.h>
#include "Screen.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void GameOverScene::Draw()
{
	const char* titleText = "�z�M���I�����܂���";

	// �t�H���g�T�C�Y��傫���ݒ�
	SetFontSize(64);

	// �e�L�X�g�̕����擾
	int textW = GetDrawStringWidth(titleText, strlen(titleText));

	// ��ʒ����ɔz�u
	int x = (Screen::WIDTH - textW) / 2;
	int y = Screen::HEIGHT / 3;
	// �`��
	DrawString(x, y, titleText, GetColor(255, 255, 255));

	// �t�H���g�T�C�Y�����ɖ߂�
	SetFontSize(16);

	DrawString(0, 0, "GAMEOVER SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}

#include "background.h"
#include <DxLib.h>
#include <assert.h>

BackGround::BackGround()
{
	hImage = LoadGraph("data/image/white.jpg");
	assert(hImage > 0);
	wImage = LoadGraph("data/image/red.jpg");
}

BackGround::BackGround(VECTOR2 pos)
{
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	//DrawExtendGraph(0, 0, 160, 1080, hImage, 0);// ���[
	DrawExtendGraph(1360, 72, 1920, 765, hImage, 0);//�E�[
	DrawExtendGraph(0, 0, 1920, 72, wImage, 0);//��
	//DrawExtendGraph(0, 832, 1920, 1080, hImage, 0);//��
}

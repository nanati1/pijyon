#include "background.h"
#include <DxLib.h>
#include <assert.h>

BackGround::BackGround()
{
	hImage = LoadGraph("data/image/white.jpg");
	assert(hImage > 0);
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
	DrawExtendGraph(0, 0, 160, 1080, hImage, 0);// ç∂í[
	DrawExtendGraph(1760, 0, 1920, 1080, hImage, 0);//âEí[
	DrawExtendGraph(0, 0, 1920, 108, hImage, 0);//è„
	DrawExtendGraph(0, 822, 1920, 1080, hImage, 0);//â∫
}

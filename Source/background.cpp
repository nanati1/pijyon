#include "background.h"
#include <DxLib.h>
#include <assert.h>

BackGround::BackGround()
{
	wImage = LoadGraph("data/image/white.jpg");
	assert(wImage > 0);
	rImage = LoadGraph("data/image/red.jpg");
	assert(rImage > 0);
	hImage = LoadGraph("data/image/skin color.jpg");
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
	//DrawExtendGraph(0, 0, 160, 1080, hImage, 0);// ç∂í[
	DrawExtendGraph(1360, 72, 1920, 765, hImage, 0);//âEí[
	DrawExtendGraph(0, 0, 1920, 72, rImage, 0);//è„
	DrawExtendGraph(0, 765, 1920, 1080, wImage, 0);//â∫
}

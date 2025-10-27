#include "background.h"
#include <DxLib.h>
#include <assert.h>
#include "Avatar.h"
#include "CommentArea.h"
#include "KeyInput.h"

BackGround::BackGround()
{
	wImage = LoadGraph("data/image/white.jpg");
	assert(wImage > 0);
	rImage = LoadGraph("data/image/Rogo1.png");
	assert(rImage > 0);
	tImage = LoadGraph("data/image/Tab.png");
	assert(tImage > 0);
	hImage = LoadGraph("data/image/chat.png");
	assert(hImage > 0);
	iImage = LoadGraph("data/image/Icon2.png");
	assert(iImage > 0);
	sImage = LoadGraph("data/image/search.png");
	assert(sImage > 0);
	bImage = LoadGraph("data/image/bell.png");
	new Avatar();
	new CommentArea();
	new KeyInput();
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
	//DrawExtendGraph(1360, 72, 1920, 765, wImage, 0);//右端
	DrawExtendGraph(1360, 72, 1920, 765, wImage, 0);//右端 白
	DrawExtendGraph(1360, 72, 1920, 765, hImage, 1);//右端　枠
	DrawExtendGraph(0, 0, 1920, 72, wImage, 0);//上
	DrawExtendGraph(400, 0, 1400, 72, sImage, 0);//上 検索
	DrawExtendGraph(100, 0, 280, 72, rImage, 1);//ロゴ
	DrawExtendGraph(0, 0, 72, 72, tImage, 1);//タブ
	DrawExtendGraph(1720, 0, 1820, 72, iImage, 1);//アイコン
	DrawExtendGraph(1620, 0, 1720, 72, bImage, 1);//ベル
	DrawExtendGraph(0, 765, 1920, 1080, wImage, 0);//下
}

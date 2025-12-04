#include "background.h"
#include <DxLib.h>
#include <assert.h>
#include "Avatar.h"
#include "CommentArea.h"
#include "KeyInput.h"
#include "Screen.h"

BackGround::BackGround()
{
	wImage = LoadGraph("data/image/white.jpg");
	assert(wImage > 0);
	rImage = LoadGraph("data/image/Rogo.png");
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
	//new KeyInput();
	GameObject::StayOnSceneChange();
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
	DrawExtendGraph(1360, Screen::toolbar, Screen::WIDTH, Screen::HEIGHTSMALL, wImage, 0);//右端 白
	//DrawExtendGraph(1360, 72, 1920, 765, hImage, 1);//右端　枠
	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::toolbar, wImage, 0);//上
	DrawExtendGraph(400, 0, 1400, Screen::toolbar, sImage, 0);//上 検索
	DrawExtendGraph(100, 0, 280, Screen::toolbar, rImage, 1);//ロゴ
	DrawExtendGraph(0, 0, Screen::toolbar, Screen::toolbar, tImage, 1);//タブ
	DrawExtendGraph(1720, 0, 1820, Screen::toolbar, iImage, 1);//アイコン
	DrawExtendGraph(1620, 0, 1720, Screen::toolbar, bImage, 1);//ベル
	DrawExtendGraph(0, Screen::HEIGHTSMALL, Screen::WIDTH, Screen::HEIGHT, wImage, 0);//下
}

#include "Avatar.h"
#include <assert.h>


Avatar::Avatar()
	:animX(3), hImage(-1)
{
	hImage = LoadGraph("data/image/AvaterChip.png");
	assert(hImage > 0);
}

Avatar::Avatar(VECTOR2 pos)
{
}

Avatar::~Avatar()
{
}

void Avatar::Update(int stress)
{
	animX = stress;//ストレス値を入れる

}

void Avatar::Draw()
{
	//DrawExtendGraph(1100, 500, 1360, 765, hImage, 1);
	DrawRectExtendGraph(1040, 500, 1380, 765, 200*(animX), 0, 200, 150, hImage, 1);
}

#include "Avatar.h"
#include <assert.h>


Avatar::Avatar()
{
	hImage = LoadGraph("data/image/default.png");
	assert(hImage > 0);
}

Avatar::Avatar(VECTOR2 pos)
{
}

Avatar::~Avatar()
{
}

void Avatar::Update()
{
}

void Avatar::Draw()
{
	DrawExtendGraph(1100, 500, 1360, 765, hImage, 1);
}

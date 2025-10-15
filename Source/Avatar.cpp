#include "Avatar.h"
#include <assert.h>



Avatar::Avatar()
	:animX(0), hImage(-1),stress(0){
	hImage = LoadGraph("data/image/AvaterChip.png");
	assert(hImage > 0);
}

Avatar::Avatar(VECTOR2 pos)
	:animX(3), hImage(-1)
{
}

Avatar::~Avatar()
{

}

void Avatar::Update()
{
	animX = (stress/10);
	ImGui::Begin("Stress");
	ImGui::InputInt("stress", &stress);
	ImGui::End();
}


void Avatar::Draw()
{
	//DrawExtendGraph(1100, 500, 1360, 765, hImage, 1);
	DrawRectExtendGraph(1040, 500, 1380, 765, 200*(animX), 0, 200, 150, hImage, 1);
}


void Avatar::StressSet(int s)
{
	if (stress < 40)
	{
		stress += s;
	}
	
}
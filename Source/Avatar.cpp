#include "Avatar.h"
#include <assert.h>

Avatar::Avatar()
	:animX(0), hImage(-1),stress(0){
	hImage = LoadGraph("data/image/AvaterChip.png");
	assert(hImage > 0);

	std::string voicePath[4] = {
		"data/voice/AngryLevel1.mp4",//‚à[
		"data/voice/AngryLevel2.mp4",//‚Î‚©
		"data/voice/AngryLevel3.mp4",//‚¨‚±‚Á‚½
		"data/voice/AngryLevel4.mp4"//‚µ‚ç‚È‚¢I
	};
}

Avatar::~Avatar()
{

}

void Avatar::Update()
{
	animX = (Screen::stress/10);
	ImGui::Begin("Screen::stress");
	ImGui::InputInt("Screen::stress", &Screen::stress);
	ImGui::End();
	if (Screen::stress > 40)
	{
		Screen::stress = 0;
		SceneManager::ChangeScene("GAMEOVER");
	}
}


void Avatar::Draw()
{
	//DrawExtendGraph(1100, 500, 1360, 765, hImage, 1);
	DrawRectExtendGraph(1040, 500, 1380, 765, 200*(animX), 0, 200, 150, hImage, 1);
}


void Avatar::StressSet(int s)
{
	if (Screen::stress < 40)
	{
		Screen::stress += s;
	}
	
}
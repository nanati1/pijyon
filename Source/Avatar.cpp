#include "Avatar.h"
#include <assert.h>
#include "Screen.h"

namespace {
	std::string voicePath[4] = {
		"data/voice/AngryLevel1.mp3",//‚à[
		"data/voice/AngryLevel2.mp3",//‚Î‚©
		"data/voice/AngryLevel3.mp3",//‚¨‚±‚Á‚½
		"data/voice/AngryLevel4.mp3"//‚µ‚ç‚È‚¢I
	};
}

int Avatar::stress = 0;
int Avatar::prevAnim = 0;

Avatar::Avatar()
	:hImage(-1), animX(0) {
	hImage = LoadGraph("data/image/AvaterChip.png");
	assert(hImage > 0);
	animX = (stress / 10);
}

Avatar::~Avatar()
{
	DeleteGraph(hImage);
}

void Avatar::Update()
{
	animX = (stress / 10);

	if (prevAnim != animX)
	{
		PlaySoundFile(voicePath[animX - 1].c_str(), DX_PLAYTYPE_BACK);
		prevAnim = animX;
	}
	if (stress >= maxStress)
	{
		stress = 0;
		prevAnim = animX;
		SceneManager::ChangeScene("GAMEOVER");

	}


	ImGui::Begin("Screen::stress");
	ImGui::InputInt("Screen::stress", &stress);
	ImGui::End();

}

void Avatar::Draw()
{
	DrawRectExtendGraph(1040, 600, 1380, Screen::HEIGHTSMALL, 200 * (animX), 0, 200, 150, hImage, 1);
}


void Avatar::StressSet(int s)
{
	stress += s;

}

void Avatar::StressReset()
{
	stress = 0;

}
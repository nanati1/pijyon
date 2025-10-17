#include "Avatar.h"
#include <assert.h>

Avatar::Avatar()
	:animX(0), hImage(-1), prevAnim(0), IsVoice(true) {
	hImage = LoadGraph("data/image/AvaterChip.png");
	assert(hImage > 0);
	Screen::stress = 0;

}

Avatar::~Avatar()
{
	DeleteGraph(hImage);
}

void Avatar::Update()
{
	animX = (Screen::stress/10);
	if (prevAnim!=animX)
	{
		if (animX == 1)
		{
			PlaySoundFile("data/voice/AngryLevel1.mp3", DX_PLAYTYPE_BACK);
		}
		else if(animX==2)
		{
			PlaySoundFile("data/voice/AngryLevel2.mp3", DX_PLAYTYPE_BACK);
		}
		else if (animX == 3)
		{
			PlaySoundFile("data/voice/AngryLevel3.mp3", DX_PLAYTYPE_BACK);
		}
		else
		{
			PlaySoundFile("data/voice/AngryLevel4.mp3", DX_PLAYTYPE_BACK);
		}
	}

	
	if (Screen::stress >= 40)
	{
		SceneManager::ChangeScene("GAMEOVER");
	}
	prevAnim = animX;

	ImGui::Begin("Screen::stress");
	ImGui::InputInt("Screen::stress", &Screen::stress);
	ImGui::End();

}


void Avatar::Draw()
{
	//DrawExtendGraph(1100, 500, 1360, 765, hImage, 1);
	DrawRectExtendGraph(1040, 500, 1380, 765, 200*(animX), 0, 200, 150, hImage, 1);
}


void Avatar::StressSet(int s)
{
		Screen::stress += s;
	
}
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
	:hImage(-1), animX(0),qImage(-1) {
	hImage = LoadGraph("data/image/AvaterChip.png");
	qImage = LoadGraph("data/image/hatena.png");
	assert(hImage > 0);
	animX = (stress / 10);
	GameObject::StayOnSceneChange();
	//for (int i = 0; i < voicePath->size(); i++)
	//{
	//	hVoice[i]=LoadSoundMem
	//}

}

Avatar::~Avatar()
{
	DeleteGraph(hImage);
}

void Avatar::Update()
{
	maxStress / 4;
	animX = (stress / 10);

	if (prevAnim != animX)
	{
		this->PlayVoice(animX);
		prevAnim = animX;
	}
	if (stress >= maxStress)
	{
		this->StressReset();
		GameObject::StayOnSceneChange(false);
		SceneManager::ChangeScene("GAMEOVER");
		prevAnim = animX;

	}

	



	/*ImGui::Begin("Screen::stress");
	ImGui::InputInt("Screen::stress", &stress);
	ImGui::End();*/

}

void Avatar::Draw()
{

	DrawRectExtendGraph(1040, 600, 1380, Screen::HEIGHTSMALL, 200 * (animX), 0, 200, 150, hImage, 1);
	if (NoInstruction)
	{
		int nowTime = GetNowCount();
		DrawExtendGraph(1080, 400, 1400, 600, qImage, 1);

		if (nowTime - Time::startTime >= 600)
		{
			NoInstruction = false;
			nowTime = 0;
			Time::startTime = 0;
		}
		
	}
}


void Avatar::StressSet(int s)
{
	stress += s;

}

void Avatar::StressReset()
{
	stress = 0;

}

void Avatar::PlayVoice(int v)
{

	//PlaySoundFile(voicePath[v].c_str(), DX_PLAYTYPE_BACK);
	if (v == 0&&NoInstruction==false)
	{
		NoInstruction = true;
		Time::startTime = GetNowCount();
	}

}

#pragma once
#include "../Library/SceneBase.h"

class BackGround;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int hBGM_;
	BackGround* bg;
};

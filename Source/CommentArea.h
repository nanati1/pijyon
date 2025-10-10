#pragma once
#include "../Library/SceneBase.h"
#include"../Library/GameObject.h"

class CommentArea:public GameObject{
public:
	CommentArea();
	~CommentArea();
	void Update() override;
	void Draw() override;
private:
	int commentAreaWidth = 1920;
	int commentAreaHeight = 122;
	int commentAreaX = 0;
	int commentAreaY = 958;
	int commentBoxWidth = 1220;
	int commentBoxHeight = 48;
	int commentBoxX = 20;
	int commentBoxY = 995;
	int commentSendButtonWidth=80;
	int commentSendButtonHeight=48;
	int commentSendButtonX=1260;
	int commentSendButtonY=995;

	
};


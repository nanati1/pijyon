#pragma once
#include "../Library/SceneBase.h"
#include"../Library/GameObject.h"

namespace CommentUi {
	inline int AreaWidth = 1920;
	inline int AreaHeight = 122;
	inline int AreaX = 0;
	inline int AreaY = 958;
	inline int BoxWidth = 1220;
	inline int BoxHeight = 48;
	inline int BoxX = 20;
	inline int BoxY = 995;
	inline int SendButtonWidth = 80;
	inline int SendButtonHeight = 48;
	inline int SendButtonX = BoxX + BoxWidth;
	inline int SendButtonY = BoxY;

}

class CommentArea:public GameObject{
public:
	CommentArea();
	~CommentArea();
	void Update() override;
	void Draw() override;
	bool superChatOnUI = false;



	
};


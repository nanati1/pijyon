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
	
};


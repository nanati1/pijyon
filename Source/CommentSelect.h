#pragma once
#include "../Library/SceneBase.h"
#include"../Library/GameObject.h"

class CommentSelect :public GameObject {
public:
	CommentSelect();
	~CommentSelect();
	void Update() override;
	void Draw() override;
private:
	enum DirectionSelect {NONE,RIGHT,LEFT,};
	enum StateSelect {STOP,WORK,RUN,JUMP,};
	enum CommentLevel {KIND,NORMAL,SEVERE,};
	enum Select{DIRECTION,STATE,LEVEL,};

	Select focus_;
	DirectionSelect dir_;
	StateSelect st_;
	CommentLevel lv_;

};


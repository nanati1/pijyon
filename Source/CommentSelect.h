#pragma once
#include "CommentOutput.h"
#include "../Library/SceneBase.h"
#include"../Library/GameObject.h"

enum DirectionSelect { NONE, RIGHT, LEFT, };
enum StateSelect { STOP, WARK, RUN, JUMP, };
enum CommentLevel { KIND, NORMAL, SEVERE, };


class CommentSelect :public GameObject {
public:
	CommentSelect();
	~CommentSelect();
	void Update() override;
	void Draw() override;
private:
	enum Select{DIRECTION,STATE,LEVEL,};

	Select focus_;
	DirectionSelect dir_;
	StateSelect st_;
	CommentLevel lv_;
	CommentOutput* commentOutputInstance;
};


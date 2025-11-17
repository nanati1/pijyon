#pragma once
#include "CommentOutput.h"
#include "ChatOutput.h"
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

	int GetDirectionValue() const { return static_cast<int>(dir_); }
	int GetStateValue()     const { return static_cast<int>(st_); }
	int GetLevelValue()     const { return static_cast<int>(lv_); }
	bool IsSuperChatOn() const { return superChatOn_;}
	bool IsSuperChatMode()const { return superChatMode_; }
	void ToggleSuperChat();

private:
	enum Select{DIRECTION,STATE,LEVEL,};
	bool superChatOn_ = false;
	bool superChatMode_ = false;
	float superChatTimer;
	float superChatTimerCount;

	Select focus_;
	DirectionSelect dir_;
	StateSelect st_;
	CommentLevel lv_;
	CommentOutput* commentOutputInstance;
	ChatOutput* chatOutputInstance;
};


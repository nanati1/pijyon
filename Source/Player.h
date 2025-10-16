#pragma once
#include "Object2D.h"
#include <vector>

class Player : public Object2D {
public:
	Player();
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	float velocityY;
	bool onGround;
	bool prevPushed;
	bool autoMovingRight=true;

	float Gravity;
	float JumpHeight;
	float JumpV0;
	float moveSpeed;
	bool directionRight = true;//向き　右:true　左:false
	bool  walkByCommentActive = false; // コメント由来の継続歩行中か
	int   walkByCommentDir = 0;     // -1:左 / 0:停止 / +1:右
};
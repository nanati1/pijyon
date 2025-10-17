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
	float DashSpeed;
	float commentMoveSpeed ;
	float airMoveSpeed;//空中横移動の速度
	bool directionRight = true;//向き　右:true　左:false
	bool  walkByCommentActive = false; // コメント由来の継続歩行中か
	bool jumpMoveActive = false;//ジャンプ中の横移動
	bool stopAfterLanding = false;//停止状態からのジャンプの際着地時停止
	int  walkByCommentDir = 0;      // -1:左 / 0:そのまま / +1:右
	int  jumpMoveDir=0;				//↑と同じ
};
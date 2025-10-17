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
	float airMoveSpeed;//�󒆉��ړ��̑��x
	bool directionRight = true;//�����@�E:true�@��:false
	bool  walkByCommentActive = false; // �R�����g�R���̌p�����s����
	bool jumpMoveActive = false;//�W�����v���̉��ړ�
	bool stopAfterLanding = false;//��~��Ԃ���̃W�����v�̍ے��n����~
	int  walkByCommentDir = 0;      // -1:�� / 0:���̂܂� / +1:�E
	int  jumpMoveDir=0;				//���Ɠ���
};
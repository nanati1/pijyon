#pragma once
#include "Object2D.h"

class Enemy : public Object2D
{
public:
	Enemy();
	Enemy(VECTOR2 pos);
	~Enemy();
	void Update() override;
	void Draw() override;
	bool HitCheck(const VECTOR2& pos, float radius);
	void OnHit(); // �_���[�W��폜�Ȃ�
	bool HitCheckWithDir(const VECTOR2& pos, float radius, bool& hitFront);

private:
	float moveSpeed = 0.5f;           // �ړ����x
	float moveRange = 64.0f;          // ���E�ɓ����͈�
	float originX = 0.0f;             // ����X���W�i��_�j
	int moveDir = 1;                  // �ړ������i1:�E, -1:���j
};
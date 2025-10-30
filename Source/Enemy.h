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
	void OnHit(); // ダメージや削除など
	bool HitCheckWithDir(const VECTOR2& pos, float radius, bool& hitFront);

private:
	float moveSpeed = 0.5f;           // 移動速度
	float moveRange = 64.0f;          // 左右に動く範囲
	float originX = 0.0f;             // 初期X座標（基準点）
	int moveDir = 1;                  // 移動方向（1:右, -1:左）
};
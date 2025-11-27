#include "Enemy.h"
#include <assert.h>
#include "Stage.h"

Enemy::Enemy()
{
}

Enemy::Enemy(VECTOR2 pos)
{
	hImage = LoadGraph("data/image/toge.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 0;
	animY = 0;

	position = pos;
	originX = pos.x;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	position.x += moveSpeed * moveDir;

	// 範囲を超えたら反転（左右に移動）
	if (position.x > originX + moveRange || position.x < originX - moveRange) {
		moveDir *= -1;
	}
}

void Enemy::Draw()
{
	Object2D::Draw();
	SetDrawOrder(100);
	Stage* st = FindGameObject<Stage>();
	float x = position.x - st->ScrollX();
	DrawBox(x - 24, position.y - 32, x + 24, position.y + 32,
		GetColor(255, 0, 0), FALSE);
}

bool Enemy::HitCheck(const VECTOR2& pos, float radius)
{
	float dx = position.x - pos.x;
	float dy = position.y - pos.y;
	float distSq = dx * dx + dy * dy;
	float r = 24.0f + radius; // 敵サイズ + 弾サイズ
	return distSq < (r * r);
}

void Enemy::OnHit()
{
	DestroyMe();
}

bool Enemy::HitCheckWithDir(const VECTOR2& pos, float radius, bool& hitFront)
{
	float dx = position.x - pos.x;
	float dy = position.y - pos.y;
	float distSq = dx * dx + dy * dy;
	float r = 24.0f + radius;
	bool hit = distSq < r * r;
	if (hit) {
		// relative position: プレイヤーから見て dx>0なら敵は右に、dx<0なら左に
		hitFront = (moveDir > 0 ? dx < 0 : dx > 0);
		// moveDir>0: 敵は右向き → 前から当たるのはプレイヤーが右側（dx<0）の場合
	}
	return hit;
}

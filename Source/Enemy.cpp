#include "Enemy.h"
#include <assert.h>
#include "Stage.h"

Enemy::Enemy()
{
}

Enemy::Enemy(VECTOR2 pos)
{
	hImage = LoadGraph("data/image/tamadot.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 0;
	animY = 1;

	position = pos;
	originX = pos.x;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	position.x += moveSpeed * moveDir;

	// �͈͂𒴂����甽�]�i���E�Ɉړ��j
	if (position.x > originX + moveRange || position.x < originX - moveRange) {
		moveDir *= -1;
	}
}

void Enemy::Draw()
{
	Object2D::Draw();
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
	float r = 24.0f + radius; // �G�T�C�Y + �e�T�C�Y
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
		// relative position: �v���C���[���猩�� dx>0�Ȃ�G�͉E�ɁAdx<0�Ȃ獶��
		hitFront = (moveDir > 0 ? dx < 0 : dx > 0);
		// moveDir>0: �G�͉E���� �� �O���瓖����̂̓v���C���[���E���idx<0�j�̏ꍇ
	}
	return hit;
}

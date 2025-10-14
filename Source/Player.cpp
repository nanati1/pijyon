#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "CsvReader.h"
#include "Screen.h"


Player::Player() : Player(VECTOR2(100, 300))
{
}

Player::Player(VECTOR2 pos)
{
	// �p�����[�^�[��ǂ�
	CsvReader* csv = new CsvReader("data/playerParam.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		std::string tag = csv->GetString(i, 0);
		if (tag == "Gravity") {
			Gravity = csv->GetFloat(i, 1);
		}
		else if (tag == "JumpHeight") {
			JumpHeight = csv->GetFloat(i, 1);
		}
		else if (tag == "MoveSpeed") {
			moveSpeed = csv->GetFloat(i, 1);
		}
	}
	JumpV0 = -sqrtf(2.0f * Gravity * JumpHeight);

	hImage = LoadGraph("data/image/tamadot.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 0;
	animY = 3;

	position = pos;
	velocityY = 0.0f;
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* st = FindGameObject<Stage>();
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += moveSpeed;
		int push = st->CheckRight(position + VECTOR2(24, -31)); // �E��
		position.x -= push;
		push = st->CheckRight(position + VECTOR2(24, 31)); // �E��
		position.x -= push;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= moveSpeed;
		int push = st->CheckLeft(position + VECTOR2(-24, -31)); // ����
		position.x += push;
		push = st->CheckLeft(position + VECTOR2(-24, 31)); // ����
		position.x += push;
	}
	if (onGround) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (prevPushed == false) {
				velocityY = JumpV0;
			}
			prevPushed = true;
		}
		else {
			prevPushed = false;
		}
	}


	position.y += velocityY;
	velocityY += Gravity;
	onGround = false;
	if (velocityY < 0.0f) {
		int push = st->CheckUp(position + VECTOR2(-24, -31)); // ����
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
		push = st->CheckUp(position + VECTOR2(24, -31)); // �E��
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
	}
	else {
		int push = st->CheckDown(position + VECTOR2(-24, 31 + 1)); // ����
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
		}
		push = st->CheckDown(position + VECTOR2(24, 31 + 1)); // �E��
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
		}
	}

	// �v���C���[�̕\���ʒu���A700�����E��������A�X�N���[������
	if (st != nullptr) {
		float drawX = position.x - st->ScrollX(); // ���ꂪ�\�����W
		static const int RightLimit = 700;
		static const int LeftLimit = 24;
		if (drawX > RightLimit) {
			st->SetScrollX(position.x - RightLimit);
		}
		else if (drawX < LeftLimit) {
			position.x = LeftLimit + st->ScrollX();
		}
	}
	ImGui::Begin("Player");
	ImGui::Checkbox("onGround", &onGround);
	ImGui::InputFloat("positionY", &position.y);
	ImGui::End();

	//��ʔ����ɏo����X�^�[�g�n�_�ɖ߂�
	if (position.y >= 710)
	{
		/*position = VECTOR2(100, 635);
		Stage* st = FindGameObject<Stage>();
		if (st != nullptr) {
			st->SetScrollX(0);
		}*/
		SceneManager::ChangeScene("RETRY");

	}
}

void Player::Draw()
{

	Object2D::Draw();
	Stage* st = FindGameObject<Stage>();
	float x = position.x - st->ScrollX();
	DrawBox(x - 24, position.y - 32, x + 24, position.y + 32,
		GetColor(255, 0, 0), FALSE);

}

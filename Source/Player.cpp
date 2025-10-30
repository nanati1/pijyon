#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "CsvReader.h"
#include "Screen.h"
#include "Avatar.h"
#include "Enemy.h"
#include"CommentSelect.h"
#include"../Library/Input.h"
#include<stdlib.h>
#include<time.h>




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
		else if (tag == "DashSpeed") {
			DashSpeed = csv->GetFloat(i, 1);
		}
	}
	CsvReader* commentCsv = new CsvReader("data/commentParam.csv");
	for (int i = 0; i < commentCsv->GetLines(); i++) {
		std::string tag = commentCsv->GetString(i, 0);
		if (tag == "SevereProbability") {
			severeProbability = commentCsv->GetFloat(i, 1);
		}
		else if (tag == "NormalProbability") {
			normalProbability = commentCsv->GetFloat(i, 1);
		}
		else if (tag == "KindProbability") {
			kindProbability = commentCsv->GetFloat(i, 1);
		}
		else if (tag == "SevereCommentStress") {
			severeCommentStress = commentCsv->GetInt(i, 1);
		}
		else if (tag == "NormalCommentStress") { 
			normalCommentStress = commentCsv->GetInt(i, 1);
		}
		else if (tag == "KindCommentStress") {
			kindCommentStress = commentCsv->GetInt(i, 1);
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
	prevPushed = false;
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* st = FindGameObject<Stage>();
	Avatar* avt = FindGameObject<Avatar>();


	if (Input::IsKeyDown(KEY_INPUT_RETURN)) { 
		if (auto* cs = FindGameObject<CommentSelect>()) {
			const int dir = cs->GetDirectionValue(); // 0:None,1:Right,2:Left
			const int state = cs->GetStateValue();     // 0:Stop,1:Wark,2:Run,3Jump
			const int lv = cs->GetLevelValue();
			const bool superChatMode = cs->IsSuperChatMode();
			float r = rand() % 1000/10.0f;

			//�R�����g�ɏ]���m��
			bool moveProbabillity = false; 
			if (superChatMode == true) {
				moveProbabillity = true;
			}else{
				if (lv == SEVERE) {
					moveProbabillity = (r < severeProbability);
				}
				else if (lv == NORMAL) {
					moveProbabillity = (r < normalProbability);
				}
				else if (lv == KIND)
				{
					moveProbabillity = (r < kindProbability);
				}
			}

			if (moveProbabillity) {

				if (state == WARK) { // WARK �̂Ƃ������p�����s���X�V
					commentMoveSpeed = moveSpeed;
					if (dir == RIGHT) {             // RIGHT
						walkByCommentActive = true;
						walkByCommentDir = +1;
						directionRight = true;
					}
					else if (dir == LEFT) {        // LEFT
						walkByCommentActive = true;
						walkByCommentDir = -1;
						directionRight = false;
					}
					else {                      // NONE
						walkByCommentActive = true;
						walkByCommentDir = (directionRight ? +1 : -1);
					}
				}
				else if (state == STOP) { // STOP �w���Ŏ~�߂�
					walkByCommentActive = false;
					walkByCommentDir = 0;
					autoMovingRight = false;
				}
				else if (state == RUN) //RUN
				{
					commentMoveSpeed = DashSpeed;
					if (dir == RIGHT) {             // RIGHT
						walkByCommentActive = true;
						walkByCommentDir = +1;
						directionRight = true;
					}
					else if (dir == LEFT) {        // LEFT
						walkByCommentActive = true;
						walkByCommentDir = -1;
						directionRight = false;
					}
					else {                      // NONE
						walkByCommentActive = true;
						walkByCommentDir = (directionRight ? +1 : -1);
					}

				}
				else if (state == JUMP) {//JUMP
					const bool idleNow = (!walkByCommentActive && !autoMovingRight);
					if (onGround) {
						if (prevPushed == false) {
							velocityY = JumpV0;
							int dirH = 0;
							if (dir == 0)velocityY = JumpV0;
							else if (dir == RIGHT)dirH = +1;//RIGHT
							else if (dir == LEFT)dirH = -1;//LEFT
							else dirH = (directionRight ? +1 : -1);//NONE:���݂̌���
							if (idleNow && dirH != 0) {
								jumpMoveActive = true;
								jumpMoveDir = dirH;
								airMoveSpeed = moveSpeed;
								directionRight = (dirH > 0);
								stopAfterLanding = true;   // ���n�����犮�S��~
							}
						}

						prevPushed = true;
					}
					

				}
				else {
					autoMovingRight = false;

				}
			}
			if (superChatMode==false) {
				if (lv == KIND) {
					avt->StressSet(kindCommentStress);
				}
				if (lv == NORMAL) {
					avt->StressSet(normalCommentStress);
				}
				if (lv == SEVERE) {
					avt->StressSet(severeCommentStress);
				}
			}
			

		}
	}
	//�󒆈ړ�
	if (jumpMoveActive) {
		const float spd = (airMoveSpeed > 0.0f) ? airMoveSpeed : moveSpeed;

		if (jumpMoveDir == +1) {
			position.x += spd;
			int push = st->CheckRight(position + VECTOR2(24, -31));
			position.x -= push;
			push = st->CheckRight(position + VECTOR2(24, 31));
			position.x -= push;
		}
		else if (jumpMoveDir == -1) {
			position.x -= spd;
			int push = st->CheckLeft(position + VECTOR2(-24, -31));
			position.x += push;
			push = st->CheckLeft(position + VECTOR2(-24, 31));
			position.x += push;
		}
	}
	//  �R�����g�R���̌p�����s 
	if (walkByCommentActive) {
		if (walkByCommentDir == +1) {
			// �E�ցi�Փ˕␳���݁j
			position.x += commentMoveSpeed;
			int push = st->CheckRight(position + VECTOR2(24, -31)); // �E��
			position.x -= push;
			push = st->CheckRight(position + VECTOR2(24, 31));      // �E��
			position.x -= push;
		}
		else if (walkByCommentDir == -1) {
			// ���ցi�Փ˕␳���݁j
			position.x -= commentMoveSpeed;
			int push = st->CheckLeft(position + VECTOR2(-24, -31)); // ����
			position.x += push;
			push = st->CheckLeft(position + VECTOR2(-24, 31));      // ����
			position.x += push;
		}
	}
	else {

		// �E�Ɏ����ړ����Ȃ�E�ړ�����
		if (autoMovingRight) {
			position.x += moveSpeed;
			int push = st->CheckRight(position + VECTOR2(24, -31)); // �E��
			position.x -= push;
			push = st->CheckRight(position + VECTOR2(24, 31)); // �E��
			position.x -= push;
		}

		//	// D�L�[�́A�����ړ����Ă��Ȃ��Ƃ������L��
		//	if (!autoMovingRight && CheckHitKey(KEY_INPUT_D)) {
		//		position.x += moveSpeed;
		//		int push = st->CheckRight(position + VECTOR2(24, -31));
		//		position.x -= push;
		//		push = st->CheckRight(position + VECTOR2(24, 31));
		//		position.x -= push;

		//		autoMovingRight = true;// D�L�[���������玩���ړ��J�n
		//	}


		//	if (CheckHitKey(KEY_INPUT_A)) {
		//		position.x -= moveSpeed;
		//		int push = st->CheckLeft(position + VECTOR2(-24, -31)); // ����
		//		position.x += push;
		//		push = st->CheckLeft(position + VECTOR2(-24, 31)); // ����
		//		position.x += push;

		//		autoMovingRight = false;// A�L�[���������玩���ړ�����
		//	}
		//}
		/*if (onGround) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				if (prevPushed == false) {
					velocityY = JumpV0;
				}
				prevPushed = true;
			}
			else {
				prevPushed = false;
			}
		}*/

	}

	// �G�Ƃ̓����蔻��
	auto enemies = FindGameObjects<Enemy>();
	for (Enemy* e : enemies) {
		bool isFront = false;
		if (e->HitCheckWithDir(position, 30.0f, isFront)) {
			if (isFront) {
				// �O���瓖������ �� �v���C���[���S
				Avatar* avt = FindGameObject<Avatar>();
				avt->StressSet(10);
				SceneManager::ChangeScene("RETRY");
			}
			else {
				// �w�ォ�瓖������ �� �i��j���E�≽�����Ȃ�
			}
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

			if (jumpMoveActive) {//�R�����g�̃W�����v���̋���
				jumpMoveActive = false;
				jumpMoveDir = 0;

				if (stopAfterLanding) {
					walkByCommentActive = false;
					walkByCommentDir = 0;
					autoMovingRight = false;
					stopAfterLanding = false;
				}
			}
		}
		push = st->CheckDown(position + VECTOR2(24, 31 + 1)); // �E��
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
			prevPushed = false;
			if (jumpMoveActive) {//�R�����g�̃W�����v���̋���
				jumpMoveActive = false;
				jumpMoveDir = 0;

				if (stopAfterLanding) {
					walkByCommentActive = false;
					walkByCommentDir = 0;
					autoMovingRight = false;
					stopAfterLanding = false;
				}
			}
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


	
	//��ʂ̊O�ɏo����X�^�[�g�n�_�ɖ߂�
	if (position.y >= 710)
	{
		Avatar* avt = FindGameObject<Avatar>();
		avt->StressSet(10);
	
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

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
#include "KeyInput.h"
#include "AnalyzeKey.h"




Player::Player() : Player(VECTOR2(100, 300))
{
}

Player::Player(VECTOR2 pos)
{
	// パラメーターを読む
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
	AnalyzeKey* cs = FindGameObject<AnalyzeKey>();
	KeyInput* ki = FindGameObject<KeyInput>();
	if (ki->GetKeyCheck()==true) { 
		//if (AnalyzeKey* cs = FindGameObject<AnalyzeKey>()) {
			const int dir = cs->GetDir(); // 0:None,1:Right,2:Left
			const std::string state = cs->GetAction();
			const int lv = cs->GetLevel();
			//const bool superChatMode = cs->IsSuperChatMode();
			float r = rand() % 1000/10.0f;

			//コメントに従う確率
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

				if (state == "WALK") { // WARK のときだけ継続歩行を更新
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
				else if (state == "STOP") { // STOP 指示で止める
					walkByCommentActive = false;
					walkByCommentDir = 0;
					autoMovingRight = false;
				}
				else if (state == "RUN") //RUN
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
				else if (state == "JUMP") {//JUMP
					
					const bool idleNow = (!walkByCommentActive && !autoMovingRight);
					if (onGround) {
						if (prevPushed == false) {
							velocityY = JumpV0;
							int dirH = 0;
							if (dir == 0)velocityY = JumpV0;
							else if (dir == RIGHT)dirH = +1;//RIGHT
							else if (dir == LEFT)dirH = -1;//LEFT
							else dirH = (directionRight ? +1 : -1);//NONE:現在の向き
							if (idleNow && dirH != 0) {
								jumpMoveActive = true;
								jumpMoveDir = dirH;
								airMoveSpeed = moveSpeed;
								directionRight = (dirH > 0);
								stopAfterLanding = true;   // 着地したら完全停止
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
			

		//}
	}
	//空中移動
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
	//  コメント由来の継続歩行 
	if (walkByCommentActive) {
		if (walkByCommentDir == +1) {
			// 右へ（衝突補正込み）
			position.x += commentMoveSpeed;
			int push = st->CheckRight(position + VECTOR2(24, -31)); // 右上
			position.x -= push;
			push = st->CheckRight(position + VECTOR2(24, 31));      // 右下
			position.x -= push;
		}
		else if (walkByCommentDir == -1) {
			// 左へ（衝突補正込み）
			position.x -= commentMoveSpeed;
			int push = st->CheckLeft(position + VECTOR2(-24, -31)); // 左上
			position.x += push;
			push = st->CheckLeft(position + VECTOR2(-24, 31));      // 左下
			position.x += push;
		}
	}
	else {

		// 右に自動移動中なら右移動処理
		if (autoMovingRight) {
			position.x += moveSpeed;
			int push = st->CheckRight(position + VECTOR2(24, -31)); // 右上
			position.x -= push;
			push = st->CheckRight(position + VECTOR2(24, 31)); // 右下
			position.x -= push;
		}

		//	// Dキーは、自動移動していないときだけ有効
		//	if (!autoMovingRight && CheckHitKey(KEY_INPUT_D)) {
		//		position.x += moveSpeed;
		//		int push = st->CheckRight(position + VECTOR2(24, -31));
		//		position.x -= push;
		//		push = st->CheckRight(position + VECTOR2(24, 31));
		//		position.x -= push;

		//		autoMovingRight = true;// Dキーを押したら自動移動開始
		//	}


		//	if (CheckHitKey(KEY_INPUT_A)) {
		//		position.x -= moveSpeed;
		//		int push = st->CheckLeft(position + VECTOR2(-24, -31)); // 左上
		//		position.x += push;
		//		push = st->CheckLeft(position + VECTOR2(-24, 31)); // 左下
		//		position.x += push;

		//		autoMovingRight = false;// Aキーを押したら自動移動解除
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

	// 敵との当たり判定
	auto enemies = FindGameObjects<Enemy>();
	for (Enemy* e : enemies) {
		bool isFront = false;
		if (e->HitCheckWithDir(position, 30.0f, isFront)) {
			if (isFront) {
				// 前から当たった → プレイヤー死亡
				Avatar* avt = FindGameObject<Avatar>();
				avt->StressSet(10);
				SceneManager::ChangeScene("RETRY");
			}
			else {
				// 背後から当たった → （例）相殺や何もしない
			}
		}
	}


	position.y += velocityY;
	velocityY += Gravity;
	onGround = false;
	if (velocityY < 0.0f) {
		int push = st->CheckUp(position + VECTOR2(-24, -31)); // 左下
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
		push = st->CheckUp(position + VECTOR2(24, -31)); // 右下
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
	}
	else {
		int push = st->CheckDown(position + VECTOR2(-24, 31 + 1)); // 左下
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;

			if (jumpMoveActive) {//コメントのジャンプ時の挙動
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
		push = st->CheckDown(position + VECTOR2(24, 31 + 1)); // 右下
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
			prevPushed = false;
			if (jumpMoveActive) {//コメントのジャンプ時の挙動
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

	// プレイヤーの表示位置が、700よりも右だったら、スクロールする
	if (st != nullptr) {
		float drawX = position.x - st->ScrollX(); // これが表示座標
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


	
	//画面の外に出たらスタート地点に戻る
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

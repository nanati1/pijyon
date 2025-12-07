#include"CommentSelect.h"
#include <DxLib.h>
#include"CommentArea.h"
#include"CommentDatabase.h"
#include"../Library/Input.h"
#include "CsvReader.h"
#include<stdlib.h>
#include"Time.h"

enum ComemntUI {
	UI_NONE, UI_RIGHT, UI_LEFT, UI_STOP, UI_WARK, UI_JUMP, UI_KIND, UI_NORMAL, UI_SEVERE
};


CommentSelect::CommentSelect()
	:focus_(Select::DIRECTION), dir_(DirectionSelect::NONE), st_(StateSelect::STOP), lv_(CommentLevel::KIND)
{
	focus_ = DIRECTION;
	dir_=NONE;
	st_=STOP;
	lv_ = KIND;

	hImageCommentSelectUI = LoadGraph("data/image/comment/CommentSelectUI.png");
	hImageSuperChatSelectUI=LoadGraph("data/image/comment/SuperChatCommentSelectUI.png");
	hImageArrowUp = LoadGraph("data/image/comment/CommentArrow.png");
	hImageArrowDown = LoadGraph("data/image/comment/CommentArrowDown.png");
	commentOutputInstance = new CommentOutput();
	chatOutputInstance = new ChatOutput();
	Input::Initialize();
	CsvReader* commentCsv = new CsvReader("data/commentParam.csv");
	for (int i = 0; i < commentCsv->GetLines(); i++) {
		std::string tag = commentCsv->GetString(i, 0);
		if (tag == "SuperChatTimer") {
			superChatTimerCount = commentCsv->GetFloat(i, 1);
		}
		if (tag == "SuperChatCounter") {
			superChatCounter = commentCsv->GetInt(i, 1);
		}

	}
	GameObject::StayOnSceneChange();
}

CommentSelect::~CommentSelect()
{
}

void CommentSelect::Update()
{
	Time::Refresh();
	float dt = Time::DeltaTime();
	Input::Update();
	//コメント欄の選択
	if (Input::IsKeyDown(KEY_INPUT_RIGHT)) {
		switch (focus_) {
		case Select::DIRECTION:focus_ = Select::STATE; break;
		case Select::STATE:focus_ = Select::LEVEL; break;
		case Select::LEVEL:focus_ = Select::DIRECTION; break;
		default:break;
		}
	}
	if (Input::IsKeyDown(KEY_INPUT_LEFT)) {
		switch (focus_) {
		case Select::DIRECTION:focus_ = Select::LEVEL; break;
		case Select::STATE:focus_ = Select::DIRECTION; break;
		case Select::LEVEL:focus_ = Select::STATE; break;
		default:break;
		}
	}

	//方向の選択
	if (focus_ == Select::DIRECTION) {
		if (Input::IsKeyDown(KEY_INPUT_UP)) {
			switch (dir_) {
			case DirectionSelect::NONE:dir_ = DirectionSelect::RIGHT; break;
			case DirectionSelect::RIGHT:dir_ = DirectionSelect::LEFT; break;
			case DirectionSelect::LEFT:dir_ = DirectionSelect::NONE; break;
			default:break;
			}
		}
		if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
			switch (dir_) {
			case DirectionSelect::NONE:dir_ = DirectionSelect::LEFT; break;
			case DirectionSelect::RIGHT:dir_ = DirectionSelect::NONE; break;
			case DirectionSelect::LEFT:dir_ = DirectionSelect::RIGHT; break;
			default:dir_ = DirectionSelect::NONE; break;
			}
		}
	}

	//命令の選択
	if (focus_ == Select::STATE) {
		if (Input::IsKeyDown(KEY_INPUT_UP)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::WARK; break;
#if 0
			case StateSelect::WARK:st_ = StateSelect::RUN; break;
#else
			case StateSelect::WARK:st_ = StateSelect::JUMP; break;
#endif
			case StateSelect::RUN:st_ = StateSelect::JUMP; break;
			case StateSelect::JUMP:st_ = StateSelect::STOP; break;
			default:break;
			}
		}
		if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::JUMP; break;

			case StateSelect::WARK:st_ = StateSelect::STOP; break;
#if 0
			case StateSelect::JUMP:st_ = StateSelect::RUN; break;
#else
			case StateSelect::JUMP:st_ = StateSelect::WARK; break;
#endif
			default:break;
			}
		}
	}

	//コメントのレベルの選択
	if (focus_ == Select::LEVEL) {
		if (Input::IsKeyDown(KEY_INPUT_UP)) {
			switch (lv_) {
			case CommentLevel::KIND:lv_ = CommentLevel::NORMAL; break;
			case CommentLevel::NORMAL:lv_ = CommentLevel::SEVERE; break;
			case CommentLevel::SEVERE:lv_ = CommentLevel::KIND; break;
			default:break;
			}
		}
		if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
			switch (lv_) {
			case CommentLevel::KIND:lv_ = CommentLevel::SEVERE; break;
			case CommentLevel::NORMAL:lv_ = CommentLevel::KIND; break;
			case CommentLevel::SEVERE:lv_ = CommentLevel::NORMAL; break;
			default:break;
			}
		}
	}

	if (Input::IsKeyDown(KEY_INPUT_RETURN)) {
		if (superChatOn_) {
			superChatMode_ = true;

		}

		srand((unsigned int)time(NULL));
		//if (st_ == StateSelect::STOP) {
		//	dir_ = DirectionSelect::NONE;
		//}
		if (commentOutputInstance) {
			std::string comment = CommentDatabase::GetComment(dir_, st_, lv_);
			commentOutputInstance->SetCommentText(comment);
			if (chatOutputInstance) {
				chatOutputInstance->AddChat(comment);
			}
		}
	}
	if (superChatCounter > 0) {
		if (Input::IsKeyDown(KEY_INPUT_LSHIFT) || Input::IsKeyDown(KEY_INPUT_RSHIFT)) {
			ToggleSuperChat();

		}
	}

	if( commentOutputInstance) {
		commentOutputInstance->Update();
	}
	if (superChatMode_) {

		if (superChatTimer > 0.0f) {
			superChatTimer -= dt;
		}
		if (superChatTimer < 0.0f) {
			superChatMode_ = false;
			superChatOn_ = false;
			superChatCounter--;

		}
	}
	else {
		superChatTimer = superChatTimerCount;
	}
}

void CommentSelect::Draw()
{
	int commentSelectNumber = 3;

	//文字の描画
	std::string superChatCount = std::to_string(superChatCounter);
	SetFontSize(40);//文字サイズ
	DrawFormatString(1430, 950,GetColor(255,0,0),"スパチャ残り%d回", superChatCounter);
	SetFontSize(30);
	DrawString((CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber) / 2-20, CommentUi::BoxY - 70, "方向", GetColor(255, 0, 0));
	DrawString((CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber + CommentUi::BoxWidth / commentSelectNumber * 2) / 2-20, CommentUi::BoxY - 70, "動作", GetColor(255, 0, 0));
	DrawString((CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2 + CommentUi::BoxWidth) / 2-95, CommentUi::BoxY - 70, "コメントレベル", GetColor(255, 0, 0));
	SetFontSize(23);
	int rowDir = UI_NONE;

	switch (dir_) {
	case DirectionSelect::NONE:  rowDir = UI_NONE;  break;
	case DirectionSelect::RIGHT: rowDir = UI_RIGHT; break;
	case DirectionSelect::LEFT:  rowDir = UI_LEFT;  break;
	default: break;
	}

	int cellW = CommentUi::BoxWidth / commentSelectNumber;
	int cellH = CommentUi::BoxHeight;

	DrawRectGraph(
		CommentUi::BoxX,
		CommentUi::BoxY,
		0,
		cellH * rowDir,
		cellW,
		cellH,
		(superChatOn_ ? hImageSuperChatSelectUI : hImageCommentSelectUI),
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX,
		CommentUi::BoxY -CommentArrowHeight,
		hImageArrowUp,
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX,
		CommentUi::BoxY + CommentUi::BoxHeight,
		hImageArrowDown,
		TRUE
	);

	int rowState = UI_STOP;
	switch (st_) {
	case StateSelect::STOP:rowState = UI_STOP; break;
	case StateSelect::WARK:rowState = UI_WARK; break;
	case StateSelect::JUMP:rowState = UI_JUMP; break;
	default:break;
	}

	DrawRectGraph(
		CommentUi::BoxX + cellW,   // 真ん中
		CommentUi::BoxY,
		0,
		cellH * rowState,
		cellW,
		cellH,
		(superChatOn_ ? hImageSuperChatSelectUI : hImageCommentSelectUI),
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX+cellW,
		CommentUi::BoxY - CommentArrowHeight,
		hImageArrowUp,
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX+cellW,
		CommentUi::BoxY + CommentUi::BoxHeight,
		hImageArrowDown,
		TRUE
	);



	int rowLevel = UI_KIND;
	switch (lv_) {
	case CommentLevel::KIND:   rowLevel = UI_KIND;   break;
	case CommentLevel::NORMAL: rowLevel = UI_NORMAL; break;
	case CommentLevel::SEVERE: rowLevel = UI_SEVERE; break;
	default: break;
	}

	DrawRectGraph(
		CommentUi::BoxX + cellW * 2, // 右
		CommentUi::BoxY,
		0,
		cellH * rowLevel,
		cellW,
		cellH,
		(superChatOn_?hImageSuperChatSelectUI:hImageCommentSelectUI),
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX+cellW*2,
		CommentUi::BoxY - CommentArrowHeight,
		hImageArrowUp,
		TRUE
	);
	DrawGraph(
		CommentUi::BoxX+cellW*2,
		CommentUi::BoxY + CommentUi::BoxHeight,
		hImageArrowDown,
		TRUE
	);


	//コメント選択の描画
	for (int i = 1; i <= commentSelectNumber; i++) {
		DrawBox(CommentUi::BoxX, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * i,
			CommentUi::BoxY + CommentUi::BoxHeight,
			(superChatMode_ ? GetColor(255, 215, 0) : GetColor(0, 0, 255)), FALSE, 5);
	}


	//選択中の枠線の色を変える
	switch (focus_) {
	case Select::DIRECTION:
		DrawBox(CommentUi::BoxX, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		DrawString((CommentUi::BoxX+CommentUi::BoxWidth / commentSelectNumber)/2, CommentUi::BoxY - 30, "↓", GetColor(255, 0, 0));
		break;
	case Select::STATE:
		DrawBox(CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		DrawString((CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber + CommentUi::BoxWidth / commentSelectNumber * 2) / 2, CommentUi::BoxY - 30, "↓", GetColor(255, 0, 0));
		break;
	case Select::LEVEL:
		DrawBox(CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		DrawString((CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2 + CommentUi::BoxWidth) / 2, CommentUi::BoxY - 30, "↓", GetColor(255, 0, 0));
		break;
	default:break;
	}


	


	// コメントのログ描画
	if (commentOutputInstance) {
		commentOutputInstance->Draw();
	}
}

void CommentSelect::ToggleSuperChat()
{
	superChatOn_ = !superChatOn_;
}

#include"CommentSelect.h"
#include <DxLib.h>
#include"CommentArea.h"
#include"CommentDatabase.h"
#include"../Library/Input.h"

CommentSelect::CommentSelect()
	:focus_(Select::DIRECTION), dir_(DirectionSelect::NONE), st_(StateSelect::STOP), lv_(CommentLevel::KIND)
{
	focus_ = DIRECTION;
	dir_=NONE;
	st_=STOP;
	lv_ = KIND;

	commentOutputInstance = new CommentOutput();
	Input::Initialize();

}

CommentSelect::~CommentSelect()
{
}

void CommentSelect::Update()
{
	Input::Update();
	//�R�����g���̑I��
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

	//�����̑I��
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

	//���߂̑I��
	if (focus_ == Select::STATE) {
		if (Input::IsKeyDown(KEY_INPUT_UP)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::WARK; break;
			case StateSelect::WARK:st_ = StateSelect::RUN; break;
			case StateSelect::RUN:st_ = StateSelect::JUMP; break;
			case StateSelect::JUMP:st_ = StateSelect::STOP; break;
			default:break;
			}
		}
		if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::JUMP; break;
			case StateSelect::WARK:st_ = StateSelect::STOP; break;
			case StateSelect::RUN:st_ = StateSelect::WARK; break;
			case StateSelect::JUMP:st_ = StateSelect::RUN; break;
			default:break;
			}
		}
	}

	//�R�����g�̃��x���̑I��
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

		if(st_==StateSelect::STOP) {
			dir_ = DirectionSelect::NONE;
		}
		if (commentOutputInstance) {
			std::string comment = CommentDatabase::GetComment(dir_, st_, lv_);
			commentOutputInstance->SetCommentText(comment);
		}
	}

	if( commentOutputInstance) {
		commentOutputInstance->Update();
	}
}

void CommentSelect::Draw()
{
	int commentSelectNumber = 3;

	//�R�����g�I���̕`��
	for (int i = 1; i <= commentSelectNumber; i++) {
		DrawBox(CommentUi::BoxX, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * i,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(0, 0, 255), FALSE, 5);
	}
	//�I�𒆂̘g���̐F��ς���
	switch (focus_) {
	case Select::DIRECTION:
		DrawBox(CommentUi::BoxX, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		break;
	case Select::STATE:
		DrawBox(CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		break;
	case Select::LEVEL:
		DrawBox(CommentUi::BoxX + CommentUi::BoxWidth / commentSelectNumber * 2, CommentUi::BoxY,
			CommentUi::BoxX + CommentUi::BoxWidth,
			CommentUi::BoxY + CommentUi::BoxHeight,
			GetColor(255, 0, 0), FALSE, 5);
		break;
	default:break;
	}
	//�����̕`��
	switch (dir_) {
		case DirectionSelect::NONE:
			break;
		case DirectionSelect::RIGHT:
			DrawString(CommentUi::BoxX + 20, CommentUi::BoxY + 20, "RIGHT", GetColor(255, 255, 255));
			break;
		case DirectionSelect::LEFT:
			DrawString(CommentUi::BoxX + 20, CommentUi::BoxY + 20, "LEFT", GetColor(255, 255, 255));
			break;
		default:break;

	}
	switch (st_) {
	case StateSelect::STOP:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 + 20, CommentUi::BoxY + 20, "STOP", GetColor(255, 255, 255));
		break;
	case StateSelect::WARK:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 + 20, CommentUi::BoxY + 20, "WARK", GetColor(255, 255, 255));
		break;
	case StateSelect::RUN:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 + 20, CommentUi::BoxY + 20, "RUN", GetColor(255, 255, 255));
		break;
	case StateSelect::JUMP:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 + 20, CommentUi::BoxY + 20, "JUMP", GetColor(255, 255, 255));
		break;
	default:break;
	}
	switch (lv_) {
	case CommentLevel::KIND:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 * 2 + 20, CommentUi::BoxY + 20, "KIND", GetColor(255, 255, 255));
		break;
	case CommentLevel::NORMAL:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 * 2 + 20, CommentUi::BoxY + 20, "NORMAL", GetColor(255, 255, 255));
		break;
	case CommentLevel::SEVERE:
		DrawString(CommentUi::BoxX + CommentUi::BoxWidth / 3 * 2 + 20, CommentUi::BoxY + 20, "SEVERE", GetColor(255, 255, 255));
		break;
	default:break;
	}

	if (commentOutputInstance) {
		commentOutputInstance->Draw();
	}

}

#include"CommentSelect.h"
#include <DxLib.h>
#include"CommentArea.h"

CommentSelect::CommentSelect()
	:focus_(Select::DIRECTION), dir_(DirectionSelect::NONE), st_(StateSelect::STOP), lv_(CommentLevel::KIND)
{
	focus_ = DIRECTION;
	dir_=NONE;
	st_=STOP;
	lv_ = KIND;


}

CommentSelect::~CommentSelect()
{
}

void CommentSelect::Update()
{
	//コメント欄の選択
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		switch (focus_) {
		case Select::DIRECTION:focus_ = Select::STATE; break;
		case Select::STATE:focus_ = Select::LEVEL; break;
		case Select::LEVEL:focus_ = Select::DIRECTION; break;
		default:break;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		switch (focus_) {
		case Select::DIRECTION:focus_ = Select::LEVEL; break;
		case Select::STATE:focus_ = Select::DIRECTION; break;
		case Select::LEVEL:focus_ = Select::STATE; break;
		default:break;
		}
	}
	
	//方向の選択
	if (focus_ == Select::DIRECTION) {
		if (CheckHitKey(KEY_INPUT_UP)) {
			switch (dir_) {
			case DirectionSelect::NONE:dir_ = DirectionSelect::LEFT; break;
			case DirectionSelect::LEFT:dir_ = DirectionSelect::RGHT; break;
			case DirectionSelect::RGHT:dir_ = DirectionSelect::NONE; break;
			default:break;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			switch (dir_) {
			case DirectionSelect::NONE:dir_ = DirectionSelect::RGHT; break;
			case DirectionSelect::LEFT:dir_ = DirectionSelect::NONE; break;
			case DirectionSelect::RGHT:dir_ = DirectionSelect::LEFT; break;
			default:break;
			}
		}
	}
	
	//命令の選択
	if (focus_ == Select::STATE) {
		if (CheckHitKey(KEY_INPUT_UP)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::WORK; break;
			case StateSelect::WORK:st_ = StateSelect::RUN; break;
			case StateSelect::RUN:st_ = StateSelect::JUMP; break;
			case StateSelect::JUMP:st_ = StateSelect::STOP; break;
			default:break;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			switch (st_) {
			case StateSelect::STOP:st_ = StateSelect::JUMP; break;
			case StateSelect::WORK:st_ = StateSelect::STOP; break;
			case StateSelect::RUN:st_ = StateSelect::WORK; break;
			case StateSelect::JUMP:st_ = StateSelect::RUN; break;
			default:break;
			}
		}
	}

	//コメントのレベルの選択
	if (focus_ == Select::LEVEL) {
		if (CheckHitKey(KEY_INPUT_UP)) {
			switch (lv_) {
			case CommentLevel::KIND:lv_ = CommentLevel::NORMAL; break;
			case CommentLevel::NORMAL:lv_ = CommentLevel::SEVERE; break;
			case CommentLevel::SEVERE:lv_ = CommentLevel::KIND; break;
			default:break;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			switch (lv_) {
			case CommentLevel::KIND:lv_ = CommentLevel::SEVERE; break;
			case CommentLevel::NORMAL:lv_ = CommentLevel::KIND; break;
			case CommentLevel::SEVERE:lv_ = CommentLevel::NORMAL; break;
			default:break;
			}
		}
	}

}

void CommentSelect::Draw()
{

}

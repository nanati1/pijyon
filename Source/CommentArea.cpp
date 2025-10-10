#include "CommentArea.h"
#include <DxLib.h>
#include "Screen.h"
#include"CommentSelect.h"

CommentArea::CommentArea()
{
	new CommentSelect();
}

CommentArea::~CommentArea()
{
}

void CommentArea::Update()
{
}

void CommentArea::Draw()
{
	//コメント入力領域
	//DrawBox(commentAreaX, commentAreaY, commentAreaX + commentAreaWidth, commentAreaY + commentAreaHeight, GetColor(255, 255, 255), TRUE);

	//コメント入力欄
	DrawBox(CommentUi::BoxX, CommentUi:: BoxY, CommentUi::BoxX + CommentUi::BoxWidth, CommentUi::BoxY + CommentUi::BoxHeight, GetColor(200, 200, 200), TRUE);

	//コメント送信ボタン
	DrawBox(CommentUi::SendButtonX, CommentUi::SendButtonY, CommentUi::SendButtonX + CommentUi::SendButtonWidth, CommentUi::SendButtonY + CommentUi::SendButtonHeight, GetColor(100, 100, 255), TRUE);
}

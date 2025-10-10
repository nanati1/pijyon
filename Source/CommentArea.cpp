#include "CommentArea.h"
#include <DxLib.h>
#include "Screen.h"

CommentArea::CommentArea()
{
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
	DrawBox(commentBoxX, commentBoxY, commentBoxX + commentBoxWidth, commentBoxY + commentBoxHeight, GetColor(200, 200, 200), TRUE);

	//コメント送信ボタン
	DrawBox(commentSendButtonX, commentSendButtonY, commentSendButtonX + commentSendButtonWidth, commentSendButtonY + commentSendButtonHeight, GetColor(100, 100, 255), TRUE);
}

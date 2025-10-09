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
	int commentAreaWidth = 1920;
	int commentAreaHeight = 122;
	int commentAreaX = 0;
	int commentAreaY = 958;
	DrawBox(commentAreaX, commentAreaY, commentAreaX + commentAreaWidth, commentAreaY + commentAreaHeight, GetColor(255, 255, 255), TRUE);

	//コメント入力欄
	int commentBoxWidth = commentAreaWidth*18/20;
	int commentBoxHeight = commentAreaHeight*4/6;
	int commentBoxX = commentAreaWidth/20;
	int commentBoxY = commentAreaY+commentAreaHeight/6;
	DrawBox(commentBoxX, commentBoxY, commentBoxX + commentBoxWidth, commentBoxY + commentBoxHeight, GetColor(200, 200, 200), TRUE);

}

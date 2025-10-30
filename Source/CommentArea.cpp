#include "CommentArea.h"
#include <DxLib.h>
#include "Screen.h"
#include"CommentSelect.h"
#include"CommentOutput.h"

CommentArea::CommentArea()
{
	new CommentSelect();
	new CommentOutput();
}

CommentArea::~CommentArea()
{
}

void CommentArea::Update()
{
	superChatOnUI = false;//�X�[�p�[�`���b�g���
	if (auto* cs = FindGameObject<CommentSelect>()) {
		superChatOnUI = cs->IsSuperChatOn();
	}

}

void CommentArea::Draw()
{
	//�R�����g���͗̈�
	//DrawBox(commentAreaX, commentAreaY, commentAreaX + commentAreaWidth, commentAreaY + commentAreaHeight, GetColor(255, 255, 255), TRUE);

	//�R�����g���͗�
	DrawBox(CommentUi::BoxX, CommentUi:: BoxY, 
		CommentUi::BoxX + CommentUi::BoxWidth, CommentUi::BoxY + CommentUi::BoxHeight, 
		(superChatOnUI?GetColor(255, 255, 0):GetColor(200,200,200)), TRUE);

	//�R�����g���M�{�^��
	DrawBox(CommentUi::SendButtonX, CommentUi::SendButtonY, CommentUi::SendButtonX + CommentUi::SendButtonWidth, CommentUi::SendButtonY + CommentUi::SendButtonHeight, GetColor(100, 100, 255), TRUE);
}

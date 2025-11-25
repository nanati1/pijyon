#include "CommentOutput.h"
#include"CommentSelect.h"
#include <DxLib.h>
#include <algorithm>
#include <assert.h>

CommentOutput::CommentOutput()
{
    bImage_ = LoadGraph("data/image/chat.jpg");
    assert(bImage_ > 0);
	mobDB_.Load("data/mobComments.csv");
}

CommentOutput::~CommentOutput()
{
    if (bImage_ > 0) {
        DeleteGraph(bImage_);
    }
}

void CommentOutput::AddMobComment() {
    std::string text = mobDB_.GetRandom();
    if (text.empty())return;
    SetCommentText(text,true);

	if (auto* chat = FindGameObject<ChatOutput>()) {
		chat->AddChat(text, true);  //*trueでモブ
	}
}

void CommentOutput::SetCommentText(const std::string& comment,bool isMob) {
    Comment com;
    com.text = comment;
    com.isMob = isMob;
    com.x = streamX_ + streamW_;  // 右端から
    // 上下にはみ出さないように lineHeight_ を引いた範囲で乱数
    int maxYSpan = (std::max)(0, streamH_ - lineHeight_);
    int randOff = (maxYSpan > 0) ? GetRand(maxYSpan) : 0;
    com.y = streamY_ + randOff;

    com.vx = defaultVx_;
    com.vy = defaultVy_;
    com.width = GetDrawStringWidth(com.text.c_str(), (int)com.text.size());
    com.height = lineHeight_;
	if (auto* cs = FindGameObject<CommentSelect>()) {
		com.superChatMode = cs->IsSuperChatMode();
	}

    comments_.push_back(std::move(com));

}

void CommentOutput::Update() {
    for (auto& com : comments_) {
        com.x -= com.vx;
        com.y += com.vy;
    }
    // 左に画面外へ出たものだけ削除
    comments_.erase(
        std::remove_if(comments_.begin(), comments_.end(),
            [](const Comment& com) { return (com.x + com.width) < 0; }),
        comments_.end()
    );

    mobCommentTimer++;
    if (mobCommentTimer >= nextMobComment) {
        mobCommentTimer = 0;

        nextMobComment = GetRand(120) + 180;

        AddMobComment();
    }
}

void CommentOutput::Draw() {
    RECT oldRect;
    GetDrawArea(&oldRect);

    SetDrawArea(
		streamX_, 
        streamY_, 
        streamX_ + streamW_,
        streamY_ + streamH_
    );

    for (const auto& com : comments_) {
            if (com.superChatMode) {
                if (com.isMob == false)DrawBox(com.x, com.y, com.x + com.width, com.y + com.height, GetColor(255, 0, 0), TRUE);
            }
            if (com.isMob == false) {
                DrawString(com.x, com.y, com.text.c_str(), GetColor(0, 127, 255));
            }
            else {
                DrawString(com.x, com.y, com.text.c_str(), GetColor(0, 0, 0));
            }
        }

    SetDrawAreaFull();
}

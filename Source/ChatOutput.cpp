#include "ChatOutput.h"
#include"CommentSelect.h"
#include <DxLib.h>
#include <algorithm>
#include <assert.h>

ChatOutput::ChatOutput()
{
    hImage_ = LoadGraph("data/image/chat.png");
    assert(hImage_ > 0);
}

ChatOutput::~ChatOutput()
{
    if (hImage_ > 0) {
        DeleteGraph(hImage_);
    }
}

void ChatOutput::AddChat(const std::string& text)
{
    Chat cht;
    cht.text = text;
    cht.x = chatX_;
    cht.y = chatY_0_;
    cht.vx = chatVx_;
    cht.vy = chatVy_;
    cht.height = lineHeight_;
	cht.width = GetDrawStringWidth(cht.text.c_str(), (int)cht.text.size());

    if (auto* cs = FindGameObject<CommentSelect>()) {
		cht.superChatMode = cs->IsSuperChatMode();
    }
    else {
		cht.superChatMode = false;
    }

    chats_.push_back(std::move(cht));
}

void ChatOutput::Update()
{
    for (auto& cht : chats_) {
        cht.x -= cht.vx;
        cht.y -= cht.vy; // 上に流す
    }

    // 上に画面外へ出たものだけ削除
    chats_.erase(
        std::remove_if(chats_.begin(), chats_.end(),
            [&](const Chat& cht) {
                // チャット欄上端(areaY_)より上に消えたら削除
                return (cht.y + lineHeight_) < areaY_;
            }),
        chats_.end()
    );
}

void ChatOutput::Draw()
{
  //  DrawExtendGraph(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, bImage_, TRUE);
    for (const auto& cht : chats_) {
        DrawBox(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, GetColor(255, 255, 255), TRUE);
        if (cht.superChatMode) {
            DrawBox(cht.x, cht.y, cht.x+cht.width, cht.y + cht.height, GetColor(255, 0, 0), TRUE);
        }
        DrawString(cht.x, cht.y, cht.text.c_str(), GetColor(0, 0, 0));
    }
    DrawExtendGraph(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, hImage_, TRUE);

}

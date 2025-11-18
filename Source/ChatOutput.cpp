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
    int h = lineHeight_;
    for (auto& c : chats_) {
        c.y -= h;
    }

    Chat cht;
    cht.text = text;
    cht.vx = 0;
    cht.vy = 0;
    cht.height = h;
	cht.width = GetDrawStringWidth(cht.text.c_str(), (int)cht.text.size());

    if (auto* cs = FindGameObject<CommentSelect>()) {
		cht.superChatMode = cs->IsSuperChatMode();
    }
    else {
		cht.superChatMode = false;
    }

    cht.x = chatX_;
    cht.y = areaY_ + areaH_ - h;
    chats_.push_back(std::move(cht));
}

void ChatOutput::Update()
{
    //for (auto& cht : chats_) {
    //    cht.x -= cht.vx;
    //    cht.y -= cht.vy; // è„Ç…ó¨Ç∑
    //}

    // è„Ç…âÊñ äOÇ÷èoÇΩÇ‡ÇÃÇæÇØçÌèú
    chats_.erase(
        std::remove_if(chats_.begin(), chats_.end(),
            [&](const Chat& c) {
                return c.y + c.height < areaY_;
            }),
        chats_.end()
    );
    
}

void ChatOutput::Draw()
{

    for (const auto& cht : chats_) {
      //  DrawBox(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, GetColor(255, 255, 255), TRUE);
        if (cht.superChatMode) {
            DrawBox(cht.x, cht.y, cht.x+cht.width, cht.y + cht.height, GetColor(255, 0, 0), TRUE);
        }
        DrawString(cht.x, cht.y, cht.text.c_str(), GetColor(0, 0, 0));
    }
    DrawExtendGraph(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, hImage_, TRUE);

}

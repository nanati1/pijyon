#include "ChatOutput.h"
#include"CommentSelect.h"
#include <DxLib.h>
#include <algorithm>
#include <assert.h>

ChatOutput::ChatOutput()
{
    hImage_ = LoadGraph("data/image/chat.png");
    hImageSuperChatRad = LoadGraph("data/image/comment/superChatRad.png");
    assert(hImage_ > 0);
}

ChatOutput::~ChatOutput()
{
    if (hImage_ > 0) {
        DeleteGraph(hImage_);
    }
}

void ChatOutput::AddChat(const std::string& text,bool isMob)
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
    cht.isMob = isMob;

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
	SetDrawArea(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_);
    for (const auto& cht : chats_) {
        if (cht.superChatMode) {
            if(cht.isMob==false)DrawGraph(cht.x, cht.y-cht.height, hImageSuperChatRad, TRUE);
        }
        if (cht.isMob == false) { 
            DrawString(cht.x, cht.y, cht.text.c_str(), (cht.superChatMode ? GetColor(255,255,255): GetColor(0, 127, 255)));
        }
        else{
			DrawString(cht.x, cht.y, cht.text.c_str(), GetColor(0, 0, 0));
        }
    }
    DrawExtendGraph(areaX_, areaY_, areaX_ + areaW_, areaY_ + areaH_, hImage_, TRUE);
    SetDrawAreaFull();
}

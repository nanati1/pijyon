#pragma once
#include "../Library/GameObject.h"
#include <string>
#include <vector>

class ChatOutput : public GameObject
{
public:
    ChatOutput();
    ~ChatOutput();

    void AddChat(const std::string& comment);  // チャット追加
    void Update() override;
    void Draw() override;

    void SetArea(int x, int y, int w, int h) {
        areaX_ = x; areaY_ = y; areaW_ = w; areaH_ = h;
    }
    void SetLineHeight(int h) { lineHeight_ = h; }
    void SetScrollSpeed(int vy) { chatVy_ = vy; }

private:
    struct Chat {
        std::string text;
        int x = 0;
        int y = 0;
        int vx = 0;
        int vy = 0;
        int height = 0;   
        int width = 0;
        bool superChatMode = false;
    };

    int hImage_ = -1;      // 枠画像

    // チャット欄の範囲
    int areaX_ = 1360;
    int areaY_ = 72;
    int areaW_ = 560;
    int areaH_ = 765;
    int lineHeight_ = 28;

    int chatX_ = 1400;    // チャットの開始X
    int chatY_0_ = 800;    // 新規チャットの開始Y（下側）
    int chatVx_ = 0;
    int chatVy_ = 2;       // 上へスクロール速度

    std::vector<Chat> chats_;
};

#pragma once
#include "../Library/GameObject.h"
#include <string>
#include <vector>
#include"MobCommentDatabase.h"

class CommentOutput : public GameObject
{
public:
    CommentOutput();
    ~CommentOutput();
    void SetCommentText(const std::string& comment, bool isMob = false);
    void Update() override;
    void Draw() override;

    void AddMobComment();
    void SetSpeed(int vx, int vy = 0) { defaultVx_ = vx; defaultVy_ = vy; }
    void SetStreamArea(int x, int y, int w, int h) {
        streamX_ = x; streamY_ = y; streamW_ = w; streamH_ = h;
    }
    void SetLineHeight(int h) { lineHeight_ = h; }
    void Clear() { comments_.clear(); }

private:
    struct Comment {
        std::string text;
        int x = 0;
        int y = 0;
        int vx = 0;
        int vy = 0;
        int width = 0; // ピクセル幅（左に抜けた判定用）
		int height = 0;
		bool superChatMode = false;
        bool isMob = false;

    };

    int bImage_ = -1;      //チャット背景


    // 配信画面の範囲
    int streamX_ = 0;
    int streamY_ = 72;
    int streamW_ = 1360;
    int streamH_ = 765;
    int lineHeight_ = 28;


    int defaultVx_ = 2;   // 左方向（Updateでマイナスする）
    int defaultVy_ = 0;

    std::vector<Comment> comments_;

    MobCommentDatabase mobDB_;
    int mobCommentTimer = 0;
    int nextMobComment = 300;

};

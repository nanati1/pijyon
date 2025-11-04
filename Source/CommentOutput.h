#pragma once
#include"../Library/GameObject.h"
#include<string>
#include<vector>

class CommentOutput :
    public GameObject
{
public:
    void SetCommentText(const std::string& comment);   
    void Update()override;
    void Draw()override;


    void SetY(int y) { baseY_ = y; }
    void SetSpeed(int vx, int vy = 0) { defaultVx_ = vx; defaultVy_ = vy; }
    void SetScreenWidth(int w) { screenW_ = w; }
    void Clear() { items_.clear(); }

    void SetStreamArea(int x, int y, int w, int h) {
        streamX_ = x; streamY_ = y; streamW_ = w; streamH_ = h;
    }
    // 1行の高さ（フォントサイズ相当）。上下のはみ出し防止に使う
    void SetLineHeight(int h) { lineHeight_ = h; }
private:
    struct Item {
        std::string text;
        int x;
        int y;
        int vx;
        int vy;
        int width; // ピクセル幅（左に抜けた判定用）
    };

    // 既存フィールドは内部デフォルトに変更
    int screenW_ = 1360;
    int baseY_ = 100;
    int defaultVx_ = 2;  
    int defaultVy_ = 0;
    //配信画面の範囲
    int streamX_ = 0, streamY_ = 72, streamW_ = 1360, streamH_ = 765;
    int lineHeight_ = 28;

    std::vector<Item> items_;
};


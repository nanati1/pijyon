
#include "CommentOutput.h"
#include <DxLib.h>
#include<algorithm>
void CommentOutput::SetCommentText(const std::string& comment) {
    Item it;
    it.text = comment;
    it.x = streamX_ + streamW_;

    // --- Yを配信画面内でランダムにする ---
    // 上下にはみ出さないように lineHeight_ を引いた範囲で乱数
    int maxYSpan = (std::max)(0, streamH_ - lineHeight_);
    int randOff = (maxYSpan > 0) ? GetRand(maxYSpan) : 0;
    it.y = streamY_ + randOff;

    it.vx = defaultVx_;
    it.vy = defaultVy_;
    it.width = GetDrawStringWidth(it.text.c_str(), (int)it.text.size());
    items_.push_back(std::move(it));
}

void CommentOutput::Update() {
    for (auto& it : items_) {
        it.x -= it.vx;
        it.y += it.vy;
    }
    // 左に画面外へ出たものだけ削除（末尾が0未満）
    items_.erase(
        std::remove_if(items_.begin(), items_.end(),
            [](const Item& it) { return (it.x + it.width) < 0; }),
        items_.end()
    );
}

void CommentOutput::Draw() {
    for (const auto& it : items_) {
        DrawString(it.x, it.y, it.text.c_str(), GetColor(0, 0, 0));
    }
}


#include "CommentOutput.h"
#include <DxLib.h>
void CommentOutput::SetCommentText(const std::string& comment) {
    currentComment_ = comment;
    x_ = 1360;
}

void CommentOutput::Update() {
    x_ -= vx_;
    y_ += vy_;

}

void CommentOutput::Draw() {
    if (!currentComment_.empty()) {
        DrawString(x_, y_, currentComment_.c_str(), GetColor(0, 0, 0));
    }
}

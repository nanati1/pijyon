// CommentDatabase.cpp
#include "CommentDatabase.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace {
    void InitRandom() {
        static bool inited = false;
        if (!inited) { std::srand((unsigned)std::time(nullptr)); inited = true; }
    }
    std::string R(const std::vector<std::string>& v) {
        if (v.empty()) return "";
        return v[std::rand() % v.size()];
    }
}

std::string CommentDatabase::GetComment(DirectionSelect dir, StateSelect state, CommentLevel level) {
    InitRandom();

    std::string head; // 方向
    switch (dir) {
    case DirectionSelect::NONE:  head = R({ "そのまま", "今のまま" }); break;
    case DirectionSelect::RIGHT: head = R({ "右へ", "右方向に" });     break;
    case DirectionSelect::LEFT:  head = R({ "左へ", "左方向に" });     break;
    default: head = "不明な方向"; break; 
    }

    std::string body; // 状態×レベル
    switch (state) {
    case StateSelect::STOP:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "止まってください", "いったん止まって" }); break;
        case CommentLevel::NORMAL: body = R({ "止まって", "そこで止まれ" });             break;
        case CommentLevel::SEVERE: body = R({ "止まれ!!!", "止まれ、バカ" });            break;
        }
        break;

    case StateSelect::WARK: 
        switch (level) {
        case CommentLevel::KIND:   body = R({ "歩いて", "少しずつ進んで" }); break;
        case CommentLevel::NORMAL: body = R({ "歩け", "進め" });             break;
        case CommentLevel::SEVERE: body = R({ "歩け!!!", "歩け、バカ" });     break;
        }
        break;

    case StateSelect::RUN:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "走って", "急いで" });           break;
        case CommentLevel::NORMAL: body = R({ "走れ", "ダッシュ" });           break;
        case CommentLevel::SEVERE: body = R({ "全力で走れ", "走れ!!!" });       break;
        }
        break;

    case StateSelect::JUMP:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "ジャンプして", "飛び越えて" }); break;
        case CommentLevel::NORMAL: body = R({ "ジャンプしろ", "飛び越えろ" }); break;
        case CommentLevel::SEVERE: body = R({ "ジャンプしろ!!!" });            break;
        }
        break;

    default:
        body = "不明な状態";
        break;
    }

    if (!head.empty() && !body.empty()) return head + " " + body;
    if (!head.empty()) return head;
    if (!body.empty()) return body;
    return "コメント未定義";
}

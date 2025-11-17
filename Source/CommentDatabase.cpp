// CommentDatabase.cpp
#include "CommentDatabase.h"
#include "CsvReader.h"
#include <vector>
#include <cstdlib>
#include <ctime>

struct CommandComment {
    DirectionSelect dir;
    StateSelect state;
    CommentLevel level;
    std::string text;
};

namespace {
    std::vector<CommandComment> g_comments;
    bool g_loaded = false;
    bool g_randInit = false;

    void InitRandom() {
        if (!g_randInit) {
            std::srand((unsigned)std::time(nullptr));
            g_randInit = true;
        }
    }

    DirectionSelect ToDir(const std::string& s) {
        if (s == "NONE")  return DirectionSelect::NONE;
        if (s == "RIGHT") return DirectionSelect::RIGHT;
        if (s == "LEFT")  return DirectionSelect::LEFT;
        // 不正値はとりあえず NONE
        return DirectionSelect::NONE;
    }

    StateSelect ToState(const std::string& s) {
        if (s == "STOP") return StateSelect::STOP;
        if (s == "WALK") return StateSelect::WARK; 
        if (s == "WARK") return StateSelect::WARK;
        if (s == "RUN")  return StateSelect::RUN;
        if (s == "JUMP") return StateSelect::JUMP;
        return StateSelect::STOP;
    }

    CommentLevel ToLevel(const std::string& s) {
        if (s == "KIND")   return CommentLevel::KIND;
        if (s == "NORMAL") return CommentLevel::NORMAL;
        if (s == "SEVERE") return CommentLevel::SEVERE;
        return CommentLevel::NORMAL;
    }

    void LoadIfNeeded() {
        if (g_loaded) return;

        CsvReader csv("data/commentCommand.csv"); // パスはプロジェクトに合わせて

        int lines = csv.GetLines();
        if (lines > 1) {
            for (int i = 1; i < lines; ++i) { // 0行目はヘッダ前提
                CommandComment c;
                c.dir = ToDir(csv.GetString(i, 0)); // Direction
                c.state = ToState(csv.GetString(i, 1)); // State
                c.level = ToLevel(csv.GetString(i, 2)); // Level
                c.text = csv.GetString(i, 3);  // Text

                if (!c.text.empty()) {
                    g_comments.push_back(c);
                }
            }
        }
        g_loaded = true;
    }

    // 条件に合うコメント群からランダムに1つ返す
    std::string PickRandom(DirectionSelect dir, StateSelect state, CommentLevel level, bool ignoreStateLevel) {
        InitRandom();
        LoadIfNeeded();

        std::vector<std::string> candidates;

        for (auto& c : g_comments) {
            if (c.dir != dir) continue;

            if (!ignoreStateLevel) {
                if (c.state != state) continue;
                if (c.level != level) continue;
            }
            candidates.push_back(c.text);
        }

        if (candidates.empty()) {
            return "コメント未登録";
        }

        int r = std::rand() % candidates.size();
        return candidates[r];
    }
}

// dir のみ指定版（state/level 無視して方向だけで選ぶ）
std::string CommentDatabase::GetComment(DirectionSelect dir)
{
    // State/Level は無視して、その dir に合うコメントから適当に
    return PickRandom(dir, StateSelect::STOP, CommentLevel::NORMAL, true);
}

// dir + state + level 版（完全一致）
std::string CommentDatabase::GetComment(DirectionSelect dir, StateSelect state, CommentLevel level)
{
    return PickRandom(dir, state, level, false);
}

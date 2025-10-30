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

    std::string head; // ����
    switch (dir) {
    case DirectionSelect::NONE:  head = R({ "���̂܂�", "���̂܂�" }); break;
    case DirectionSelect::RIGHT: head = R({ "�E��", "�E������" });     break;
    case DirectionSelect::LEFT:  head = R({ "����", "��������" });     break;
    default: head = "�s���ȕ���"; break; 
    }

    std::string body; // ��ԁ~���x��
    switch (state) {
    case StateSelect::STOP:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "�~�܂��Ă�������", "��������~�܂���" }); break;
        case CommentLevel::NORMAL: body = R({ "�~�܂���", "�����Ŏ~�܂�" });             break;
        case CommentLevel::SEVERE: body = R({ "�~�܂�!!!", "�~�܂�A�o�J" });            break;
        }
        break;

    case StateSelect::WARK: 
        switch (level) {
        case CommentLevel::KIND:   body = R({ "������", "�������i���" }); break;
        case CommentLevel::NORMAL: body = R({ "����", "�i��" });             break;
        case CommentLevel::SEVERE: body = R({ "����!!!", "�����A�o�J" });     break;
        }
        break;

    case StateSelect::RUN:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "������", "�}����" });           break;
        case CommentLevel::NORMAL: body = R({ "����", "�_�b�V��" });           break;
        case CommentLevel::SEVERE: body = R({ "�S�͂ő���", "����!!!" });       break;
        }
        break;

    case StateSelect::JUMP:
        switch (level) {
        case CommentLevel::KIND:   body = R({ "�W�����v����", "��щz����" }); break;
        case CommentLevel::NORMAL: body = R({ "�W�����v����", "��щz����" }); break;
        case CommentLevel::SEVERE: body = R({ "�W�����v����!!!" });            break;
        }
        break;

    default:
        body = "�s���ȏ��";
        break;
    }

    if (!head.empty() && !body.empty()) return head + " " + body;
    if (!head.empty()) return head;
    if (!body.empty()) return body;
    return "�R�����g����`";
}

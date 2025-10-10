#pragma once
#include <cstdint>

namespace Input
{
    // DxLib_Init() �����1��Ăԁiprev �o�b�t�@���������j
    void Initialize();

    // ���t���[���ŏ��ɌĂԁiprev �� now�Anow ���X�V�j
    void Update();

    // �����Ă���� true
    bool IsKey(int keyCode);

    // �������u�Ԃ��� true�i1�t���[���j
    bool IsKeyDown(int keyCode);

    // �������u�Ԃ��� true�i1�t���[���j
    bool IsKeyUp(int keyCode);
}
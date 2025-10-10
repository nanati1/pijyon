#pragma once
#include <cstdint>

namespace Input
{
    // DxLib_Init() 直後に1回呼ぶ（prev バッファを初期化）
    void Initialize();

    // 毎フレーム最初に呼ぶ（prev ← now、now を更新）
    void Update();

    // 押している間 true
    bool IsKey(int keyCode);

    // 押した瞬間だけ true（1フレーム）
    bool IsKeyDown(int keyCode);

    // 離した瞬間だけ true（1フレーム）
    bool IsKeyUp(int keyCode);
}
#include "Input.h"
#include <DxLib.h>

namespace {
    static unsigned char sNow[256]{};
    static unsigned char sPrev[256]{};
}

namespace Input
{
    void Initialize()
    {
        // 1�t���[���ڂ� prev �𑵂���
        GetHitKeyStateAll(reinterpret_cast<char*>(sNow));
        for (int i = 0; i < 256; ++i) sPrev[i] = sNow[i];
    }

    void Update()
    {
        // �O���� �̏��ōX�V
        for (int i = 0; i < 256; ++i) sPrev[i] = sNow[i];
        GetHitKeyStateAll(reinterpret_cast<char*>(sNow));
    }

    bool IsKey(int keyCode)
    {
        return sNow[keyCode] != 0;
    }

    bool IsKeyDown(int keyCode)
    {
        return (sNow[keyCode] != 0) && (sPrev[keyCode] == 0);
    }

    bool IsKeyUp(int keyCode)
    {
        return (sNow[keyCode] == 0) && (sPrev[keyCode] != 0);
    }
}

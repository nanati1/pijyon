#include "KeyInput.h"

KeyInput::KeyInput()
{
    // キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
    InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
    // 作成したキー入力ハンドルをアクティブにする
    SetActiveKeyInput(InputHandle);
    //キー入力の色を変更
    SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR,GetColor(0, 0, 0));
    
}

KeyInput::~KeyInput()
{
    // 用済みのインプットハンドルを削除する
    DeleteKeyInput(InputHandle);
}

void KeyInput::Update()
{
    if (CheckKeyInput(InputHandle) == true)
    {
        SetKeyInputString("", InputHandle);
        SetActiveKeyInput(InputHandle);
        GetKeyInputString(String, InputHandle);
    }
}

void KeyInput::Draw()
{
    // 入力モードを描画
    DrawKeyInputModeString(30, 850);

    // 入力途中の文字列を描画
    DrawKeyInputString(30, 800, InputHandle);

}






    


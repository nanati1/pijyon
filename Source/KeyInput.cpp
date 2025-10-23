#include "KeyInput.h"

KeyInput::KeyInput()
{
    // キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
    InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
    // 作成したキー入力ハンドルをアクティブにする
    SetActiveKeyInput(InputHandle);


}

KeyInput::~KeyInput()
{
    // 用済みのインプットハンドルを削除する
    DeleteKeyInput(InputHandle);


}

void KeyInput::Update()
{

    // 入力された文字列を取得
    GetKeyInputString(String, InputHandle);

}

void KeyInput::Draw()
{
    // 入力モードを描画
    DrawKeyInputModeString(640, 480);

    // 入力途中の文字列を描画
    DrawKeyInputString(0, 0, InputHandle);

}






    


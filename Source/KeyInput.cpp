#include "KeyInput.h"  
#include "AnalyzeKey.h"  
#include "CsvReader.h"  

KeyInput::KeyInput()  
{  
   // キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)  
   InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);  
   // 作成したキー入力ハンドルをアクティブにする  
   SetActiveKeyInput(InputHandle);  
   //キー入力の色を変更  
   SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, GetColor(0, 0, 0));  
   command = new CsvReader("data/KeyComment.csv"); 
}  

KeyInput::~KeyInput()  
{  
   // 用済みのインプットハンドルを削除する  
   DeleteKeyInput(InputHandle); 
   delete command; // command のメモリを解放  
}  

void KeyInput::Update()  
{  
   //キー入力が終了したら  
   if (CheckKeyInput(InputHandle) == true)  
   {  
       GetKeyInputString(String, InputHandle); //値を取得 
       SetKeyInputString("", InputHandle); //中を初期化  
       SetActiveKeyInput(InputHandle); //もう一度入力可能状態に  
   }  
}  

void KeyInput::Draw()  
{  
   // 入力モードを描画  
   DrawKeyInputModeString(30, 850);  

   // 入力途中の文字列を描画  
   DrawKeyInputString(30, 800, InputHandle);  
}
        

#include "KeyInput.h"  
#include "AnalyzeKey.h"   
#include "CommentOutput.h"
KeyInput::KeyInput()  
{  
   // キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)  
   InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);  
   // 作成したキー入力ハンドルをアクティブにする  
   SetActiveKeyInput(InputHandle);  
   //キー入力の色を変更  
   SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, GetColor(0, 0, 0));  

   new AnalyzeKey();
   comOut=new CommentOutput();
}  

KeyInput::~KeyInput()  
{  
   // 用済みのインプットハンドルを削除する  
   DeleteKeyInput(InputHandle); 
}  

void KeyInput::Update()  
{  
   //キー入力が終了したら  
   if (CheckKeyInput(InputHandle) == true)  
   { 
       keyCheck = CheckKeyInput(InputHandle);
       GetKeyInputString(String, InputHandle); //値を取得 
       comOut->SetCommentText(String);
       if(AnalyzeKey* al = FindGameObject<AnalyzeKey>())
       al->AnalyzeComm(String);
       SetKeyInputString("", InputHandle); //中を初期化  
       
       SetActiveKeyInput(InputHandle); //もう一度入力可能状態に  
   }  
   comOut->Update();
}  

void KeyInput::Draw()  
{  
   // 入力モードを描画  
   DrawKeyInputModeString(30, 850);  

   // 入力途中の文字列を描画  
   DrawKeyInputString(30, 800, InputHandle);  

   if (comOut) {
       comOut->Draw();
   }
}
        

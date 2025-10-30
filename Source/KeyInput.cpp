#include "KeyInput.h"  
#include "AnalyzeKey.h"   
#include "CommentOutput.h"
KeyInput::KeyInput()  
{  
   // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)  
   InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);  
   // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���  
   SetActiveKeyInput(InputHandle);  
   //�L�[���͂̐F��ύX  
   SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, GetColor(0, 0, 0));  

   AnK = new AnalyzeKey();
   comOut=new CommentOutput();
}  

KeyInput::~KeyInput()  
{  
   // �p�ς݂̃C���v�b�g�n���h�����폜����  
   DeleteKeyInput(InputHandle); 
}  

void KeyInput::Update()  
{  
   //�L�[���͂��I��������  
   if (CheckKeyInput(InputHandle) == true)  
   {  
       GetKeyInputString(String, InputHandle); //�l���擾 
       comOut->SetCommentText(String);
       SetKeyInputString("", InputHandle); //����������  
       
       SetActiveKeyInput(InputHandle); //������x���͉\��Ԃ�  
   }  
   comOut->Update();
}  

void KeyInput::Draw()  
{  
   // ���̓��[�h��`��  
   DrawKeyInputModeString(30, 850);  

   // ���͓r���̕������`��  
   DrawKeyInputString(30, 800, InputHandle);  

   if (comOut) {
       comOut->Draw();
   }
}
        

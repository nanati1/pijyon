#include "KeyInput.h"  
#include "AnalyzeKey.h"  
#include "CsvReader.h"  

KeyInput::KeyInput()  
{  
   // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)  
   InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);  
   // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���  
   SetActiveKeyInput(InputHandle);  
   //�L�[���͂̐F��ύX  
   SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, GetColor(0, 0, 0));  
   command = new CsvReader("data/KeyComment.csv"); 
}  

KeyInput::~KeyInput()  
{  
   // �p�ς݂̃C���v�b�g�n���h�����폜����  
   DeleteKeyInput(InputHandle); 
   delete command; // command �̃����������  
}  

void KeyInput::Update()  
{  
   //�L�[���͂��I��������  
   if (CheckKeyInput(InputHandle) == true)  
   {  
       GetKeyInputString(String, InputHandle); //�l���擾 
       SetKeyInputString("", InputHandle); //����������  
       SetActiveKeyInput(InputHandle); //������x���͉\��Ԃ�  
   }  
}  

void KeyInput::Draw()  
{  
   // ���̓��[�h��`��  
   DrawKeyInputModeString(30, 850);  

   // ���͓r���̕������`��  
   DrawKeyInputString(30, 800, InputHandle);  
}
        

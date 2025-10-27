#include "KeyInput.h"

KeyInput::KeyInput()
{
    // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
    InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
    // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
    SetActiveKeyInput(InputHandle);
    //�L�[���͂̐F��ύX
    SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR,GetColor(0, 0, 0));
    
}

KeyInput::~KeyInput()
{
    // �p�ς݂̃C���v�b�g�n���h�����폜����
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
    // ���̓��[�h��`��
    DrawKeyInputModeString(30, 850);

    // ���͓r���̕������`��
    DrawKeyInputString(30, 800, InputHandle);

}






    


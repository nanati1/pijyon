#include "KeyInput.h"

KeyInput::KeyInput()
{
    // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
    InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
    // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
    SetActiveKeyInput(InputHandle);


}

KeyInput::~KeyInput()
{
    // �p�ς݂̃C���v�b�g�n���h�����폜����
    DeleteKeyInput(InputHandle);


}

void KeyInput::Update()
{

    // ���͂��ꂽ��������擾
    GetKeyInputString(String, InputHandle);

}

void KeyInput::Draw()
{
    // ���̓��[�h��`��
    DrawKeyInputModeString(640, 480);

    // ���͓r���̕������`��
    DrawKeyInputString(0, 0, InputHandle);

}






    


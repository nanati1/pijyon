#include "KeyInput.h"

KeyInput::KeyInput()
{
}

KeyInput::~KeyInput()
{
    // �p�ς݂̃C���v�b�g�n���h�����폜����
    DeleteKeyInput(InputHandle);

}

void KeyInput::Update()
{
}


    char String[256];
    int InputHandle;

    // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
    InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);

    // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
    SetActiveKeyInput(InputHandle);

        // ���̓��[�h��`��
        DrawKeyInputModeString(640, 480);

        // ���͓r���̕������`��
        DrawKeyInputString(0, 0, InputHandle);

       
    // ���͂��ꂽ��������擾
    GetKeyInputString(String, InputHandle);

    
    // ��ʂ̏�����
    ClearDrawScreen();

    // ���͂��ꂽ���������ʂɕ\������
    DrawString(0, 0, "���Ȃ������͂����������", GetColor(255, 255, 255));
    DrawString(0, 16, String, GetColor(255, 255, 255));

    // ����ʂ̓��e��\��ʂɔ��f������
    ScreenFlip();

    // �L�[���͑҂�
    WaitKey();

    // �c�w���C�u�����̎g�p�I��
    DxLib_End();

    // �I��
    return 0;
}
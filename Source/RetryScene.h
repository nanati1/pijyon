#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class RetryScene : public SceneBase
{
public:
	RetryScene();
	~RetryScene();
	void Update() override;
	void Draw() override;
};

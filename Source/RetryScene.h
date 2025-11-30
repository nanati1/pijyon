#pragma once
#include "../Library/SceneBase.h"

class BackGround;
/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class RetryScene : public SceneBase
{
public:
	RetryScene();
	~RetryScene();
	void Update() override;
	void Draw() override;
private:
	BackGround* bg;
};

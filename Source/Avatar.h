#pragma once
#include "Object2D.h"
#include <vector>
#include "../ImGui/imgui.h"
class Avatar : public Object2D {
public:

	Avatar();
	~Avatar();
	void Update()override;
	void Draw() override;
	void StressSet(int s);
	int GetStress() { return stress; }
	void StressReset();
	void PlayVoice(int v = 0);//何も代入しないければ失敗ボイス
private:
	int animX;//表情を変えるための変数。0～3,大きくなるほど怒る
	int hImage;//画像ハンドル
	static int prevAnim; //ストレス値を取得するための変数
	static int stress; //ストレス値
	static const int maxStress = 40; //最大ストレス値
};
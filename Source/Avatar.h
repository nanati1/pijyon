#pragma once
#include "Object2D.h"
#include <vector>
#include "../ImGui/imgui.h"
#include "Screen.h"
class Avatar : public Object2D {
public:

	Avatar();
	~Avatar();
	void Update()override;
	void Draw() override;
	void StressSet(int s);
	int GetStress() { return Screen::stress; }
private:
	int stress ; //ストレス値を取得するための変数
	int hImage;//画像ハンドル
	int animX;//表情を変えるための変数。0～3,大きくなるほど怒る
};
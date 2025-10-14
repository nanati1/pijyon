#pragma once
#include "Object2D.h"
#include <vector>

class Avatar : public Object2D {
public:
	Avatar();
	Avatar(VECTOR2 pos);
	~Avatar();
	void Update(int stress);
	void Draw() override;
private:
	int hImage;//画像ハンドル

	int animX;//表情を変えるための変数。0～3,大きくなるほど怒る
};
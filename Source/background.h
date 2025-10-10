#pragma once
#include "Object2D.h"
#include <vector>

class BackGround : public Object2D{
public:
	BackGround();
	BackGround(VECTOR2 pos);
	~BackGround();
	void Update() override;
	void Draw() override;
private:
	int wImage;
	int rImage;
	
};
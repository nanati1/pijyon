#pragma once
#include "Object2D.h"
#include <vector>

class Avatar : public Object2D {
public:
	Avatar();
	Avatar(VECTOR2 pos);
	~Avatar();
	void Update() override;
	void Draw() override;
private:
	int aImage;
	int rImage;

};
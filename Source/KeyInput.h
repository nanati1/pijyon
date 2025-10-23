#pragma once
#include "Object2D.h"

class KeyInput
	:public  Object2D
{
public:
	KeyInput();
	~KeyInput();	
	void Update() override;
	void Draw() override;
private:
	char String[256];
	int InputHandle;
};


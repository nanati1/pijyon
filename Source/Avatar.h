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
	int hImage;//�摜�n���h��

	int animX;//�\���ς��邽�߂̕ϐ��B0�`3,�傫���Ȃ�قǓ{��
};
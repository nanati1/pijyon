#pragma once
#include "Object2D.h"
#include <vector>
#include "../ImGui/imgui.h"
class Avatar : public Object2D {
public:
	Avatar();
	Avatar(VECTOR2 pos);
	~Avatar();
	void Update()override;
	void Draw() override;
	void StressSet(int s);
	int GetStress() { return stress; }
private:
	int stress ; //�X�g���X�l���擾���邽�߂̕ϐ�
	int hImage;//�摜�n���h��
	int animX;//�\���ς��邽�߂̕ϐ��B0�`3,�傫���Ȃ�قǓ{��
};
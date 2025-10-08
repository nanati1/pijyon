#pragma once
#include "Object2D.h"
#include <vector>

class Stage : public Object2D {
public:
	Stage();
	~Stage();
	void Draw() override;
	float ScrollX() { return scrollX; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="sc">  </param>
	void SetScrollX(float sc) { scrollX = sc; }

	/// <summary>
	/// �w�肵���_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="pos">���ׂ�_</param>
	/// <returns>�������Ă���΁A���ɉ����Ԃ���</returns>
	int CheckRight(VECTOR2 pos);

	int CheckLeft(VECTOR2 pos);

	int CheckDown(VECTOR2 pos);

	int CheckUp(VECTOR2 pos);
private:
	float scrollX; // ���X�N���[����
	int bImage;
	bool IsWall(VECTOR2 pos);

	std::vector<std::vector<int>> map;
};

#pragma once


namespace Input
{
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);
	bool IsKeyDown(int keyCode);
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown();
	bool IsMouseUP();
	bool IsMouseKeep();
	bool IsButtonDown(int button);
	bool IsButtonUP(int button);
	bool IsButtonKeep(int button);
}

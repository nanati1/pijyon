#pragma once
#include <iostream>
#include <string>
#include <vector>



class CsvReader;

struct CommandResult {
	std::string action;  // ���o���ꂽ�s���L�[���[�h
	int badLevel = 0;    // �ő�̖\�����x��
};

struct CommandData
{
	std::string type;   // ��ށimove, bad�Ȃǁj
	std::string word;   // �Ή�����P��"�E, �o�J�Ȃǁj
	int level = 0;      // �\�����x��
	int priority = 0;   // �s���D��x
};


class AnalyzeKey
{
public:
	AnalyzeKey();
	~AnalyzeKey();
	void Update() ;
	CommandResult AnalyzeComm(std::string comment);
private:
	std::vector<CommandData> commands;
	int prevPri=0;// �D��x�Ō��܂�ŏI�s��
};


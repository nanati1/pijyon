#pragma once
#include <iostream>
#include <string>
#include <vector>



class CsvReader;

struct CommandResult {
	std::vector<std::string> action;  // ���o���ꂽ�s���L�[���[�h
	int badLevel = 0;                 // �ő�̖\�����x��
	std::string finalAction;          // �D��x�Ō��܂�ŏI�s��
};


class AnalyzeKey
{
public:
	AnalyzeKey();
	~AnalyzeKey();
	void Update() ;
	CommandResult AnalyzeComm(std::string comment, CsvReader csv);
private:
	std::vector<std::string> actionList;

};


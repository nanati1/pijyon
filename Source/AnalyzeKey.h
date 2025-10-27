#pragma once
#include <iostream>
#include <string>
#include <vector>



class CsvReader;

struct CommandResult {
	std::vector<std::string> action;  // 検出された行動キーワード
	int badLevel = 0;                 // 最大の暴言レベル
	std::string finalAction;          // 優先度で決まる最終行動
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


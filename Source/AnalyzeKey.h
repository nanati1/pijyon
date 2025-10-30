#pragma once
#include <iostream>
#include <string>
#include <vector>



class CsvReader;

struct CommandResult {
	std::string action;  // 検出された行動キーワード
	int badLevel = 0;    // 最大の暴言レベル
};

struct CommandData
{
	std::string type;   // 種類（move, badなど）
	std::string word;   // 対応する単語"右, バカなど）
	int level = 0;      // 暴言レベル
	int priority = 0;   // 行動優先度
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
	int prevPri=0;// 優先度で決まる最終行動
};


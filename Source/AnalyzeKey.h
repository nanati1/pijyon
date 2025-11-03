#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Object2D.h"


class CsvReader;




struct CommandResult {
	std::string action;  // 検出された行動キーワード
	int badLevel = 0;    // 最大の暴言レベル
	int dir=1;			// 0:None,1:Right,2:Left
};

struct CommandData
{
	std::string type;   // 種類（move, badなど）
	std::string word;   // 対応する単語"右, バカなど）
	int level = 0;      // 暴言レベル
	int priority = 0;   // 行動優先度
	int dir = 1;		// 0:None,1:Right,2:Left
};


class AnalyzeKey:public  Object2D
{
public:
	
	AnalyzeKey();
	~AnalyzeKey();
	void Update() override;
	void Draw() override {};
	CommandResult AnalyzeComm(std::string comment);
	std::string GetAction() { return result.action; };
	int GetLevel() { return result.badLevel; };
	int GetDir() { return result.dir; };
private:
	std::vector<CommandData> commands;
	int prevPri=0;// 優先度で決まる最終行動
	CommandResult result;
};


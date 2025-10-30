#include "AnalyzeKey.h"
#include "DxLib.h"
#include "CsvReader.h"



AnalyzeKey::AnalyzeKey()
{
	CsvReader* csv=new CsvReader("data/map/KeyComment.csv");


	for (int i = 1; i < csv->GetLines(); i++)
	{
		CommandData cmd;
		cmd.word	 = csv->GetString(i,0);
		cmd.type	 = csv->GetString(i,1);
		cmd.level	 = csv->GetInt(i,2);
		cmd.priority = csv->GetInt(i,3);
		commands.push_back(cmd);
	}

}

AnalyzeKey::~AnalyzeKey()
{
}

void AnalyzeKey::Update()
{
}

CommandResult AnalyzeKey::AnalyzeComm(std::string comment )
{
	CommandResult result;
	result.action = nullptr;
	result.badLevel = 0;
	for (auto cmd : commands)
	{
		if (comment.find(cmd.word) != 0)
		{
			if (cmd.priority>prevPri)
			{
				result.action = cmd.type;
				prevPri = cmd.priority;
			}
			result.badLevel += cmd.level;
		}
	}

	return result;
}

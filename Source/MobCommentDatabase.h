#pragma once
#include<string>
#include<vector>

struct MobComment {
	std::string text;
	int weight;
};

class MobCommentDatabase
{
public:
	bool Load(const std::string& filename);
	std::string GetRandom()const;

private:
	std::vector<MobComment>list_;
};


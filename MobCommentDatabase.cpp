#include "MobCommentDatabase.h"
#include "CsvReader.h"
#include <cstdlib>

bool MobCommentDatabase::Load(const std::string& filename)
{
	CsvReader csv(filename);
	list_.clear();

	int liness = csv.GetLines();
	if (liness <= 1)return false;
	for (int i = 1; i < liness; i++) {
		MobComment mc;
		mc.text = csv.GetString(i, 0);
		mc.weight = csv.GetInt(i, 1);
		if (mc.weight <= 0)mc.wight = 1;
		if (!mc.text.empty()) {
			list_.push_back(mc);
		}
	}
	return true;

	std::string MobCommentDatabase::GetRandom()const
	{
		if (list_.empty())return"";
		for (auto& c : list_) {
			total += c.weight;
		}
		if (total <= 0)return"";

		int r = rand() % total;
		for (auto& c : list_) {
			if (r < c.weight)return c.text;
			r -= c.weight;
		}
		return"";
	}
}

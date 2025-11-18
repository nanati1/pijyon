#include "MobCommentDatabase.h"
#include "CsvReader.h"
#include <cstdlib>

bool MobCommentDatabase::Load(const std::string& filename)
{
    CsvReader csv(filename);

    list_.clear();

    int lines = csv.GetLines();
    if (lines <= 1) return false; // 0s–Ú‚Íƒwƒbƒ_

    for (int i = 1; i < lines; ++i) {
        MobComment mc;
        mc.text = csv.GetString(i, 0);   // Text
        mc.weight = csv.GetInt(i, 1);    // Weight
        if (mc.weight <= 0) mc.weight = 1;
        if (!mc.text.empty()) {
            list_.push_back(mc);
        }
    }
    return true;
}

std::string MobCommentDatabase::GetRandom() const
{
    if (list_.empty()) return "";

    int total = 0;
    for (auto& c : list_) {
        total += c.weight;
    }
    if (total <= 0) return "";

    int r = std::rand() % total;

    for (auto& c : list_) {
        if (r < c.weight) return c.text;
        r -= c.weight;
    }
    return "";
}

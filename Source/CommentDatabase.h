
#pragma once
#include <string>
#include "CommentSelect.h"  // enum’è‹`‚Ì‚½‚ß

class CommentDatabase {
public:
   // static std::string GetComment(CommentLevel level);
    static std::string GetComment(DirectionSelect dir);
    static std::string GetComment(DirectionSelect dir, StateSelect state,CommentLevel level);
};

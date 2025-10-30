#pragma once  
#include "Object2D.h"  
#include <string>

class AnalyzeKey;
class CommentOutput;

class KeyInput
:public  Object2D  
{  
public:  
KeyInput();  
~KeyInput();  
void Update() override;  
void Draw() override;  
bool GetKeyCheck() { return CheckKeyInput(InputHandle); }
std::string  GetComment() { return String; }

private:  
char String[256];  
int InputHandle;  
AnalyzeKey* AnK;
CommentOutput* comOut;
};

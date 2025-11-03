#pragma once  
#include "Object2D.h"  
#include <string>

class CommentOutput;

class KeyInput
:public  Object2D  
{  
public:  
KeyInput();  
~KeyInput();  
void Update() override;  
void Draw() override;  
int GetKeyCheck() { return keyCheck; }
std::string  GetComment() { return String; }

private:  
char String[256];  
int InputHandle;  
CommentOutput* comOut;
int keyCheck;
};

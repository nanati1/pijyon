#pragma once  
#include "Object2D.h"  
#include "AnalyzeKey.h" 
#include <string>

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
AnalyzeKey* Ana; // "Ana" �����o�[��ǉ�  
CsvReader* command; // command �������o�[�ϐ��Ƃ��Ēǉ�  
};

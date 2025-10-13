#pragma once
#include"../Library/GameObject.h"

class CommentOutput :
    public GameObject
{
public:
    void SetCommentText(const std::string& comment);   
    void Update()override;
    void Draw()override;

private:
    std::string currentComment_;
    int x_ = 1360;
	int y_ = 100;
	int vx_ = 2;
	int vy_ = 0;
};


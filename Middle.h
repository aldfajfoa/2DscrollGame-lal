#pragma once
#include "Engine/GameObject.h"

class Middle :
    public GameObject
{
public:
	Middle(GameObject* scene);
	~Middle();
	void Draw() override;
	void Release() override;
	void SetPosition(int x, int y) { transform_.position_.x = x;
	                                 transform_.position_.y = y;}
	//‰~‚Ì“–‚½‚è”»’è
	bool CollideCircle(float x, float y, float r);
private:
	int middle;
};


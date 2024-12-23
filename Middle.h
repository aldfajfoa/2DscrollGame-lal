#pragma once
#include "Engine/GameObject.h"

class Middle :public GameObject
{
public:
	Middle(GameObject* scene);
	~Middle();
	void Draw() override;
	void Release() override;

	void SetPosition(const int& x, const int& y) { transform_.position_.x = x;
	                                               transform_.position_.y = y;}
	//‰~‚Ì“–‚½‚è”»’è
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	int middle;
};


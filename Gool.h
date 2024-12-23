#pragma once
#include "Engine/GameObject.h"
#include "Field.h"
class Camera;

class Gool :public GameObject
{
public:
	Gool(GameObject* scene);
	~Gool();
	void Update() override;
	void Draw() override;
	int GetPositionX() { return transform_.position_.x; }

	//座標をセットする
	void SetPosition(const int& x, const int& y) {transform_.position_.x = x;
		                                          transform_.position_.y = y;}

	//円の当たり判定をする
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	Camera* cam;

	int counter;
	float baseY;//生成時のY座標

	int hImage;
};


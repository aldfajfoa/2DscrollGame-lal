#pragma once
#include "Engine/GameObject.h"

//////鳥（敵）//////////
class Enemy2: public GameObject 
{
public:
	Enemy2(GameObject* scene);
	~Enemy2();
	void Update() override;
	void Draw() override;

	//座標をセットする
	void SetPosition(const int& x, const int& y);

	//円の当たり判定
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	float baseY;//生成時のY座標
	int frameCounter;

	int animType; //状況
	int animFrame;//コマ
	int hImage;
};


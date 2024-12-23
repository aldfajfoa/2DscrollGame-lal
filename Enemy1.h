#pragma once
#include "Engine/GameObject.h"

//////亀（敵）//////////
class Enemy1 : public GameObject
{
public:
	Enemy1(GameObject* scene);
	~Enemy1();
	void Update() override;
	void Draw() override;

	//座標をセットする
	void SetPosition(const int& x, const int& y);

	//円の当たり判定
	bool CollideCircle(const float &x, const float &y, const float &r);

	//敵の向きを反転させる
	void ReverseEnemy();
private:

	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float baseY;//生成時のY座標
	int frameCounter;
	bool IsReverse;
	int tmpPosx, tmpPosy;

	int animType; //状況
	int animFrame;//コマ
	int hImage;
};

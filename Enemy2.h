#pragma once
#include "Engine/GameObject.h"

//////���i�G�j//////////
class Enemy2: public GameObject 
{
public:
	Enemy2(GameObject* scene);
	~Enemy2();
	void Update() override;
	void Draw() override;

	//���W���Z�b�g����
	void SetPosition(const int& x, const int& y);

	//�~�̓����蔻��
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	float baseY;//��������Y���W
	int frameCounter;

	int animType; //��
	int animFrame;//�R�}
	int hImage;
};


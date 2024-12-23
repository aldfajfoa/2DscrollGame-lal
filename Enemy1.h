#pragma once
#include "Engine/GameObject.h"

//////�T�i�G�j//////////
class Enemy1 : public GameObject
{
public:
	Enemy1(GameObject* scene);
	~Enemy1();
	void Update() override;
	void Draw() override;

	//���W���Z�b�g����
	void SetPosition(const int& x, const int& y);

	//�~�̓����蔻��
	bool CollideCircle(const float &x, const float &y, const float &r);

	//�G�̌����𔽓]������
	void ReverseEnemy();
private:

	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float baseY;//��������Y���W
	int frameCounter;
	bool IsReverse;
	int tmpPosx, tmpPosy;

	int animType; //��
	int animFrame;//�R�}
	int hImage;
};

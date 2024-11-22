#pragma once
#include "Engine/GameObject.h"

class Enemy1 : public GameObject
{
public:
	Enemy1(GameObject* scene);
	~Enemy1();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ���W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);

	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);

	void Reset();
	void ReverseEnemy();
private:
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	int hImage;
	float baseY;//��������Y���W
	int animType; //��
	int animFrame;//�R�}
	int frameCounter;
	bool IsReverse;
	int tmpPosx, tmpPosy;
};

#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���i�G�j
/// </summary>

class Enemy2
	: public GameObject 
{
public:
	Enemy2(GameObject* scene);
	~Enemy2();
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
};


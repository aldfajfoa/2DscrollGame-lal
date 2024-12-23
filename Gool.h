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

	//���W���Z�b�g����
	void SetPosition(const int& x, const int& y) {transform_.position_.x = x;
		                                          transform_.position_.y = y;}

	//�~�̓����蔻�������
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	Camera* cam;

	int counter;
	float baseY;//��������Y���W

	int hImage;
};


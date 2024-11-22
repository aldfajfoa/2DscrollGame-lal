#pragma once
#include "Engine/GameObject.h"
#include "Field.h"
class Camera;

class Gool :
    public GameObject
{
public:
	Gool(GameObject* scene);
	~Gool();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ���̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);

	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);

	void Reset();
private:
	//Field* field;
	Camera* cam;
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	int hImage;
	float baseY;//��������Y���W
};


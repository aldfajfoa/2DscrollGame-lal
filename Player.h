#pragma once
#include "Engine/GameObject.h"
class Camera;
class Field;
class LeverMaster;

////// �v���C���[ //////////
class Player : public GameObject
{
public:
    int count;

	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void Release() override;

	//���W���Z�b�g����
	void SetPosition(const int& x, const int& y) {transform_.position_.x = x;
		                                          transform_.position_.y = y;}
	void SetGround(const float &_ground) { Ground = _ground; }
	void Setp_speed(const float &speed) { p_speed = speed; }
	int GetPositionX() { return transform_.position_.x; }
	bool GetReversX() { return ReversX; }
	float GetMOVE_SPEED() { return MOVE_SPEED; }
	float GetMOVE_SPEED2() { return MOVE_SPEED2; }

	bool MovePlayer();
	void ControlCollision();
	bool CollideCircle(const float& x, const float& y, const float& r);

private:
	const float MOVE_SPEED = 2.0f;//�ʏ�X�s�[�h
	const float MOVE_SPEED2 = 6.0f;//�X�s�[�h�X�g�[������������̃X�s�[�h

	XINPUT_STATE input;
	GameObject* sceneTop;
	Camera* cam;
	Field* field;
	LeverMaster* lMas;

	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int frameCounter;
	float readyTimer;
	bool ReversX;
	int tmpPosx,tmpPosy;
	int ceiling;
	int Ground;
	bool firstGround;
	float p_speed;

	int animType; //��
	int animFrame;//�R�}
	int PlayerG;//�v���C���[�摜�̃n���h��
	int kazu;
	int StonesoundHandle;// �����̃n���h��
	int WalkHandle;//�������ʉ�
	int ClearSound;
};
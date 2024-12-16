#pragma once
#include "Engine/GameObject.h"
class Camera;
class Field;
class LeverMaster;

/// <summary>
/// �v���C���[�L����
/// </summary>
class Player : public GameObject
{
public:
    int count;

	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void Release() override;
	/// <summary>
	/// �v���C���[�̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);
	int GetPositionX() { return transform_.position_.x; }
	bool GetReversX() { return ReversX; }
	void ControlCollision();
	void SetGround(float _ground) { Ground = _ground; }
	bool MovePlayer();
	bool IsActive() { return isAlive; }//isAlive��true���ǂ���
	void DeActivateMe() { isAlive = false; }
	void ActivateMe() { isAlive = true; }
	void Setp_speed(float speed) { p_speed = speed; }
	float GetMOVE_SPEED() { return MOVE_SPEED; }
	float GetMOVE_SPEED2() { return MOVE_SPEED2; }
	bool CollideCircle(float x, float y, float r);

private:
	const float MOVE_SPEED = 2.0f;
	const float MOVE_SPEED2 = 6.0f;

	XINPUT_STATE input;
	GameObject* sceneTop;
	Camera* cam;
	Field* field;
	LeverMaster* lMas;

    int PlayerG;
	int kazu;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int animType; //��
	int animFrame;//�R�}
	int frameCounter;
	float readyTimer;
	bool ReversX;
	int tmpPosx,tmpPosy;
	int ceiling;
	int Ground;
	bool firstGround;
	bool isAlive;
	float p_speed;

	int StonesoundHandle;// �����̃n���h��
	int WalkHandle;//�������ʉ�
	int ClearSound;
};
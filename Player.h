#pragma once
#include "Engine/GameObject.h"
class Camera;
class Field;
class LeverMaster;

/// <summary>
/// プレイヤーキャラ
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
	/// プレイヤーの座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);
	int GetPositionX() { return transform_.position_.x; }
	bool GetReversX() { return ReversX; }
	void ControlCollision();
	void SetGround(float _ground) { Ground = _ground; }
	bool MovePlayer();
	bool IsActive() { return isAlive; }//isAliveがtrueかどうか
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
	int animType; //状況
	int animFrame;//コマ
	int frameCounter;
	float readyTimer;
	bool ReversX;
	int tmpPosx,tmpPosy;
	int ceiling;
	int Ground;
	bool firstGround;
	bool isAlive;
	float p_speed;

	int StonesoundHandle;// 音声のハンドル
	int WalkHandle;//歩く効果音
	int ClearSound;
};
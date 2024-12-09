#pragma once
#include "Engine/GameObject.h"
class Player;
class Field;

//ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
class Stone : public GameObject
{
public:
	Stone(GameObject* scene);
	~Stone();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
	void ControlCollision();//“–‚½‚è”»’è
	void Reset();

private:
	Player* pPlayer;
	Field* pField;
	int tmpPosx, tmpPosy;
	int StoneG;
	int timer;
	int ceiling;
	int Ground;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	bool colL, colR, colU, colD;
	bool IsReverse;
	float dir;
	float MoveSpeed;

	void SetMoveSpeed(float speed) { MoveSpeed = speed; }
	void WarpStone();
};
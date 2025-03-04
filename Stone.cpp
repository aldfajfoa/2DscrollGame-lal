#include "Stone.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"

namespace {
	const Size S_SIZE = { 20,19 };
	const float MOVE_SPEED = 3.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 2.0f;
	const float GRAVITY = 9.8f / 60.0f;
}

Stone::Stone(GameObject* scene) 
	: GameObject(scene),MoveSpeed(MOVE_SPEED)
{
	StoneG = LoadGraph("Assets/stone.png");
	assert(StoneG > 0);
	pPlayer = GetParent()->FindGameObject<Player>();
	IsReverse = true;
}

Stone::~Stone()
{
	if (StoneG > 0)
	{
		DeleteGraph(StoneG);
	}
}

void Stone::Update()
{
	tmpPosx = transform_.position_.x;
	tmpPosy = transform_.position_.y; 

	pField = GetParent()->FindGameObject<Field>();

	ControlCollision();

	jumpSpeed += GRAVITY;
	transform_.position_.y += jumpSpeed;


	if (--timer <= 0)
	{
		IsReverse = true;
		Release();
		KillMe();
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}

	WarpStone();//プレイヤーを石の位置に移動
}

void Stone::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawGraph(x-pField->Getscroll(), y, StoneG, TRUE);
}

void Stone::SetPosition(const XMFLOAT3& pos)
{
	transform_.position_ = pos;
	timer = 150;
}

void Stone::ControlCollision()
{
	int push = pField->CollisionRight(transform_.position_.x + 20, transform_.position_.y + 15);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x -= tmp % 32 / 10;
		colR = true;
	}
	else
	{
		colR = false;
	}

	push = pField->CollisionLeft(transform_.position_.x, transform_.position_.y + 15);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x += tmp % 32 / 16;
		colL = true;
	}
	else
	{
		colL = false;
	}

	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x, transform_.position_.y + 18);
		int pushL = pField->CollisionDown(transform_.position_.x + 18, transform_.position_.y + 18);
		int push = max(pushR, pushL);//２つの足元のめり込みの大きい方

		if (push > 1)
		{
			transform_.position_.y -= push;
			MoveSpeed = MOVE_SPEED;
			jumpSpeed = 0.0f;
			onGround = true;
			colD = true;
		}
		else
		{
			colD = false;
		}
	}

	if (onGround == false)
	{
		if (IsReverse) {
			if (pPlayer->GetReversX() == false)
			{
				dir = 1;
			}
			else if (pPlayer->GetReversX())
			{
				dir = -1;
			}
			IsReverse = false;
		}

		transform_.position_.x += MoveSpeed * dir;
		transform_.position_.y -= sqrtf(2 * GRAVITY * JUMP_HEIGHT);

		if (pField != nullptr)
		{
			int pushR = pField->CollisionDown(transform_.position_.x, transform_.position_.y + 18);
			int pushL = pField->CollisionDown(transform_.position_.x + 18, transform_.position_.y + 18);
			int push = max(pushR, pushL);//２つの足元のめり込みの大きい方

			if (push > 0)
			{
				transform_.position_.y += push;
				jumpSpeed = 0.0f;
				MoveSpeed = MOVE_SPEED;
				onGround = true;
				colD = true;
			}
			else
			{
				colD = false;
			}
		}
	}

	if (colL || colR || colU || colD)//当たったら速度を0にする 
	{
		MoveSpeed = 0;
	}
}

void Stone::Reset()
{
	KillMe();
}

void Stone::WarpStone()
{
	if (timer == 2)
	{
		int pushR = pField->CollisionRight(transform_.position_.x + 80, transform_.position_.y + 19);

		if (pushR > 1)
		{
			pPlayer->SetPosition(transform_.position_.x - 40, transform_.position_.y - 65);
		}
		else
		{
			pPlayer->SetPosition(transform_.position_.x-5, transform_.position_.y - 65);
		}
	}
}
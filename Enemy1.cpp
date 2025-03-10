#include "Enemy1.h"
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace 
{
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
	const Size E1_SIZE = { 64,64 };
};

Enemy1::Enemy1(GameObject* scene):counter(0), animType(0), animFrame(0), frameCounter(0), IsReverse(false)
{
	hImage = LoadGraph("Assets/mob2.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}

Enemy1::~Enemy1()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Enemy1::Update()
{
	tmpPosx = transform_.position_.x;
	tmpPosy = transform_.position_.y;

	Field* pField = GetParent()->FindGameObject<Field>();
	counter -= 1;

	if (counter <= 0)
	{
		counter = 5;
		if (++frameCounter >= 9)
		{
			animFrame = (animFrame + 1) % 2;
			frameCounter = 0;
		}
	}

	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 60);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 60);
		int push = max(pushR, pushL);//２つの足元のめり込みの大きい方
		if (push >= 1)
		{
			transform_.position_.y -= push - 1;
			jumpSpeed = 0.0f;
			onGround = true;
		}
		else
		{
			onGround = false;
		}
	}

	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	if (x > WIN_WIDTH)
		return;
	else if (x < 0 - E1_SIZE.w) 
	{
		KillMe();
		return;
	}

	if (IsReverse) {
		transform_.position_.x += 0.4f;
	}
	else {
		transform_.position_.x -= 0.4f;
	}
	jumpSpeed += GRAVITY;//速度 += 加速度
	transform_.position_.y += jumpSpeed; //座標 += 速度

	ReverseEnemy();

	if (transform_.position_.y >= 700)
	{
		KillMe();
	}

	if (counter == 0)
	{
		counter = 160;
	}
}

void Enemy1::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Field* field = GetParent()->FindGameObject<Field>();
	DrawRectGraph(x-field->Getscroll(), y, 0, animFrame * E1_SIZE.h, E1_SIZE.w, E1_SIZE.h, hImage, TRUE, IsReverse);
}

bool Enemy1::CollideCircle(const float& x, const float& y, const float& r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Enemy1::ReverseEnemy()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	int push = pField->CollisionRight(transform_.position_.x + E1_SIZE.w, transform_.position_.y + 50);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x -= tmp % 32 / 10;
		IsReverse = false;
	}

	push = pField->CollisionLeft(transform_.position_.x, transform_.position_.y + 50);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x += tmp % 32 / 10;
		IsReverse = true;
	}
}

void Enemy1::SetPosition(const int& x, const int& y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	baseY = x;
}
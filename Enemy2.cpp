#include "Enemy2.h"
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace {
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
	const Size E2_SIZE = { 64,64 };
};

Enemy2::Enemy2(GameObject* scene):counter(0), animType(0), animFrame(0), frameCounter(0)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}

Enemy2::~Enemy2()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Enemy2::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	counter -= 1;

	if (++frameCounter >= 9)
	{
		animFrame = (animFrame + 1) % 3;
		frameCounter = 0;
	}

	if (pField != nullptr)
	{
		//(50,64)と(14,64)も見る
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 64);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 64);
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

	if (x > WIN_WIDTH) //即値、マジックナンバー
		return;
	else if (x < 0 - E2_SIZE.w)
	{
		KillMe();
		return;
	}

	sinAngle += 1.0f;//度
	float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
	transform_.position_.y = baseY + sinValue * 150;

	if (transform_.position_.y >= 700)
	{
		KillMe();
	}

	if (counter == 0)
	{
		counter = 160;
	}
}

void Enemy2::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Field* field = GetParent()->FindGameObject<Field>();
	DrawRectGraph(x-field->Getscroll(), y, 0, animFrame * E2_SIZE.h, E2_SIZE.w, E2_SIZE.h, hImage, TRUE);
}

void Enemy2::SetPosition(const int& x, const int& y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	baseY = y;
}

bool Enemy2::CollideCircle(const float& x, const float& y, const float& r)
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
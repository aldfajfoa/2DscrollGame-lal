#include "SpeedStone.h"
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"
#include "Player.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
	static float t = 0;
}

SpeedStone::SpeedStone()
{
	SpeedStoneG = LoadGraph("Assets/houseki.png");
	assert(SpeedStoneG > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 650.0f;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	counter = 0;
	isAlive = true;
}

SpeedStone::SpeedStone(GameObject parent)
{
	SpeedStoneG = LoadGraph("Assets/houseki.png");
	assert(SpeedStoneG > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 650.0f;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	counter = 0;
	isAlive = true;
}

SpeedStone::~SpeedStone()
{
	if (SpeedStoneG > 0)
	{
		DeleteGraph(SpeedStoneG);
	}
}

void SpeedStone::Initialize()
{
	p = GetParent()->FindGameObject<Player>();
}

void SpeedStone::Update()
{
	counter -= 1;
	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	if (counter <= 0)
	{
		counter = 3;
		if (++frameCounter >= 10)
		{
			animFrame = (animFrame + 1) % 3;
			frameCounter = 0;
		}
	}

	if (x > SCREEN_WIDTH) //���l�A�}�W�b�N�i���o�[
		return;
	else if (x < 0 - 64)
	{
		KillMe();
		return;
	}


	if (counter == 0)
	{
		counter = 160;
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}

	if (isAlive == false)
	{
		KillStone();
	}
}

void SpeedStone::Draw()
{
	if (IsAlive())
	{
		int x = (int)transform_.position_.x;
		int y = (int)transform_.position_.y;
		Camera* cam = GetParent()->FindGameObject<Camera>();
		if (cam != nullptr) {
			x -= cam->GetValue();
		}

		DrawRectGraph(x, y, animFrame * 48, 48, 48, 40, SpeedStoneG, TRUE, IsReverse);
	}
}

void SpeedStone::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool SpeedStone::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void SpeedStone::Reset()
{
	KillMe();
}

void SpeedStone::KillStone()
{
	if (t <= 100)
	{
		p->Setp_speed(p->GetMOVE_SPEED2());
		t++;
	}
	else
	{
		p->Setp_speed(p->GetMOVE_SPEED());
		KillMe();
		t = 0;
		Release();
	}
}

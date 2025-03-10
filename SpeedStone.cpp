#include "SpeedStone.h"
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"
#include "Player.h"

namespace
{
	static float t = 0;
}

SpeedStone::SpeedStone(GameObject* parent) :counter(0), animType(0), animFrame(0), frameCounter(0), isAlive(true)
{
	SpeedStoneG = LoadGraph("Assets/houseki.png");
	assert(SpeedStoneG > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 650.0f;
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

	if (counter <= 0)
	{
		counter = 3;
		if (++frameCounter >= 10)
		{
			animFrame = (animFrame + 1) % 3;
			frameCounter = 0;
		}
	}

	if (x > WIN_WIDTH) //即値、マジックナンバー
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

bool SpeedStone::CollideCircle(const float& x, const float& y, const float& r)
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

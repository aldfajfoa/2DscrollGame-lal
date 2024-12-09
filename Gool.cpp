#include "Gool.h"
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace
{
	const Size G_SIZE = {128,256};
}

Gool::Gool(GameObject* scene)
{
	hImage = LoadGraph("Assets/hata.png");
	assert(hImage > 0);
	counter = 0;
}

Gool::~Gool()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Gool::Update()
{
	int x = (int)transform_.position_.x;

	if (x > WIN_WIDTH) //即値、マジックナンバー
		return;
	else if (x < 0 -G_SIZE.w)
	{
		KillMe();
		return;
	}

	if (transform_.position_.y >= WIN_HEIGHT)
	{
		KillMe();
	}

	if (counter == 0)
	{
		counter = 160;
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}
}

void Gool::Draw()
{
	Field* field = GetParent()->FindGameObject<Field>();

	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	
	DrawGraph(x-field->Getscroll(), y, hImage, TRUE);
}

void Gool::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Gool::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 100.0f;
	float myCenterY = transform_.position_.y + 100.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Gool::Reset()
{
	KillMe();
}

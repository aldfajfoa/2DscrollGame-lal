#include "Middle.h"
#include "Field.h"

Middle::Middle(GameObject* scene)
	:GameObject(scene, "Middle")
{
	middle = LoadGraph("Assets/bird.png");
	assert(middle > 0);
}

Middle::~Middle()
{
	DeleteGraph(middle);
	Release();
}

void Middle::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Field* field = GetParent()->FindGameObject<Field>();
	DrawGraph(x - field->Getscroll(), y, middle, TRUE);
}

void Middle::Release()
{
}

bool Middle::CollideCircle(float x, float y, float r)
{
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
	//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

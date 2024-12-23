#include "LeverMaster.h"
#include "Lever.h"
#include "LeverBrock.h"
#include "Camera.h"

LeverMaster::LeverMaster(GameObject* scene)
	:GameObject(scene, "LeverMaster")
{
	for (int i = 0; i < LEVER_NUM; i++)
	{
		Lever* le = Instantiate<Lever>(this);
		Levers[i] = le;
	}
}

LeverMaster::~LeverMaster()
{
	lBrocks.clear();
	Release();
}

void LeverMaster::Update()
{
	cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
}

void LeverMaster::Release(){}

void LeverMaster::SetLeverPos(const int& num, const int& x, const int& y)
{
	Levers[num - 600]->SetPosition(x, y);
	Levers[num - 600]->SetLeverID(num - 600);
}

void LeverMaster::birthLeverBrock(const int& x, const int& y, const int& ID)
{
	LeverBrock* l = Instantiate<LeverBrock>(GetParent());
	l->SetPosition(x, y);
	l->SetLeverBrockID(ID);
	lBrocks.push_back(l);
}

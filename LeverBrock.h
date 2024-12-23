#pragma once
#include "Engine/GameObject.h"
class Field;
class LeverMaster;

class LeverBrock :
    public GameObject
{
	Field* fi;
	LeverMaster* lMas;

	int LeverBrockID;
	int Lscroll;
	int hImage;
public:
	LeverBrock(GameObject* scene);
	~LeverBrock();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetPosition(const int &x, const int &y) { transform_.position_.x = x;
	                                               transform_.position_.y = y;}
	void SetLeverBrockID(const int &ID) { LeverBrockID = ID; }
	int GetLeverBrockID() { return LeverBrockID; }
};


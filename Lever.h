#pragma once
#include "Engine/GameObject.h"
class Player;
class LeverMaster;
class LeverBrock;
class Field;

class Lever :public GameObject
{
	Player* p;
	Field* fi;
	LeverMaster* lMas;

	bool ReversX;
	int Lscroll;
	int LeverID;

	int hImage;
	int soundHandle;//�����̃n���h��
public:
	Lever(GameObject* scene);
	~Lever();
	void Update()override;
	void Draw()override;
	void Release()override;

	void SetPosition(const int& x, const int& y);//���W���Z�b�g����
	void SetLeverID(const int &ID) { LeverID = ID; }
	void ReversXfalse() { ReversX =false; }
	void DestroyLBrock();
};


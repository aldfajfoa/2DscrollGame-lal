#pragma once
#include "Engine/GameObject.h"
#include <vector>
using std::vector;
class Lever;
class LeverBrock;
class Camera;
const int LEVER_NUM = 5;

class LeverMaster :
    public GameObject
{
	Camera* cam;
	Lever* Levers[LEVER_NUM];
	vector<LeverBrock*> lBrocks;
public:
	LeverMaster(GameObject* scene);
	~LeverMaster();
	void Update() override;
	void Draw() override;
	void Release() override;
	void SetLeverPos(int num, int x, int y);
	Camera* Getcam() { return cam; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="ID">�u���b�N��ID</param>
	void birthLeverBrock(int x,int y,int ID);
	vector<LeverBrock*> GetlBrocks() { return lBrocks; }
};


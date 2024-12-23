#pragma once
#include "Engine/GameObject.h"
#include <vector>
using std::vector;
class Lever;
class LeverBrock;
class Camera;
const int LEVER_NUM = 5;

class LeverMaster :public GameObject
{
	Camera* cam;
	Lever* Levers[LEVER_NUM];
	vector<LeverBrock*> lBrocks;
public:
	LeverMaster(GameObject* scene);
	~LeverMaster();
	void Update() override;
	void Release() override;

	void SetLeverPos(const int &num, const int &x, const int &y);

	/// <summary>
	/// レバーブロックを生成
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="ID">ブロックのID</param>
	void birthLeverBrock(const int &x,const int &y,const int &ID);

	Camera* Getcam() { return cam; }
	vector<LeverBrock*> GetlBrocks() { return lBrocks; }
};


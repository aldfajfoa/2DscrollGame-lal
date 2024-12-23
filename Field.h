#pragma once
#include "Engine/GameObject.h"
class Camera;
class Player;
class SceneManager;

////// 地面（プレイフィールド）//////////
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// 右側の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めりこんだ量(ドット)</returns>
	int CollisionRight(int x, int y);

	/// <summary>
	/// 左側の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量(ドット)</returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// 下の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量(ドット)</returns>
	int CollisionDown(int x, int y);

	/// <summary>
	/// 上の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns></returns>
	int CollisionUp(int x, int y);

	void IsScroll();
	void SetScroll(int scroll_) { scroll = scroll_; }
	int Getscroll() { return scroll; }
	bool GetLeftSc() { return LeftSc; }
	bool GetRightSc() { return RightSc; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void ChangeChip(const int &x, const int &y, const int &changeNum);

private:
	const int CH_SIZE = 32;//マップチップサイズ

	Camera* cam;
	Player* pplayer;
	SceneManager* SM;

	int hImage;
	int background;
	int stone;
	int controll;

	int* Map;
	float middlePosX, middlePosY;
	int Backnum;//背景の枚数
	int width, height;
	int scroll;
	bool LeftSc, RightSc;

	bool IsWallBlock(const int& x, const int& y);
};

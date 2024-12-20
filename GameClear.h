#pragma once
#include "Engine/GameObject.h"
class GameClear :
    public GameObject
{
private:
	int clear;
	XINPUT_STATE input;
	int count;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameClear(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
};
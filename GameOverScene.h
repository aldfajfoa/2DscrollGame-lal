#pragma once
#include "Engine/GameObject.h"
class GameOverScene :
    public GameObject
{
	int count;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int over;
	int s;
	int q;
	int counter;
	XINPUT_STATE input;
};


#pragma once
#include "Engine/GameObject.h"
class GameOverScene :
    public GameObject
{
private:
	int count;
	int over;
	int counter;
	XINPUT_STATE input;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
};


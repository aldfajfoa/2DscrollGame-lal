#pragma once
#include "Engine/GameObject.h"
class TitleScene :
    public GameObject
{
private:
	int count;
	int title;
	XINPUT_STATE input;
public:
	//コンストラクタ
    //引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
};


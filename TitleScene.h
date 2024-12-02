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
	//�R���X�g���N�^
    //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
};


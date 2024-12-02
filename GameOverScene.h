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
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameOverScene(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
};


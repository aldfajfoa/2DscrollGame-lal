#pragma once
#include "Engine/GameObject.h"
class GameOverScene :
    public GameObject
{
	int count;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
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


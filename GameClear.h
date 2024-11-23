#pragma once
#include "Engine/GameObject.h"
class GameClear :
    public GameObject
{
	int count;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameClear(GameObject* parent);
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int clear;
	XINPUT_STATE input;
};
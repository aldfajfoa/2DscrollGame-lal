#include "TestScene.h"
#include "Player.h"
#include "Enemy1.h"
#include "Field.h"
#include "Camera.h"
#include "Banner.h"
#include "LeverMaster.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), isSoundPlaying(false), soundHandle(-1)
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	pField = Instantiate<Field>(this);
	Instantiate<LeverMaster>(this);
	Instantiate<Player>(this);
	pField->Reset();
	Instantiate<Banner>(this);

	soundHandle = LoadSoundMem("Assets/Dream_diffuser.mp3");
	PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	isSoundPlaying = true;

	StartReady();
}

//�X�V
void TestScene::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	switch (state) {
	case S_Ready:UpdateReady(); break;
	case S_Play:UpdatePlay(); break;
	case S_Clear: UpdateClear(); break;
	case S_Dead: UpdateDead(); break;
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
	StopSoundMem(soundHandle);
	DeleteSoundMem(soundHandle);
	soundHandle = -1;
	isSoundPlaying = false;
}

bool TestScene::CanMove()
{
	return (state == S_Play);
}

void TestScene::StartReady()
{
	readyTimer = 1.5f;
	state = S_Ready;
}

void TestScene::UpdateReady()
{
	readyTimer -= 1.0f / 60.0f;
	if (readyTimer <= 0.0f) 
	{
		StartPlay();
	}
}

void TestScene::StartPlay()
{
	state = S_Play;
	//Banner* bn = FindGameObject<Banner>();
	//bn->View(Banner::ViewID::V_Nothing);
}

void TestScene::UpdatePlay()
{
}

void TestScene::UpdateClear()
{
}

void TestScene::StartDead()
{
	readyTimer = 1.5f;
	state = S_Dead;
}

void TestScene::UpdateDead()
{
	readyTimer -= 1.0f / 60.0f;
	if (readyTimer <= 0.0f)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Release();
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

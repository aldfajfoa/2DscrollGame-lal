#include "TestScene.h"
#include "Player.h"
#include "Enemy1.h"
#include "Field.h"
#include "Camera.h"
#include "LeverMaster.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), isSoundPlaying(false), soundHandle(-1)
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Camera>(this);
	pField = Instantiate<Field>(this);
	Instantiate<LeverMaster>(this);
	Instantiate<Player>(this);
	pField->Reset();

	soundHandle = LoadSoundMem("Assets/Dream_diffuser.mp3");
	PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	isSoundPlaying = true;

	OverSound = LoadSoundMem("Assets/over.mp3");

	readyTimer = 1.5f;
	state = S_Ready;
}

//更新
void TestScene::Update()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	switch (state) {
	case S_Ready:UpdateReady(); break;
	case S_Dead: UpdateDead(); break;
	}
}

//開放
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
		PlaySoundMem(OverSound, DX_PLAYTYPE_BACK);
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Release();
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

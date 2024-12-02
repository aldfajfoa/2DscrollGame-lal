#include "GameOverScene.h"
#include "Engine/SceneManager.h"

GameOverScene::GameOverScene(GameObject* parent)
	:count(50)
{
	over = LoadGraph("Assets/GAMEOVER_ .png");
	counter = 0;
}

void GameOverScene::Update()
{
	count -= 1;

	// “ü—Íó‘Ô‚ðŽæ“¾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (CheckHitKey(KEY_INPUT_Q))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Release();
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Release();
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
	if (input.Buttons[XINPUT_BUTTON_START] == 1)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Release();
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}

	if (input.Buttons[XINPUT_BUTTON_BACK] == 1)
	{
		if (count <= 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			Release();
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, over, TRUE);
}

void GameOverScene::Release()
{
	if (over > 0)
	{
		DeleteGraph(over);
	}
}

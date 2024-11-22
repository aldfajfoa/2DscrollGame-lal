#include "GameClear.h"
#include "Engine/SceneManager.h"

GameClear::GameClear(GameObject* parent)
	:count(50)
{
	clear = LoadGraph("Assets/Clear.png");
	mori = LoadGraph("Assets/mori1.jpg");
	SpaceButton = LoadGraph("Assets/s.png");
	EscButton = LoadGraph("Assets/e.png");
}

void GameClear::Update()
{
	count -= 1;
	// “ü—Íó‘Ô‚ðŽæ“¾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (CheckHitKey(KEY_INPUT_E))
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

void GameClear::Draw()
{
	DrawGraph(0, 0, mori, TRUE);
	DrawGraph(150, 200, clear, TRUE);
	DrawGraph(150, 400, SpaceButton, TRUE);
	DrawGraph(260, 500, EscButton, TRUE);
}

void GameClear::Release()
{
}

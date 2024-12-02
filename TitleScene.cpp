#include "TitleScene.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene"), count(20)
{
	title = LoadGraph("Assets/Title1.png");
}

void TitleScene::Update()
{
	count -= 1;
	// “ü—Íó‘Ô‚ðŽæ“¾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

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

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		exit(0);
	}
	
	
	if (input.Buttons[XINPUT_BUTTON_BACK])
	{
		if (count <= 0)
		{
			exit(0);
		}
	}
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, title, TRUE);
}

void TitleScene::Release()
{
	DeleteGraph(title);
}

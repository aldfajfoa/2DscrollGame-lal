#pragma once
#include "global.h"
#include "GameObject.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_TITLE = 0,
	SCENE_ID_TEST,
	SCENE_ID_GAMEOVER,
	SCENE_ID_GAMECLEAR
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

	void SetisMiddle(bool is) { isMiddle = is; }
	bool GetisMiddle() { return isMiddle; }
private:
	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン

	bool isMiddle;//中間にスポーンするかどうか
};
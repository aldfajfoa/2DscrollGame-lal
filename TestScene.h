#pragma once
#include "Engine/GameObject.h"
#include <DxLib.h> //DxLibの機能を利用する場合
class Field;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Release() override;

	bool CanMove();
	void StartDead();
private:
	Field* pField;
	enum State {
	    S_Ready,//Ready表示中(2秒間すたーとを表示)
	    S_Play, //ゲーム中
		S_Dead, //死亡(ゲームオーバーを表示してボタンが押されるまで待つ)
	};
	State state;         // 現在のステート
	float readyTimer;    // Ready 表示のタイマー
	bool isSoundPlaying; // 音声再生中かを確認するフラグ
	int soundHandle;     // 音声のハンドル
	int OverSound;       //ゲームオーバーのハンドル

	XINPUT_STATE input;   // コントローラーの入力状態

	// ステートの切り替えと更新処理
	void UpdateReady();
	void StartPlay();
	void UpdateDead();
};
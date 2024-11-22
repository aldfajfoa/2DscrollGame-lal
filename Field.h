#pragma once
#include "Engine/GameObject.h"
class Camera;

/// <summary>
/// �n�ʁi�v���C�t�B�[���h�j
/// </summary>
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// �E���̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns>�߂肱�񂾗�(�h�b�g)</returns>
	int CollisionRight(int x, int y);

	/// <summary>
	/// �����̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns>�߂荞�񂾗�(�h�b�g)</returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// ���̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns>�߂荞�񂾗�(�h�b�g)</returns>
	int CollisionDown(int x, int y);

	/// <summary>
	/// ��̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns></returns>
	int CollisionUp(int x, int y);

	void IsScroll();
	bool GetLeftSc() { return LeftSc; }
	bool GetRightSc() { return RightSc; }
	bool IsCollisionRight(int i);
	bool IsCollisionLeft(int i);
	bool IsCollisionUp(int i);
	bool IsCollisionDown(int i);

	bool EnemyCollisionRight(int i);
	bool EnemyCollisionLeft(int i);
	void SetScroll(int scroll_) { scroll = scroll_; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int Getscroll() { return scroll; }
	void ChangeChip(int x, int y, int changeNum);
private:
	const int CH_SIZE = 32;//�}�b�v�`�b�v�T�C�Y
	Camera* cam;
	int hImage;
	int background;
	int stone;

	bool IsWallBlock(int x, int y);
	int* Map;
	int Backnum;//�w�i�̖���
	int width;
	int height;
	int sousa;
	//int controll;
	int scroll;
	bool LeftSc, RightSc;
};
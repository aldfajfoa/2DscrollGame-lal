#pragma once
#include "Engine/GameObject.h"
#include <DxLib.h> // DxLib�̋@�\�𗘗p����ꍇ
class Field;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool CanMove();
	void StartDead();
private:
	Field* pField;
	enum State {
	    S_Ready, //Ready�\����(2�b�Ԃ����[�Ƃ�\��)
	    S_Play, //�Q�[����
		S_Clear, //�Q�[���N���A(�N���A��\�����ă{�^�����������܂ő҂�)
		S_Dead, //���S(�Q�[���I�[�o�[��\�����ă{�^�����������܂ő҂�)
	};
	State state;          // ���݂̃X�e�[�g
	float readyTimer;     // Ready �\���̃^�C�}�[
	bool isSoundPlaying;  // �����Đ��������m�F����t���O
	int soundHandle;      // �����̃n���h��

	XINPUT_STATE input;   // �R���g���[���[�̓��͏��

	// �X�e�[�g�̐؂�ւ��ƍX�V����
	void StartReady();
	void UpdateReady();
	void StartPlay();
	void UpdatePlay();
	void UpdateClear();
	void UpdateDead();
};
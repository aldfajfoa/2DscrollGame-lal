#pragma once
#include "Engine/GameObject.h"
#include <DxLib.h> //DxLib�̋@�\�𗘗p����ꍇ
class Field;

//�e�X�g�V�[�����Ǘ�����N���X
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
	    S_Ready,//Ready�\����(2�b�Ԃ����[�Ƃ�\��)
	    S_Play, //�Q�[����
		S_Dead, //���S(�Q�[���I�[�o�[��\�����ă{�^�����������܂ő҂�)
	};
	State state;         // ���݂̃X�e�[�g
	float readyTimer;    // Ready �\���̃^�C�}�[
	bool isSoundPlaying; // �����Đ��������m�F����t���O
	int soundHandle;     // �����̃n���h��
	int OverSound;       //�Q�[���I�[�o�[�̃n���h��

	XINPUT_STATE input;   // �R���g���[���[�̓��͏��

	// �X�e�[�g�̐؂�ւ��ƍX�V����
	void UpdateReady();
	void StartPlay();
	void UpdateDead();
};
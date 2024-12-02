#include "Engine/SceneManager.h"
#include "Player.h"
#include "Stone.h"
#include "Camera.h"
#include "Field.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Gool.h"
#include "SpeedStone.h"
#include "TestScene.h"
#include "LeverMaster.h"
#include "Middle.h"

namespace {
	const Size P_SIZE = { 80,88 };
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;//�W�����v�̍���
	const float GRAVITY = 9.8f / 60.0f;//�d�͉����x
	const int MAX_STONE = 20; //���΂𓊂����ő吔
	float STONE_NUMBER = 940;
}


Player::Player(GameObject* parent) 
	: GameObject(sceneTop), cam(nullptr), field(nullptr), lMas(nullptr), 
	  counter(0), count(0), rcount(0), firstGround(true)
{
	PlayerG = LoadGraph("Assets/player2.png");
	kazu = LoadGraph("Assets/suji.png");
	assert(PlayerG > 0);
	transform_.position_.x = 10.0f;
	transform_.position_.y = GROUND;
	jumpSpeed = 0.0f;
	onGround = true;
	isAlive = true;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	state = S_Walk;
	transparency = 0;
	readyTimer = 1.5f;
	p_speed = MOVE_SPEED;
	StonesoundHandle = LoadSoundMem("Assets/�Γ�����.mp3");
	StoneLine = LoadGraph("Assets/Yosokusen.png");
	WalkHandle = LoadSoundMem("Assets/WalkSound.mp3");
	WalkFlag = false;
	ClearSound = LoadSoundMem("Assets/Clear.mp3");
	Reset();
}


Player::~Player()
{
	if (PlayerG > 0)
	{
		DeleteGraph(PlayerG);
	}
}


void Player::Update()
{
	//���͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	tmpPosx = transform_.position_.x;
	tmpPosy = transform_.position_.y;

	field = GetParent()->FindGameObject<Field>();
	Stone* st = Instantiate<Stone>(GetParent());
	lMas = GetParent()->FindGameObject<LeverMaster>();

	counter -= 1;

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
	{
		return;
	}

	if (MovePlayer())
	{
		if (++frameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 3;
			frameCounter = 0;
		}
	}
	else
	{
		animFrame = 0;
		frameCounter = 0;
	}

	jumpSpeed += GRAVITY;//���x += �����x
	transform_.position_.y += jumpSpeed; //���W += ���x

	ControlCollision();

	if (transform_.position_.y > Ground) {
		transform_.position_.y = Ground;
		jumpSpeed = 0.0f;
	}

	//�΂𓊂���
	if (count == MAX_STONE)
	{
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_O))
		{
			if (counter <= 0)
			{
				PlaySoundMem(StonesoundHandle, DX_PLAYTYPE_BACK);
				counter = 160;
				if (counter == 160)
				{
					count += 1;
					STONE_NUMBER -= 47;
				}
				st->SetPosition(transform_.position_);
			}
		}
		if (input.Buttons[XINPUT_BUTTON_B] == 1)
		{
			if (counter <= 0)
			{
				PlaySoundMem(StonesoundHandle, DX_PLAYTYPE_BACK);
				counter = 160;
				if (counter == 160)
				{
					count += 1;
					STONE_NUMBER -= 47;
				}
				st->SetPosition(transform_.position_);
			}
		}
	}

	//�G1�̓����蔻��
	std::list<Enemy1*> pBirds = GetParent()->FindGameObjects<Enemy1>();
	for (Enemy1* pBird : pBirds)
	{
		if (pBird->CollideCircle(transform_.position_.x + (P_SIZE.w / 2), transform_.position_.y + (P_SIZE.h / 2), 20.0f))
		{
			animType = 4;
			animFrame = 0;
			scene->StartDead();
		}
	}

	//�G2�̓����蔻��
	std::list<Enemy2*> pLivingthings = GetParent()->FindGameObjects<Enemy2>();
	for (Enemy2* pLivingthing : pLivingthings)
	{
		if (pLivingthing->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f))
		{
			animType = 4;
			animFrame = 0;
			scene->StartDead();
		}
	}

	//���Ԓn�_�̓����蔻��
	std::list<Middle*> pMiddle = GetParent()->FindGameObjects<Middle>();
	for (Middle* pMiddle : pMiddle)
	{
		if (pMiddle->CollideCircle(transform_.position_.x + (P_SIZE.w / 2), transform_.position_.y + (P_SIZE.h / 2), 20.0f))
		{
			SceneManager* pScene = (SceneManager*)GetParent()->GetParent();
			pScene->SetisMiddle(true);
		}
	}

	//�S�[���̓����蔻��
	std::list<Gool*> pGools = GetParent()->FindGameObjects<Gool>();
	for (Gool* pGool : pGools)
	{
		if (pGool->CollideCircle(transform_.position_.x + (P_SIZE.w / 2), transform_.position_.y + (P_SIZE.h / 2), 110.0f))
		{
			animType = 4;
			animFrame = 0;

			readyTimer -= 1.0f / 60.0f;
			if (readyTimer <= 0.0f)
			{
				SceneManager* pScene = (SceneManager*)GetParent()->GetParent();
				pScene->SetisMiddle(false);
				PlaySoundMem(ClearSound, DX_PLAYTYPE_BACK);
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
			}
		}
	}

	//�X�s�[�h�X�g�[���̓����蔻��
	std::list<SpeedStone*> pSs = GetParent()->FindGameObjects<SpeedStone>();
	for (SpeedStone* pSs : pSs)
	{
		if (pSs->CollideCircle(transform_.position_.x + (P_SIZE.w / 2), transform_.position_.y + (P_SIZE.h / 2), 20.0f))
		{
			animType = 4;
			animFrame = 0;
			pSs->DeActivateMe();
			this->DeActivateMe();
		}
	}

	//�����ŃJ�����ʒu�̒���
	cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	
	if (field->GetRightSc()) {
		if (x > 600) {
			x = 600;
			cam->SetValue((int)transform_.position_.x - x);
		}
	}
	if (field->GetLeftSc()) {
		if (x < 500) {
			x = 500;
			cam->SetValue((int)transform_.position_.x - x);
		}
	}

	//����������
	if (transform_.position_.y >= 700)
	{
		scene->StartDead();
		KillMe();
	}

	//���Z�b�g
	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency + 500);
	}

	if (transform_.position_.x <= 0)
	{
		transform_.position_.x = 0;
	}

	if (transform_.position_.x >= field->GetWidth()*32)
	{
		transform_.position_.x = field->GetWidth() * 32;
	}
}

void Player::Draw()
{
	DrawRectGraph(145, -10, 0, STONE_NUMBER, 92, 64, kazu, TRUE);

	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x - field->Getscroll(), y, animFrame * P_SIZE.w, P_SIZE.h * 2, 80, 88, PlayerG, TRUE, ReversX);
}

void Player::Release()
{
}

//�v���C���[�̃|�W�V����
void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Player::Reset()
{
	count = 0;
	STONE_NUMBER = 940;
	DrawRectGraph(170, 0, 0, STONE_NUMBER, 64, 64, kazu, TRUE);
}

void Player::ControlCollision()
{
	Field* map = GetParent()->FindGameObject<Field>();

	int push = map->CollisionRight(transform_.position_.x + P_SIZE.w-10, transform_.position_.y + 80);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x -= tmp % 32 / 10;
	}

	push = map->CollisionLeft(transform_.position_.x+10, transform_.position_.y + 80);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x += tmp % 32 / 10;
	}

    push = map->CollisionUp(transform_.position_.x + P_SIZE.w/2, transform_.position_.y);

	if (push > 1)
	{
		int tmp = transform_.position_.x;
		transform_.position_.x -= tmp % 32 / 10;
		ceiling = tmpPosy;
	}
	else {
		ceiling = 0;
	}

	if (map != nullptr)
	{
		if (firstGround) {
			Ground -= 20;
			firstGround = false;
		}
		else {
			int pushR = map->CollisionDown(transform_.position_.x + 60, transform_.position_.y + 85);
			int pushL = map->CollisionDown(transform_.position_.x + 25, transform_.position_.y + 85);
			int push = max(pushR, pushL);//�Q�̑����̂߂荞�݂̑傫����
			if (push >= 1)
			{
				transform_.position_.y -= push - 1;
				jumpSpeed = 0.0f;
				onGround = true;
			}
			else
			{
				Ground = 1000;
				onGround = false;
			}
		}
	}
}

bool Player::MovePlayer()
{
	// �O�i
	if (CheckHitKey(KEY_INPUT_D))
	{
		// ���ʉ����Đ����łȂ��ꍇ�̂ݍĐ�
		if (CheckSoundMem(WalkHandle) == 0)
		{
			PlaySoundMem(WalkHandle, DX_PLAYTYPE_BACK);
		}
		ReversX = false;
		transform_.position_.x += p_speed;
		return true;
	}
	// ���
	else if (CheckHitKey(KEY_INPUT_A))
	{
		// ���ʉ����Đ����łȂ��ꍇ�̂ݍĐ�
		if (CheckSoundMem(WalkHandle) == 0)
		{
			PlaySoundMem(WalkHandle, DX_PLAYTYPE_BACK);
		}
		ReversX = true;
		transform_.position_.x -= p_speed;
		return true;
	}

	// �W���C�p�b�h�̓��͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (input.ThumbLX >= 10000)
	{
		if (CheckSoundMem(WalkHandle) == 0)
		{
			PlaySoundMem(WalkHandle, DX_PLAYTYPE_BACK);
		}
		ReversX = false;
		transform_.position_.x += p_speed;
		return true;
	}
	else if (input.ThumbLX <= -10000)
	{
		if (CheckSoundMem(WalkHandle) == 0)
		{
			PlaySoundMem(WalkHandle, DX_PLAYTYPE_BACK);
		}
		ReversX = true;
		transform_.position_.x -= p_speed;
		return true;
	}

	// �ړ����Ă��Ȃ��ꍇ�͌��ʉ����~
	if (CheckSoundMem(WalkHandle) == 1)
	{
		StopSoundMem(WalkHandle);
	}

	return false;
}


bool Player::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + (P_SIZE.w / 2);
	float myCenterY = transform_.position_.y + (P_SIZE.h / 2);
	float myR = 32.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

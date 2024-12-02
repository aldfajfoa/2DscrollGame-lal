#include "Field.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Gool.h"
#include "Stone.h"
#include "LeverMaster.h"
#include "SpeedStone.h"
#include "Engine/CsvReader.h"
#include "TestScene.h"
#include "Middle.h"
#include "Engine/SceneManager.h"

Field::Field(GameObject* scene)
	:GameObject(scene,"Field")
{
	hImage = LoadGraph("Assets/bgchar.png");
	background = LoadGraph("Assets/mori.jpg");
	stone = LoadGraph("Assets/isi.png");
	controll = LoadGraph("Assets/Controll.png");
	assert(hImage > 0);
	assert(background > 0);
	assert(controll > 0);
	Map = nullptr;
	scroll = 0;
	SM = (SceneManager*)GetParent()->GetParent();
}

Field::~Field()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
		DeleteGraph(stone);
		DeleteGraph(background);
		DeleteGraph(controll);
	}
	if (Map != nullptr) 
	{
		delete[] Map; //Map�͔z��
	}

	Release();
}

void Field::Reset()
{

	if (Map != nullptr) 
	{
		delete[] Map;
		Map = nullptr;
	}

	CsvReader csv;//�f�[�^��ǂރN���Xf�̃C���X�^���X���쐬
	bool ret = csv.Load("Assets/stageT2.csv");
	assert(ret);
	width = csv.GetWidth(0);
	height = csv.GetHeight();
	Map = new int[width * height];//C����ł̓��I�񎟌��z��̎���
	Backnum = (width * CH_SIZE / WIN_WIDTH) + 1;//�X�e�[�W�̍L���ɍ��킹�Ĕw�i��p��
	
	for (int h = 0; h < height; h++) 
	{
		if (csv.GetString(0, h) == "") 
		{
			height = h;
			break;
		}

		for (int w = 0; w < width; w++)
		{
			Map[h * width + w] = csv.GetInt(w, h);
		}
	}

	//Map�f�[�^�̒���0������΁APlayer�̍��W��0�̈ʒu�ɂ���
	for (int h = 0; h < height; h++) 
	{
		for (int w = 0; w < width; w++) 
		{
			switch (csv.GetInt(w,h+height+1))
			{
			case 0://player
			{
				pplayer = GetParent()->FindGameObject<Player>();
				pplayer->SetPosition(w * 32, h * 32);
				pplayer->SetGround((h * 32) - 20);
			}
			break;
			case 1://�T
			{
				Enemy1* pEne1 = Instantiate<Enemy1>(GetParent());
				pEne1->SetPosition(w * 32, h * 32);
			}
			break;
			case 2://��
			{
				Enemy2* pEne2 = Instantiate<Enemy2>(GetParent());
				pEne2->SetPosition(w * 32, h * 32);
			}
			break;
			case 3://Gool
			{
				Gool* Gools = Instantiate<Gool>(GetParent());
				Gools->SetPosition(w * 32, h * 32);
			}
			break;
			case 4:
			{
			}
			break;
			case 5://SpeedStone
			{
				SpeedStone* Ss = Instantiate<SpeedStone>(GetParent());
				Ss->SetPosition(w * 32, h * 32);
			}
			break;
			case 600:
			case 601:
			case 602:
			case 603:
			case 604:
			{
				LeverMaster* leMas = GetParent()->FindGameObject<LeverMaster>();
				leMas->SetLeverPos(csv.GetInt(w, h + height + 1), w * 32, h * 32);
			}
			break;
			case 7://Middle(���Ԓn�_)
			{
				Middle* mi = Instantiate<Middle>(GetParent());
				mi->SetPosition(w * 32, h * 32);
				middlePosX = w * 32;
				middlePosY = h * 32;
			}
			break;
			}
		}
	}

	if (SM->GetisMiddle()) {
		pplayer->SetPosition(middlePosX, middlePosY);
		pplayer->SetGround(middlePosY - 20);
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			switch (csv.GetInt(w, h))
			{
			case 610:
			case 611:
			case 612:
			case 613:
			case 614:
			{
				LeverMaster* lbMas = GetParent()->FindGameObject<LeverMaster>();
				lbMas->birthLeverBrock(w * 32, h * 32, (csv.GetInt(w, h)) - 610);
			}
			break;
			}
		}
	}
}

void Field::Update()
{
	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}
}

void Field::Draw()
{
	for (int i = 0; i < Backnum; i++) {
		DrawRectGraph((WIN_WIDTH * i) - scroll, 0, 0, 0, WIN_WIDTH, WIN_HEIGHT, background, TRUE);
	}

	scroll = 0;
	cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		scroll = cam->GetValue();
	}

	IsScroll();

	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			int chip = Map[y*width+x];
			DrawRectGraph((x*32)-scroll, y*32, 32*(chip % 16), 32*(chip / 16), 32,32, hImage, TRUE);
		}
	}

	DrawGraph(0, 0, stone, TRUE);
	DrawGraph(10,60, controll, TRUE);
}

void Field::Release()
{
}

int Field::CollisionRight(int x, int y)
{
	if (IsWallBlock(x, y))
	{
		//�������Ă���̂ŁA�߂荞�񂾗ʂ�Ԃ�
		return x % 32 + 1;
	}
	else
		return 0;
}

int Field::CollisionLeft(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//�������Ă���̂ŁA�߂荞�񂾗ʂ�Ԃ�
		return x % 32 - 1;
	}
	else
		return 0;
}

int Field::CollisionDown(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//�������Ă���̂ŁA�߂荞�񂾗ʂ�Ԃ�
		return y % 32 + 1;
	}
	else
		return 0;
}

int Field::CollisionUp(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//�������Ă���̂ŁA�߂荞�񂾗ʂ�Ԃ�
		return y % 32 + 1;
	}
	else
		return 0;
}

void Field::IsScroll()
{
	if (scroll <= 0) {
		scroll = 0;
		LeftSc = false;
	}
	else {
		LeftSc = true;
	}

	if (scroll >= width * 32 - WIN_WIDTH) {
		scroll = width * 32 - WIN_WIDTH;
		RightSc = false;
	}
	else {
		RightSc = true;
	}
}

void Field::ChangeChip(int x, int y,int changeNum)
{
	y;
	x;
	changeNum;
	Map[y * width + x] = changeNum;
}

bool Field::IsWallBlock(int x, int y)
{
	Player* pplayer = GetParent()->FindGameObject<Player>();
	if (pplayer != nullptr)
	{
		int chipX = x / 32;
		int chipY = y / 32;
		switch (Map[chipY * width + chipX])
		{
		case 16:
		case 17:
		case 18:
		case 19:
		case 32:
		case 33:
		case 34:
		case 35:
		case 610:
		case 611:
		case 612:
		case 613:
		case 614:
			return true;
		}
		return false;
	}
}


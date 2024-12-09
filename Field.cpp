#include "Field.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Gool.h"
#include "Stone.h"
#include "LeverMaster.h"
#include "SpeedStone.h"
#include "Middle.h"
#include "Engine/CsvReader.h"
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
	assert(stone > 0);
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
		delete[] Map; //Mapは配列
	}

	Release();
}

void Field::Reset()
{
	if (Map != nullptr)//Mapが空じゃなかったらdelete 
	{
		delete[] Map;
		Map = nullptr;
	}

	CsvReader csv;//データを読むクラスのインスタンスを作成
	bool ret = csv.Load("Assets/stageT2.csv");
	assert(ret);
	width = csv.GetWidth(0);
	height = csv.GetHeight();
	Map = new int[width * height];//C言語での動的二次元配列の取り方
	Backnum = (width * CH_SIZE / WIN_WIDTH) + 1;//ステージの広さに合わせて背景を用意
	
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

	//Mapデータの中で0があれば、Playerの座標を0の位置にする
	for (int h = 0; h < height; h++) 
	{
		for (int w = 0; w < width; w++) 
		{
			switch (csv.GetInt(w,h+height+1))
			{
			case 0://プレイヤー
			{
				pplayer = GetParent()->FindGameObject<Player>();
				pplayer->SetPosition(w * CH_SIZE, h * CH_SIZE);
				pplayer->SetGround((h * CH_SIZE) - 20);
			}
			break;
			case 1://亀
			{
				Enemy1* pEne1 = Instantiate<Enemy1>(GetParent());
				pEne1->SetPosition(w * CH_SIZE, h * CH_SIZE);
			}
			break;
			case 2://鳥
			{
				Enemy2* pEne2 = Instantiate<Enemy2>(GetParent());
				pEne2->SetPosition(w * CH_SIZE, h * CH_SIZE);
			}
			break;
			case 3://ゴール
			{
				Gool* Gools = Instantiate<Gool>(GetParent());
				Gools->SetPosition(w * CH_SIZE, h * CH_SIZE);
			}
			break;
			case 4:
			{
			}
			break;
			case 5://スピードストーン(取ると移動速度UP)
			{
				SpeedStone* Ss = Instantiate<SpeedStone>(GetParent());
				Ss->SetPosition(w * CH_SIZE, h * CH_SIZE);
			}
			break;
			//レバー
			case 600:
			case 601:
			case 602:
			case 603:
			case 604:
			{
				LeverMaster* leMas = GetParent()->FindGameObject<LeverMaster>();
				leMas->SetLeverPos(csv.GetInt(w, h + height + 1), w * CH_SIZE, h * CH_SIZE);
			}
			break;
			case 7://Middle(中間地点)
			{
				Middle* mi = Instantiate<Middle>(GetParent());
				mi->SetPosition(w * CH_SIZE, h * CH_SIZE);
				middlePosX = w * CH_SIZE;
				middlePosY = h * CH_SIZE;
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
				lbMas->birthLeverBrock(w * CH_SIZE, h * CH_SIZE, (csv.GetInt(w, h)) - 610);
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
			DrawRectGraph((x* CH_SIZE)-scroll, y* CH_SIZE, CH_SIZE *(chip % 16), CH_SIZE *(chip / 16), CH_SIZE, CH_SIZE, hImage, TRUE);
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
		//当たっているので、めり込んだ量を返す
		return x % CH_SIZE + 1;
	}
	else
		return 0;
}

int Field::CollisionLeft(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return x % CH_SIZE - 1;
	}
	else
		return 0;
}

int Field::CollisionDown(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return y % CH_SIZE + 1;
	}
	else
		return 0;
}

int Field::CollisionUp(int x, int y)
{
	if (IsWallBlock(x, y)) 
	{
		//当たっているので、めり込んだ量を返す
		return y % CH_SIZE + 1;
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

	if (scroll >= width * CH_SIZE - WIN_WIDTH) {
		scroll = width * CH_SIZE - WIN_WIDTH;
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
		int chipX = x / CH_SIZE;
		int chipY = y / CH_SIZE;
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


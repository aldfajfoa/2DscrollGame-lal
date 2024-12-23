#pragma once
#include "Engine/GameObject.h"
class Player;

class SpeedStone :public GameObject
{
public:
    SpeedStone(GameObject* parent);
    ~SpeedStone();
    void Initialize()override;
    void Update() override;
    void Draw() override;

    //���W���Z�b�g����
    void SetPosition(const int& x, const int& y) {transform_.position_.x = x;
                                                  transform_.position_.y = y;}
    
    bool CollideCircle(const float& x, const float& y, const float& r);//�~�̓����蔻��

    bool IsAlive() { return isAlive; }        //�X�s�[�h�X�g�[���͐����Ă邩�H
    void DeActivateMe() { isAlive = false; }  //�X�s�[�h�X�g�[��������
    void KillStone();

private:
    Player* p;

    bool prevSpaceKey;
    float jumpSpeed;
    int counter;
    bool onGround;
    float baseY;//��������Y���W
    int frameCounter;
    bool IsReverse;
    int tmpPosx, tmpPosy;
    bool isAlive;

    int animType; //��
    int animFrame;//�R�}
    int SpeedStoneG;
};


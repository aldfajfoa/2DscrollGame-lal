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

    //座標をセットする
    void SetPosition(const int& x, const int& y) {transform_.position_.x = x;
                                                  transform_.position_.y = y;}
    
    bool CollideCircle(const float& x, const float& y, const float& r);//円の当たり判定

    bool IsAlive() { return isAlive; }        //スピードストーンは生きてるか？
    void DeActivateMe() { isAlive = false; }  //スピードストーンが死んだ
    void KillStone();

private:
    Player* p;

    bool prevSpaceKey;
    float jumpSpeed;
    int counter;
    bool onGround;
    float baseY;//生成時のY座標
    int frameCounter;
    bool IsReverse;
    int tmpPosx, tmpPosy;
    bool isAlive;

    int animType; //状況
    int animFrame;//コマ
    int SpeedStoneG;
};


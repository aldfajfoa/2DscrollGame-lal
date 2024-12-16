#pragma once
#include "Engine/GameObject.h"
class Player;

class SpeedStone :
    public GameObject
{
public:
    SpeedStone(GameObject* parent);
    ~SpeedStone();
    void Initialize()override;
    void Update() override;
    void Draw() override;

    /// <summary>
    /// �X�s�[�h�X�g�[���̍��W���Z�b�g����
    /// </summary>
    /// <param name="x">X���W</param>
    /// <param name="y">Y���W</param>
    void SetPosition(int x, int y);

    bool CollideCircle(float x, float y, float r);

    bool IsAlive() { return isAlive; }         //�X�s�[�h�X�g�[���͐����Ă邩�H
    void DeActivateMe() { isAlive = false; }   //�X�s�[�h�X�g�[��������
    void ActivateMe() { isAlive = true; }      //�X�s�[�h�X�g�[�����܂������Ă�
    void KillStone();

private:
    bool prevSpaceKey;
    float jumpSpeed;
    int counter;
    bool onGround;
    int SpeedStoneG;
    float baseY;//��������Y���W
    int animType; //��
    int animFrame;//�R�}
    int frameCounter;
    bool IsReverse;
    int tmpPosx, tmpPosy;
    bool isAlive;
    Player* p;
};


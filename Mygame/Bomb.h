#pragma once
#include "Bullet.h";

#define BOMB_STATE_ACTIVE 3100
#define BOMB_STATE_FINISH 3101

#define ID_ANI_BOMB 31001
#define ID_ANI_BOMB_FINISH 31002

#define BOMB_BBOX_WIDTH 9
#define BOMB_BBOX_HEIGHT 9

class Bomb : public Bullet
{
public:
    bool isFinish;
    virtual void render();
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual int IsBlocking() { return 0; };
    virtual int IsCollidable() { return 1; };
    virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);

    Bomb(float  x, float y) :Bullet(x, y)
    {
        timetodestroy = new Timer(10000);
        objecttag = "Bomb";
        dame = 30;
        vx = 0;
        vy = 0;
        maxVx = 0;
        maxVy = 0.1f;
        ax = 0;
        ay = -0.1f;
        state = BOMB_STATE_ACTIVE;
        isFinish = false;
    }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<Gameobject*>* coObjects);
    virtual void SetState(int state);

    void ShootService(float nx, float ny)
    {
        this->nx = nx;
        this->ny = ny;
        ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->AddObject(this);
    }


};

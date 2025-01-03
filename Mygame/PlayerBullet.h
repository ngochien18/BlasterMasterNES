#pragma once
#include "Bullet.h";

#define PLAYERBULLET_STATE_ACTIVE 3000
#define PLAYERBULLET_STATE_FINISH 3001

#define ID_ANI_PLAYERBULLET_RIGHT 30001
#define ID_ANI_PLAYERBULLET_UP 30002
#define ID_ANI_PLAYERBULLET_LEFT 30003
#define ID_ANI_PLAYERBULLET_DOWN 30004

#define ID_ANI_PLAYERBULLET_FINISH 30009

#define PLAYERBULLET_BBOX_WIDTH 9
#define PLAYERBULLET_BBOX_HEIGHT 6

class PlayerBullet : public Bullet
{
public:
    bool isFinish;
    virtual void render();
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual int IsBlocking() { return 0; };
    virtual int IsCollidable() { return 1; };
    virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);

    PlayerBullet(float  x, float y) :Bullet(x, y)
    {
        timetodestroy = new Timer(10000);
        objecttag = "PlayerBullet";
        dame = 50;
        vx = 0;
        vy = 0;
        maxVx = 0.9f;
        maxVy = 0.9f;
        ax = 0.1f;
        ay = 0.1f;
        state = PLAYERBULLET_STATE_ACTIVE;
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


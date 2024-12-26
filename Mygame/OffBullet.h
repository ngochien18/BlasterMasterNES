#pragma once
#include "Bullet.h";
#include "Offside.h"

#define OFFBULLET_STATE_ACTIVE 3200
#define OFFBULLET_STATE_FINISH 3201

#define ID_ANI_OFFBULLET 32001

#define OFFBULLET_BBOX_WIDTH 9
#define OFFBULLET_BBOX_HEIGHT 9

class OffBullet : public Bullet
{
public:
    virtual void render();
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual int IsBlocking() { return 0; };
    virtual int IsCollidable() { return 1; };
    virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject);

    OffBullet(float  x, float y) :Bullet(x, y)
    {
        timetodestroy = new Timer(10000);
        objecttag = "OffBullet";
        dame = 20;
        vx = 0.01f;
        vy = 0.005f;
        maxVx = 0.05f;
        maxVy = 0.006f;
        ax = 0.01f;
        ay = 0.01f;
    }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<Gameobject*>* coObjects);
    virtual void SetState(int state);
    void ShootService(float nx, float ny);
};



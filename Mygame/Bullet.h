#pragma once
#include "GameObject.h"
#include "PlayScene.h"
#include "Timer.h"
class Bullet :
    public Gameobject
{
protected:
    float ax, ay;
    float maxVx, maxVy;
    int size;
    Timer* timetodestroy;
public:
    int dame;
    string fireobjecttag;
    virtual void render() = 0;
    virtual void OnNoCollision(DWORD dt) = 0;
    virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;
    virtual int IsBlocking() { return 0; };
    virtual int IsCollidable() { return 1; };
    virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) = 0;

    Bullet(float  x, float y) :Gameobject(x, y)
    {
        timetodestroy = new Timer(500);
        objecttag = "Bullet";
        vx = 0;
        vy = 0;
        maxVx = 0;
        maxVy = 0;
        ax = 0;
        ay = 0;
        dame = 0;
    }
    virtual void Destroy() { isdeleted = true; }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
    virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {
        if (timetodestroy->IsTimeUp())
        {
            Destroy();
        }
        x += vx * dt;
        y += vy * dt;
    };
    void ShootService(float nx, float ny)
    {
        this->nx = nx;
        this->ny = ny;
        ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->AddObject(this);
    }

};


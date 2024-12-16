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
    int dam;
    int size;
    Timer* timetodestroy;
public:
    string fireobjecttag;
    virtual void render() = 0;
    virtual void OnNoCollision(DWORD dt);
    virtual int IsBlocking() { return 0; }
    virtual void CollisionProcess()
    {

    }
    Bullet(float  x, float y) :Gameobject(x, y)
    {
        timetodestroy = new Timer(3000);
        objecttag = "Bullet";
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
        this->nx=nx;
        this->ny = ny;
        ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->AddObject(this);
    }

};


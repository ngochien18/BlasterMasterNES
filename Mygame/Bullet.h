#pragma once
#include "GameObject.h"
class Bullet :
    public Gameobject
{
protected:
    float ax, ay;
    float maxVx, maxVy;
    int dam;
    int size;
public:
    string fireobjecttag;
    virtual void render() = 0;
    virtual void OnNoCollision(DWORD dt);
    virtual int IsBlocking() { return 0; }
    virtual void CollisionProcess()
    {
        
    }
    virtual void Destroy() { isdeleted = true; }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
    virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {};
};


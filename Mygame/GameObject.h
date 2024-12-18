#pragma once
#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Debug.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "string"
#include "Colision.h"
#define ID_TEX_BBOX 100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency


using namespace std;
class Gameobject
{
protected:
	float x, y;
	float vx, vy;
	int nx,ny;
	int state;
	bool isdeleted;	
	
public:
	bool alwaysrender = false;
	string objecttag;
	virtual void render()=0;
	virtual void setstate(int state) { this->state = state;	 }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	int GetDirection() { return this->nx; }
	int GetState() { return this->state; }
	
	virtual void Delete() { isdeleted = true; }
	bool IsDeleted() { return isdeleted; }

	void RenderBoundingBox();

	Gameobject();
	Gameobject(float x, float y) :Gameobject() { this->x = x; this->y = y; }
	virtual void SetState(int state) { this->state = state; }
	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 1; };//0 for off and 1 for onfloat 

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};
	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	// Does this object collide with other object at certain direction ( like ColorBox )
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }
	// Process Collision
	virtual void CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)=0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {};
	~Gameobject();
	float Getx(){ return x; }
	float Gety() { return y; }
	static bool IsDeleted(const Gameobject* & o) { return o->isdeleted; }
	virtual void impactwithbullet(int dam)
	{

	}
};
typedef Gameobject* LPGAMEOBJECT;

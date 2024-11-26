#pragma once
#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "Debug.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
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
	virtual void render()=0;
	virtual void setstate(int state) { this->state = state;	 }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	
	virtual void Delete() { isdeleted = true; }
	bool IsDeleted() { return isdeleted; }

	void RenderBoundingBox();

	Gameobject();
	Gameobject(float x, float y) :Gameobject() { this->x = x; this->y = y; }
	virtual void SetState(int state) { this->state = state; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<Gameobject*>* coObjects = NULL) {};
	~Gameobject();
	float Getx(){ return x; }
	float Gety() { return y; }
	static bool IsDeleted(const Gameobject* & o) { return o->isdeleted; }
};
typedef Gameobject* LPGAMEOBJECT;

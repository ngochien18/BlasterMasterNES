#pragma once
#include "GameObject.h"
#include "Player.h"
#include "PlayerState.h"
#define JASON_BIG_BBOX_WIDTH  14
#define JASON_BIG_BBOX_HEIGHT 24
class PlayerState;
class Playerdata :
	public Gameobject
{
protected:
	float maxVx;
	float maxVy;
	float accel;			// acceleration 
	int level;
	int untouchable;
	ULONGLONG untouchable_start;

	int id = 0;
public:
	Playerdata(float x, float y) :Gameobject(x, y)
	{
		maxVx = 0.0f;
		maxVy = 0.0f;
		accel = 0.0f;
		id = 403;
		states = new Player();
		states->mPlayerdata = this;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - JASON_BIG_BBOX_WIDTH / 2;
		top = y - JASON_BIG_BBOX_HEIGHT / 2;
		right = left + JASON_BIG_BBOX_WIDTH;
		bottom = top + JASON_BIG_BBOX_HEIGHT;
	}
	void setstate(PlayerState* newstate)
	{
		delete this->states->mPlayerstate;
		states->mPlayerstate = newstate;
	}
	void render()
	{
		Animations* animations = Animations::GetInstance();
		int aniId = -1;
		aniId = id;
		animations->Get(aniId)->Render(x, y);

		RenderBoundingBox();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (nx == 0)
		{
			vx = 0;
		}
		if (ny == 0)
		{
			vy = 0;
		}
		vy += (accel * dt * ny);
		vx += (accel * dt * nx);
		DebugOut(L"vx,vy:%f,%f\n", vx, vy);
		if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
		if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

		x += vx;
		y += vy;
	}
	void SetDirect(float nx, float ny) { this->nx = nx; this->ny = ny; }
	void GetDirect(float& nx, float& ny) { ny = this->ny; nx = this->nx; }
	void SetMaxSpeed(float Speed) { maxVx = Speed; maxVy = Speed; }
	void SetAccel(float a) { accel = a; }
	void SetId(int x) { id = x; }
	void SetSpeed(int x, int y) { vx = x; vy = y; }
};
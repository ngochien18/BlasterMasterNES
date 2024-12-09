#include "Blackfoot.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Colision.h"
#include "string"
void Blackfoot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx *nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy*nx;
	
	if ((state == BLACKFOOT_STATE_DIE) && (GetTickCount64() - die_start > BLACKFOOT_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}
	
	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
	
	//DebugOut(L"ve blackfoot");
}
void Blackfoot::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->objd->IsBlocking()) return;
	if (dynamic_cast<Blackfoot*>(e->objd)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	
	else if (e->nx != 0)
	{
		this->nx = -this->nx;
		ax = -ax;
	}
}
void Blackfoot::OnNoCollision(DWORD dt)
{
	/*float distance = this->distancewithplayer();
	if (distance>range)
	{
		x += vx;
		y += vy;
	}*/
	x += vx;
	y += vy;
}

void Blackfoot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state ==BLACKFOOT_STATE_DIE)
	{
		left = x - BLACKFOOT_BBOX_WIDTH /2;
		top = y + BLACKFOOT_BBOX_HEIGHT_DIE / 2;
		right = left + BLACKFOOT_BBOX_WIDTH;
		bottom = top - BLACKFOOT_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BLACKFOOT_BBOX_WIDTH/2;
		top = y + BLACKFOOT_BBOX_HEIGHT/ 2;
		right = left + BLACKFOOT_BBOX_WIDTH;//+range for the traking box
		bottom = top - BLACKFOOT_BBOX_HEIGHT;//-range for the traking box
	}
}
void Blackfoot::render()
{
	int aniID = 0;
	if (state == BLACKFOOT_STATE_DIE)
	{
		aniID = ID_ANI_BLACKFOOT_DIE;
	}
	else if (vx >= 0)
	{
		aniID = ID_ANI_BLACKFOOT_WALKING_RIGHT;
	}
	else
	{
		aniID = ID_ANI_BLACKFOOT_WALKING_LEFT;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Blackfoot::SetState(int state)
{
	// class game co ham get campos cho a lay ra campos va gan vao bien nha a
	//vi du ve camera a co the lay unity ra a nhe
	//con sunami em da sua thanh lam theo camera roi a co the lay tham khao anh nhe
	Gameobject::SetState(state);
	switch (state)
	{
	case BLACKFOOT_STATE_DIE:
		die_start = GetTickCount64();
		y += (BLACKFOOT_BBOX_HEIGHT - BLACKFOOT_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BLACKFOOT_STATE_WALKING_RL:
		break;
	}
}
void Blackfoot::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{

}
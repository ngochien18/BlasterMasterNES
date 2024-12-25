#include "HealUp.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Colision.h"
#include "string"
void HealUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	Gameobject::Update(dt, coObjects);
	//Colision::GetInstance()->process(this, dt, coObjects);

}
void HealUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->objd->objecttag == "Player"|| e->objs->objecttag == "Player")
	{
		isdeleted = true;
		return;
	}
}
void HealUp::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void HealUp::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HEALUP_BBOX_WIDTH / 2;
	top = y + HEALUP_BBOX_HEIGHT / 2;
	right = left + HEALUP_BBOX_WIDTH;
	bottom = top - HEALUP_BBOX_HEIGHT;
}
void HealUp::render()
{
	int aniID = 0;
	if (state == HEALUP_STATE_ACTIVE)
	{
		aniID = ID_ANI_HEALUP_ACTIVE;
	}
	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void HealUp::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case HEALUP_STATE_ACTIVE:
		break;

	}
}

void HealUp::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	vector<LPCOLLISIONEVENT>event;
	LPCOLLISIONEVENT colX = NULL;
	LPCOLLISIONEVENT colY = NULL;
	event.clear();
	if (IsCollidable())
	{
		Colision::GetInstance()->scan(this, dt, coObject, event);
	}
	if (event.size() == 0)
	{
		OnNoCollision(dt);
	}
	else
	{
		Colision::GetInstance()->filter(this, event, colX, colY, 1, 1, 1);
		if (colX != NULL && colY != NULL)
		{
			if (colX < colY)
			{
				this->OnCollisionWith(colX);
				LPCOLLISIONEVENT colY_other = NULL;
				colX->isdelete = true;
				event.push_back(Colision::GetInstance()->SweptAABB(this, dt, colX->objd));
				Colision::GetInstance()->filter(this, event, colX, colY_other, 1, 0, 1);
				if (colY_other != NULL)
				{
					OnCollisionWith(colY_other);
				}
				else
				{
					y += vy * dt;
				}
			}
			else
			{
				this->OnCollisionWith(colY);
				LPCOLLISIONEVENT colX_other = NULL;
				colY->isdelete = true;
				event.push_back(Colision::GetInstance()->SweptAABB(this, dt, colY->objd));
				Colision::GetInstance()->filter(this, event, colX_other, colY, 1, 1, 0);
				if (colX_other != NULL)
				{
					OnCollisionWith(colX_other);
				}
				else
				{
					x += vx * dt;
				}
			}
		}
		else
		{
			if (colX != NULL)//hoac colx hoac coly null
			{
				y += vy * dt;
				this->OnCollisionWith(colX);
			}
			else {//x null
				if (colY != NULL)
				{
					x += vx * dt;
					this->OnCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += vx * dt;//nho them *dt de phu hop voi tinh frame a nhe
					y += vy * dt;
				}
			}
		}
		for (UINT i = 0; i < event.size(); i++)//check col with all collsion that from non blocking object
		{
			LPCOLLISIONEVENT e = event[i];
			if (e->isdelete) continue;
			if (e->objd->IsBlocking()) continue;  // blocking collisions were handled already, skip them

			OnCollisionWith(e);
		}


		for (UINT i = 0; i < event.size(); i++) delete event[i];//xoa toan bo nhung event 
	}
}
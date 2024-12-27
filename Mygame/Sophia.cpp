#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "PlayScene.h"


#include "SophiaMiddle.h"
#include "SophiaRightWheel.h"
#include "SophiaLeftWheel.h"
#include "SophiaCabin.h"
#include "SophiaGun.h"


Sophia::Sophia(float x, float y) : Playerlevel(x, y)
{
	/*maxVx = 0;
	maxVy = 0;
	ax = 0;
	ay = 0;
	vx = 0;
	vy = 0;*/
	state = SOPHIA_STATE_IDLE;
	objecttag = "Player";

	maxVx = 0.2f;
	maxVy = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
	this->x = x;
	this->y = y;

	middle = new SophiaMiddle(this);
	rightWheel = new SophiaRightWheel(this);
	leftWheel = new SophiaLeftWheel(this);
	cabin = new SophiaCabin(this);
	gun = new SophiaGun(this);
}
void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

	middle->Update(dt);
	rightWheel->Update(dt);
	leftWheel->Update(dt);
	cabin->Update(dt);
	gun->Update(dt);

	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);

	DebugOut(L"vx: %f", vx);


}

void Sophia::render()
{
	middle->render();
	rightWheel->render();
	leftWheel->render();
	cabin->render();
	gun->render();

	RenderBoundingBox();
}

void Sophia::SetState(int state)
{
	Gameobject::SetState(state);

	switch (state)
	{
	case SOPHIA_STATE_WALKING_RIGHT:
		vx = SOPHIA_WALKING_SPEED;
		ax = 0.05f;
		maxVy = SOPHIA_WALKING_MAX_SPEED;
		nx = 1;
		ny = 0;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		break;
	case SOPHIA_STATE_IDLE:
		ax = 0.0f;
		ay = 0.0f;
		vx = 0;
		vy = 0;
		break;
	case SOPHIA_STATE_DIE:
		break;
	}
}

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SOPHIA_BIG_BBOX_WIDTH/2;
	top = y+ SOPHIA_BIG_BBOX_WIDTH/2-10;
	right = left +SOPHIA_BIG_BBOX_WIDTH;
	bottom = top - SOPHIA_BIG_BBOX_HEIGHT;

}

void Sophia::Keystate(BYTE* key)
{
	LPGAME game = game->GetInstance();
	if (state == SOPHIA_STATE_DIE)
	{
		return;
	}
	else if (state == SOPHIA_STATE_IDLE)
	{
		if (game->IsKeyDown(DIK_A))
		{
			SetState(SOPHIA_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(SOPHIA_STATE_WALKING_RIGHT);
		}
		else
		{
			SetState(SOPHIA_STATE_IDLE);
		}
	}
	else if (state == SOPHIA_STATE_WALKING_LEFT
		|| state == SOPHIA_STATE_WALKING_RIGHT)
	{
		if (game->IsKeyDown(DIK_A))
		{
			SetState(SOPHIA_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(SOPHIA_STATE_WALKING_RIGHT);
		}
		else
		{
			SetState(SOPHIA_STATE_IDLE);
		}
	}
}
void Sophia::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->objd->IsBlocking()) return;
}
void Sophia::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

}
void Sophia::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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
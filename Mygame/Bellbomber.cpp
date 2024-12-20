#include "Bellbomber.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include <stdlib.h> 

void Bellbomber::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

	distance = this->distancewithplayerx();

	if ((state == BELLBOMBER_STATE_DIE) && (GetTickCount64() - die_start > BELLBOMBER_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
}
void Bellbomber::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BELLBOMBER_STATE_DIE)
	{
		left = x - BELLBOMBER_BBOX_WIDTH / 2;
		top = y + BELLBOMBER_BBOX_HEIGHT_DIE / 2;
		right = left + BELLBOMBER_BBOX_WIDTH;
		bottom = top - BELLBOMBER_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BELLBOMBER_BBOX_WIDTH / 2;
		top = y + BELLBOMBER_BBOX_HEIGHT / 2;
		right = left + BELLBOMBER_BBOX_WIDTH;
		bottom = top - BELLBOMBER_BBOX_HEIGHT;
	}
}
void Bellbomber::render()
{
	int aniID = ID_ANI_BELLBOMBER_IDLE;
	if (state == BELLBOMBER_STATE_DIE)
	{
		aniID = ID_ANI_BELLBOMBER_DIE;
	}
	else if (vx >= 0)
	{
		aniID = ID_ANI_BELLBOMBER_FLYING_RIGHT;
	}
	else if (vx<0)
	{
		aniID = ID_ANI_BELLBOMBER_FLYING_LEFT;
		if (state == BELLBOMBER_STATE_DROPPING_BOMB) {
			aniID = aniID = ID_ANI_BELLBOMBER_DROPPING_BOMB_LEFT;
		}

	}

	else if (vy >= 0)
	{
		aniID = ID_ANI_BELLBOMBER_FLYING_AWAY;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Bellbomber::SetState(int state)
{
	Gameobject::SetState(state);

	switch (state)
	{
	case BELLBOMBER_STATE_DIE:
		die_start = GetTickCount64();
		y += (BELLBOMBER_BBOX_HEIGHT - BELLBOMBER_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		maxVx = 0;
		maxVy = 0;
		break;
	case BELLBOMBER_STATE_FLYING:
		vx = BELLBOMBER_FLYING_SPEED;
		if (distance >0)
		{
			nx = 1;
			vx = vx;
		}
		else if (distance < 0)
		{
			nx = -1;
			vx = -vx;
		}
		break;
	case BELLBOMBER_STATE_IDLE:
		ax = 0;
		ay = 0;
		break;
	case BELLBOMBER_STATE_DROPPING_BOMB:
		DropBomb();
		//sleep(2000);
		break;
	case BELLBOMBER_STATE_FLYING_AWAY:
		ax = 0;
		vx = 0;
		maxVx = 0;
		vy = BELLBOMBER_FLYING_SPEED;
	}
}
void Bellbomber::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->objd->IsBlocking()) return;
	if (dynamic_cast<Bellbomber*>(e->objd)) return;
}
void Bellbomber::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (abs(distance) <= 200)
	{
		this->SetState(BELLBOMBER_STATE_FLYING);
	}
	/*if (abs(distance) <= 30)
	{
		this->SetState(BELLBOMBER_STATE_DROPPING_BOMB);
		this->SetState(BELLBOMBER_STATE_FLYING_AWAY);
	}*/
	if ((state == BELLBOMBER_STATE_FLYING_AWAY) && (this->y >= 300))
	{
		this->SetState(BELLBOMBER_STATE_DIE);
	}
}

void Bellbomber::DropBomb() {
	Bomb* pBomb = new Bomb(x, y);
	pBomb->ShootService(GunDirectionX, 0);
}
void Bellbomber::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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
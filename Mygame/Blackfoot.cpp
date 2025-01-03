#include "Blackfoot.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Colision.h"
#include "string"
void Blackfoot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay*dt;
	vx = ax*dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx *nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy*ny;
	
	if (health <= 0) 
	{
		SetState(BLACKFOOT_STATE_DIE);
	}
	
	if ((state == BLACKFOOT_STATE_DIE) && (GetTickCount64() - die_start > BLACKFOOT_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}
	
	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
	
}

void Blackfoot::DropItem() 
{
	HealUp* healup = new HealUp(x, y);
	((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->AddObject(healup);
}
void Blackfoot::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->objd->objecttag == "Blackfoot") return;
	if (e->objd->objecttag == "PlayerBullet")
	{
		PlayerBullet* pBu = new PlayerBullet(0, 0);
		TakeDamage(pBu->dame);
		e->objd->Delete();
	}
	if (e->ny != 0)
	{
		Colision::GetInstance()->PushingY(e->t, e->dy, e->ny, this->y, e);
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
	x += vx*dt;
	y += vy*dt;
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
	Gameobject::SetState(state);
	switch (state)
	{
	case BLACKFOOT_STATE_DIE:
		die_start = GetTickCount64();
		y += (BLACKFOOT_BBOX_HEIGHT - BLACKFOOT_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		if (isDropItem == false) {
			DropItem();
			isDropItem = true;
		}
		break;
	case BLACKFOOT_STATE_WALKING_RL:
		break;
	}
}
void Blackfoot::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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
					y += vy*dt;
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
					x += vx*dt;
				}
			}
		}
		else
		{
			if (colX != NULL)//hoac colx hoac coly null
			{
				y += vy*dt;
				this->OnCollisionWith(colX);
			}
			else {//x null
				if (colY != NULL)
				{
					x += vx*dt;
					this->OnCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += vx*dt;//nho them *dt de phu hop voi tinh frame a nhe
					y += vy*dt;
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
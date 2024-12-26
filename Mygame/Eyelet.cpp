#include "Eyelet.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Eyelet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

	if (health <= 0) 
	{
		SetState(EYELET_STATE_DIE);
	}

	if ((state == EYELET_STATE_DIE) && (GetTickCount64() - die_start > EYELET_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	//x += vx;
	//y += vy; //100 - 50 * sin(x / 360 * 3.14);
	
	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
}
void Eyelet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == EYELET_STATE_DIE)
	{
		left = x - EYELET_BBOX_WIDTH / 2;
		top = y + EYELET_BBOX_HEIGHT_DIE / 2;
		right = left + EYELET_BBOX_WIDTH;
		bottom = top - EYELET_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - EYELET_BBOX_WIDTH / 2;
		top = y + EYELET_BBOX_HEIGHT / 2;
		right = left + EYELET_BBOX_WIDTH;
		bottom = top - EYELET_BBOX_HEIGHT;
	}
}
void Eyelet::render()
{
	int aniID = 0;
	if (state == EYELET_STATE_DIE)
	{
		aniID = ID_ANI_EYELET_DIE;
	}
	else if (ax >= 0 )
	{
		aniID = ID_ANI_EYELET_FLYING_RIGHT;

	}
	else if (ax < 0 )
	{
		aniID = ID_ANI_EYELET_FLYING_LEFT;
	}

	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Eyelet::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case EYELET_STATE_DIE:
		die_start = GetTickCount64();	
		y += (EYELET_BBOX_HEIGHT - EYELET_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case EYELET_STATE_FLYING:
		break;

	}
}

void Eyelet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->objd->IsBlocking()) return;
	if (dynamic_cast<Eyelet*>(e->objd)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}

	else if (e->nx != 0)
	{
		this->nx = -this->nx;
		ax = -ax;
	}

	if (e->objd->objecttag == "PlayerBullet")
	{
		PlayerBullet* pBu = new PlayerBullet(0, 0);
		TakeDamage(pBu->dame);
		e->objd->Delete();
	}
}
void Eyelet::OnNoCollision(DWORD dt)
{
	x += vx;
	y += vy;
}

void Eyelet::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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
					y += vy;
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
					x += vx;
				}
			}
		}
		else
		{
			if (colX != NULL)//hoac colx hoac coly null
			{
				y += vy;
				this->OnCollisionWith(colX);
			}
			else {//x null
				if (colY != NULL)
				{
					x += vx;
					this->OnCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += vx;
					y += vy;
				}
			}
		}
	}
}
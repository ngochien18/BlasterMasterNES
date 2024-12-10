#include "Sunami.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Sunami::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = 0.1f*ny;
	vx = 0.1f*nx;

	if ((state == SUNAMI_STATE_DIE) && (GetTickCount64() - die_start > SUNAMI_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
}
void Sunami::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<Sunami*>(e->objd)) return;
	DebugOut(L"Collisioned\n");
	if (e->nx != 0 && e->ny != 0)
	{
		if (lastcolY == 0)
		{
			nx = -nx;
		}
		if (lastcolX == 0)
		{
			ny = -ny;
		}
	}
	if (e->objd->IsBlocking() != 0) {
		lastcolX = e->nx;
		lastcolY = e->ny;
		lastXcol = this->x;
		lastYcol = this->y;
	}
}
void Sunami::OnNoCollision(DWORD dt)
{
	DebugOut(L"No collision\n");
	if (lastcolX==0)
	{
		ny = ny;
		nx = -nx;
		x = lastXcol;
		x += vx * dt;
		y += vy*dt;
		
	}
	else if (lastcolY==0)
	{
		ny = ny;
		ny = -ny;
		y = lastYcol;
		y += vy * dt;
		x += vx * dt;
		
	}
	
}

void Sunami::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SUNAMI_STATE_DIE)
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y + SUNAMI_BBOX_HEIGHT_DIE / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top - SUNAMI_BBOX_HEIGHT_DIE;
	}
	else //x,y tinh tu diem tren ben trai
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y + SUNAMI_BBOX_HEIGHT / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top - SUNAMI_BBOX_HEIGHT;
	}
}
void Sunami::render()
{
	int aniID = 0;
	if (state == SUNAMI_STATE_DIE)
	{
		aniID = ID_ANI_SUNAMI_DIE;
	}
	else if (nx < 0&&lastcolX==0&&lastcolY!=0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_RIGHT;
	}
	else if (nx > 0 && lastcolX == 0&&lastcolY != 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_LEFT;
	}
	else if (ny > 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_DOWN;
	}
	else if (ny < 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_UP;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Sunami::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case SUNAMI_STATE_DIE:
		die_start = GetTickCount64();
		y += (SUNAMI_BBOX_HEIGHT - SUNAMI_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SUNAMI_STATE_WALKING_X:
		break;
	case SUNAMI_STATE_WALKING_Y:
		break;

	}
}

void Sunami::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {
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
				Colision::GetInstance()->filter(this, event, colX, colY_other,1,0,1);
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
#include "Offside.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
#include "Colision.h"
#include "string"
void Offside::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	distance = this->distancewithplayerx();
	if (health <= 0)
	{
		setstate(OFFSIDE_STATE_DIE);
	}

	if ((state == OFFSIDE_STATE_DIE) && (GetTickCount64() - die_start > OFFSIDE_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);

}

void Offside::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->objd->objecttag == "Offside") return;
	if (e->objd->objecttag == "PlayerBullet")
	{
		PlayerBullet* pBu = new PlayerBullet(0, 0);
		TakeDamage(pBu->dame);
		e->objd->Delete();
	}
}
void Offside::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (distance >= 0 && distance <= OFFSIDE_SHOOT_RANGE)
	{
		this->SetState(OFFSIDE_STATE_SHOOT_RIGHT);
	}
	else if (distance >= -OFFSIDE_SHOOT_RANGE && distance < 0)
	{
		this->SetState(OFFSIDE_STATE_SHOOT_LEFT);
	}
	else
	{
		this->SetState(OFFSIDE_STATE_IDLE);
	}
}

void Offside::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == OFFSIDE_STATE_DIE)
	{
		left = x - OFFSIDE_BBOX_WIDTH / 2;
		top = y + OFFSIDE_BBOX_HEIGHT_DIE / 2;
		right = left + OFFSIDE_BBOX_WIDTH;
		bottom = top - OFFSIDE_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - OFFSIDE_BBOX_WIDTH / 2;
		top = y + OFFSIDE_BBOX_HEIGHT / 2;
		right = left + OFFSIDE_BBOX_WIDTH;
		bottom = top - OFFSIDE_BBOX_HEIGHT;
	}
}
void Offside::render()
{
	int aniID = ID_ANI_OFFSIDE_IDLE;
	if (state == OFFSIDE_STATE_DIE)
	{
		aniID = ID_ANI_OFFSIDE_DIE;
	}
	else if (state == OFFSIDE_STATE_SHOOT_RIGHT)
	{
		aniID = ID_ANI_OFFSIDE_SHOOT_RIGHT;
	}
	else if (state == OFFSIDE_STATE_SHOOT_LEFT)
	{
		aniID = ID_ANI_OFFSIDE_SHOOT_LEFT;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void Offside::SetState(int state)
{
	Gameobject::SetState(state);
	switch (state)
	{
	case OFFSIDE_STATE_DIE:
		die_start = GetTickCount64();
		//y += (OFFSIDE_BBOX_HEIGHT - OFFSIDE_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case OFFSIDE_STATE_IDLE:
		break;
	case OFFSIDE_STATE_SHOOT_LEFT:
		GunDirectionX = -1;
		if (GetTickCount64() - this->GetLastShoot() >= 1000) {

			Shoot();
			this->SetLastShoot();
		}
		break;
	case OFFSIDE_STATE_SHOOT_RIGHT:
		GunDirectionX = 1;
		if (GetTickCount64() - this->GetLastShoot() >= 1000) {

			Shoot();
			this->SetLastShoot();
		}
		break;

	}
}

void Offside::Shoot() {
	OffBullet* oBullet = new OffBullet(x, y);
	oBullet->ShootService(GunDirectionX, -1);
}
void Offside::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject)
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
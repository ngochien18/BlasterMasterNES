#include "OffBullet.h"

void OffBullet::render() {
	int aniID = ID_ANI_OFFBULLET;
	if (state == OFFBULLET_STATE_ACTIVE)
	{
		aniID = ID_ANI_OFFBULLET;
	}
	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void OffBullet::Update(DWORD dt, vector<Gameobject*>* coObjects) {
	SetState(this->state);
	if (timetodestroy->IsTimeUp())
	{
		isdeleted = true;
		return;
	}

	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

	Gameobject::Update(dt, coObjects);
	CollisionProcess(dt, coObjects);
}

void OffBullet::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void OffBullet::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->objd->objecttag == "Player")
	{
		this->Delete();
	}
	if (e->objd->objecttag == "Ground")
	{
		this->Delete();
	}
}

void OffBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - OFFBULLET_BBOX_WIDTH / 2;
	top = y + OFFBULLET_BBOX_HEIGHT / 2;
	right = left + OFFBULLET_BBOX_WIDTH;
	bottom = top - OFFBULLET_BBOX_HEIGHT;
}

void OffBullet::SetState(int state) {
	Gameobject::SetState(state);
	switch (state)
	{
	case OFFBULLET_STATE_ACTIVE:
		break;

	}
}
void OffBullet::ShootService(float nx, float ny)
{
	this->nx = nx;
	this->ny = ny;
	((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->AddObject(this);
}
void OffBullet::CollisionProcess(DWORD dt, vector<LPGAMEOBJECT>* coObject) {
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



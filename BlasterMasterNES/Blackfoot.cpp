#include "Blackfoot.h"

CBlackfoot::CBlackfoot(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BLACKFOOT_GRAVITY;
	die_start = -1;
	SetState(BLACKFOOT_STATE_WALKING_LEFT);
}

void CBlackfoot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BLACKFOOT_STATE_DIE)
	{
		left = x - BLACKFOOT_BBOX_WIDTH / 2;
		top = y - BLACKFOOT_BBOX_HEIGHT_DIE / 2;
		right = left + BLACKFOOT_BBOX_WIDTH;
		bottom = top + BLACKFOOT_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BLACKFOOT_BBOX_WIDTH / 2;
		top = y - BLACKFOOT_BBOX_HEIGHT / 2;
		right = left + BLACKFOOT_BBOX_WIDTH;
		bottom = top + BLACKFOOT_BBOX_HEIGHT;
	}
}

void CBlackfoot::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBlackfoot::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBlackfoot*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CBlackfoot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == BLACKFOOT_STATE_DIE) && (GetTickCount64() - die_start > BLACKFOOT_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (vx > 0) {
		state = BLACKFOOT_STATE_WALKING_RIGHT;
	}
	else if (vx < 0) {
		state = BLACKFOOT_STATE_WALKING_LEFT;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBlackfoot::Render()
{
	int aniId = -1;
	if (state == BLACKFOOT_STATE_DIE)
	{
		aniId = ID_ANI_BLACKFOOT_DIE;
	}
	else if (state == BLACKFOOT_STATE_WALKING_LEFT)
		aniId = ID_ANI_BLACKFOOT_WALKING_LEFT;
	else if (state == BLACKFOOT_STATE_WALKING_RIGHT)
		aniId = ID_ANI_BLACKFOOT_WALKING_RIGHT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBlackfoot::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACKFOOT_STATE_DIE:
		die_start = GetTickCount64();
		y += (BLACKFOOT_BBOX_HEIGHT - BLACKFOOT_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BLACKFOOT_STATE_WALKING_LEFT:
		vx = -BLACKFOOT_WALKING_SPEED;
		break;
	case BLACKFOOT_STATE_WALKING_RIGHT:
		vx = BLACKFOOT_WALKING_SPEED;
		break;
	}
}

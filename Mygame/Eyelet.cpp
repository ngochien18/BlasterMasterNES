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
	x += vx;
	y += vy;
	if ((state == EYELET_STATE_DIE) && (GetTickCount64() - die_start > EYELET_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}
	
	Gameobject::Update(dt, coObjects);
}
void Eyelet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == EYELET_STATE_DIE)
	{
		left = x - EYELET_BBOX_WIDTH / 2;
		top = y - EYELET_BBOX_HEIGHT_DIE / 2;
		right = left + EYELET_BBOX_WIDTH;
		bottom = top + EYELET_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - EYELET_BBOX_WIDTH / 2;
		top = y - EYELET_BBOX_HEIGHT / 2;
		right = left + EYELET_BBOX_WIDTH;
		bottom = top + EYELET_BBOX_HEIGHT;
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
		if (y <= lowerbar)
		{
			ny = 1;
		}
		else if (y >= upperbar)
		{
			ny = -1;
		}
		if (ax > 0 && x > Game::GetInstance()->GetBackBufferWidth()-10) { 
			ax = -ax; nx = -1;
		}
		if (ax < 0 && x < 10) { ax = -ax; nx = 1; }
		break;

	}
}
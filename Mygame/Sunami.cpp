#include "Sunami.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Sunami::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	x += vx;
	y += vy;
	if ((state == SUNAMI_STATE_DIE) && (GetTickCount64() - die_start > SUNAMI_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}

	Gameobject::Update(dt, coObjects);
}
void Sunami::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SUNAMI_STATE_DIE)
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y - SUNAMI_BBOX_HEIGHT_DIE / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top + SUNAMI_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SUNAMI_BBOX_WIDTH / 2;
		top = y - SUNAMI_BBOX_HEIGHT / 2;
		right = left + SUNAMI_BBOX_WIDTH;
		bottom = top + SUNAMI_BBOX_HEIGHT;
	}
}
void Sunami::render()
{
	int aniID = 0;
	if (state == SUNAMI_STATE_DIE)
	{
		aniID = ID_ANI_SUNAMI_DIE;
	}
	else if (ax > 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_RIGHT;
	}
	else if (ax < 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_LEFT;
	}
	if (ay > 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_DOWN;
	}
	else if (ay < 0)
	{
		aniID = ID_ANI_SUNAMI_WALKING_UP;
	}


	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}
void Sunami::SetState(int state)
{
	//float cx = 0;
	//float cy = 0;
	//Game::GetInstance()->GetCamPos(cx, cy);
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

		/*if (ax > 0 && x>150) { ax = -ax; nx = -1; }
		if (ax < 0 && x <10) { ax = -ax; nx = 1; }*/
		ay = 0; vy = 0; ny = 0;
		if (y <= 68)
		{
			y = 68;
			ax = 1; nx = 1;
		}
		else if (y >= 100)
		{
			y = 100;
			ax = -1; nx = -1;
		}
		else
		{
			ax = 1; nx = 1;
		}
		if (ax > 0 && x >= 512) { this->state = SUNAMI_STATE_WALKING_Y; }
		if (ax < 0 && x <= 464) {

			this->state = SUNAMI_STATE_WALKING_Y;
		}
		break;
	case SUNAMI_STATE_WALKING_Y:

		/*if (ay > 0 && y > 180) { ay = -ay; ny = -1; }
		if (ay < 0 && y < 10) { ay = -ay; ny = 1; }*/
		ax = 0;  nx = 0; vx = 0;
		if (x <= 464)
		{
			x = 464;
			ay = -1; ny = -1;
		}
		else if (x >= 512)
		{
			x = 512;
			ay = 1; ny = 1;
		}
		else
		{
			ay = -1; ny = -1;
		}
		if (ay > 0 && y >= 100) {

			this->state = SUNAMI_STATE_WALKING_X;
		}
		if (ay < 0 && y <= 68) {

			this->state = SUNAMI_STATE_WALKING_X;
		}

		break;

	}
}
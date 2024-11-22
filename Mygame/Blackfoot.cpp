#include "Blackfoot.h"
#include"Playablechracter.h"
#include "PlayScene.h"
#include "Game.h"
void Blackfoot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;
	x += vx;
	y += vy;
	DebugOut(L"Updated\n");
	if ((state == BLACKFOOT_STATE_DIE) && (GetTickCount64() - die_start > BLACKFOOT_DIE_TIMEOUT))
	{
		isdeleted = true;
		return;
	}
	Gameobject::Update(dt, coObjects);
}
void Blackfoot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
	// class game co ham get campos cho a lay ra campos va gan vao bien nha a
	//vi du ve camera a co the lay unity ra a nhe
	//con sunami em da sua thanh lam theo camera roi a co the lay tham khao anh nhe
	Gameobject::SetState(state);
	switch (state)
	{
	case BLACKFOOT_STATE_DIE:
		die_start = GetTickCount64();
		y += (BLACKFOOT_BBOX_HEIGHT - BLACKFOOT_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BLACKFOOT_STATE_WALKING_RL:

		if(ax >= 0 && x > 200) { ax = -ax; nx = -1; };
		if (ax < 0 && x < 90) { ax = -ax; nx = 1; }
		/*ay = 0; vy = 0; ny = 0;
		if (y <= 10)
		{
			y = 10;
			ax = 1; nx = 1;
		}
		else if (y >= 150)
		{
			y = 150;
			ax = -1; nx = -1;
		}
		else
		{
			ax = 1; nx = 1;
		}
		if (ax > 0 && x >= 250) { this->state = BLACKFOOT_WALKING_DU; }
		if (ax < 0 && x <= 10) {

			this->state = BLACKFOOT_WALKING_DU;
		}
		DebugOut(L"WALKX");*/
		break;
	case BLACKFOOT_WALKING_DU:
		ax = 0;  nx = 0; vx = 0;
		if (x <= 15)
		{
			x = 15;
			ay = -1; ny = -1;
		}
		else if (x >= 250)
		{
			x = 250;
			ay = 1; ny = 1;
		}
		else
		{
			ay = -1; ny = -1;
		}
		if (ay > 0 && y >= 150) {

			this->state = BLACKFOOT_STATE_WALKING_RL;
		}
		if (ay < 0 && y <= 10) {

			this->state = BLACKFOOT_STATE_WALKING_RL;
		}

		break;
	
		/*if (x < 50 || x > 200)
		{
			ax = -0.001f; nx = -1;
		}
		else
		{
			ax = 0.001f; nx = 1;
		}
		break;*/
		/*if (((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Getx() - this->x > 0)
		{
			ax = 0.001f; nx = 1;
		}
		else if (((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Getx()-this->x < 0)
		{
			ax = -0.001f;
			nx = -1;
		}
		else
		{
			vx = 0;
			ax = 0;
		}

		if (this->y - ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Gety() > 0)
		{
			ay = -0.001f; ny = -1;
		}
		else if (this->y - ((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer()->Gety()< 0)
		{
			ay = 0.001f;
			ny = 1;
		}
		else
		{
			vy = 0;
			ay = 0;
		}
		maxVx = BLACKFOOT_WALKING_SPEED;
		maxVy = BLACKFOOT_WALKING_SPEED;
		break;*/
	}
}
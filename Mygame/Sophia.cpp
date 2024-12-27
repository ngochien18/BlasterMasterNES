#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "PlayScene.h"


#include "SophiaMiddle.h"
#include "SophiaRightWheel.h"
#include "SophiaLeftWheel.h"
#include "SophiaCabin.h"
#include "SophiaGun.h"


Sophia::Sophia(float x, float y) : Playerlevel(x, y)
{
	maxVx = 0.2f;
	maxVy = 0;
	ax = 0.1f;
	ay = 0;
	vx = 0.1f;
	vy = 0;
	state = SOPHIA_STATE_IDLE;

	this->x = x;
	this->y = y;

	middle = new SophiaMiddle(this);
	rightWheel = new SophiaRightWheel(this);
	leftWheel = new SophiaLeftWheel(this);
	cabin = new SophiaCabin(this);
	gun = new SophiaGun(this);
}
void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;

	middle->Update(dt);
	rightWheel->Update(dt);
	leftWheel->Update(dt);
	cabin->Update(dt);
	gun->Update(dt);

	Gameobject::Update(dt, coObjects);
	//CollisionProcess(dt, coObjects);


}

void Sophia::render()
{
	middle->render();
	rightWheel->render();
	leftWheel->render();
	cabin->render();
	gun->render();

	RenderBoundingBox();
}

void Sophia::SetState(int state)
{
	Gameobject::SetState(state);

	switch (state)
	{
	case SOPHIA_STATE_WALKING_RIGHT:
		//vx = SOPHIA_WALKING_SPEED;
		//nx = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		//vx = -SOPHIA_WALKING_SPEED;
		//nx = -1;
		break;
	case SOPHIA_STATE_IDLE:
		//vx = 0;
		//ax = 0;
		//maxVx = 0;
		break;
	case SOPHIA_STATE_DIE:
		break;
	}
}

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- SOPHIA_BIG_BBOX_WIDTH/2;
	top = y+ SOPHIA_BIG_BBOX_WIDTH/2;
	right = left +SOPHIA_BIG_BBOX_WIDTH;
	bottom = top - SOPHIA_BIG_BBOX_HEIGHT;

}

void Sophia::Keystate(BYTE* key)
{
	LPGAME game = game->GetInstance();
	if (state == SOPHIA_STATE_DIE)
	{
		return;
	}
	else if (state == SOPHIA_STATE_IDLE)
	{
		if (game->IsKeyDown(DIK_A))
		{
			SetState(SOPHIA_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(SOPHIA_STATE_WALKING_RIGHT);
		}
		else
		{
			SetState(SOPHIA_STATE_IDLE);
		}
	}
	else if (state == SOPHIA_STATE_WALKING_LEFT
		|| state == SOPHIA_STATE_WALKING_RIGHT)
	{
		if (game->IsKeyDown(DIK_A))
		{
			SetState(SOPHIA_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_D))
		{
			SetState(SOPHIA_STATE_WALKING_RIGHT);
		}
		else
		{
			SetState(SOPHIA_STATE_IDLE);
		}
	}
}
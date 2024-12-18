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



void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	middle->Update(dt);
	rightWheel->Update(dt);
	leftWheel->Update(dt);
	cabin->Update(dt);
	gun->Update(dt);

	// Simple fall down
	vy += SOPHIA_GRAVITY * dt;
	
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
		vx = SOPHIA_WALKING_SPEED;
		nx = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		vx = -SOPHIA_WALKING_SPEED;
		nx = -1;
		break;
	case SOPHIA_STATE_JUMP:
		// TODO: need to check if SOPHIA is *current* on a platform before allowing to jump again
		vy = -SOPHIA_JUMP_SPEED_Y;
		break;
	case SOPHIA_STATE_IDLE:
		vx = 0;
		break;
	case SOPHIA_STATE_DIE:
		vy = -SOPHIA_DIE_DEFLECT_SPEED;
		break;
	}
}

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- SOPHIA_BIG_BBOX_WIDTH/2;
	top = y+ SOPHIA_BIG_BBOX_WIDTH/2;
	right = x + SOPHIA_BIG_BBOX_WIDTH;
	bottom = y - SOPHIA_BIG_BBOX_HEIGHT;

}


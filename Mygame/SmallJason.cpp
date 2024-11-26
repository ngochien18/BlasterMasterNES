#include "SmallJason.h"
#include "Debug.h"
#include "Scene.h"
#include "PlayScene.h"
void SmallJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (abs(vy) > abs(maxVy))	vy = maxVy;
	x += vx;
	y += vy;
	// reset untouchable timer if untouchable time has passed
	/*if (GetTickCount64() - untouchable_start > SMALLJASON_DASH_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/
}
int SmallJason::GetAniIdSmall()
{
	int aniId = -1;
	aniId = ID_ANI_SMALLJASON_IDLE_LEFT;
	if (vx == 0 && vy == 0)
	{
		if (nx > 0) aniId = ID_ANI_SMALLJASON_IDLE_RIGHT;
		else if (ny > 0)		aniId = ID_ANI_SMALLJASON_IDLE_DOWN;
		else aniId = ID_ANI_SMALLJASON_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_SMALLJASON_WALKING_RIGHT;
	}
	else if (vx < 0)// vx < 0
	{
		aniId = ID_ANI_SMALLJASON_WALKING_LEFT;
	}
	else if (vy < 0)
	{
		aniId = ID_ANI_SMALLJASON_WALKING_DOWN;
	}
	if (aniId == -1) aniId = ID_ANI_SMALLJASON_IDLE_RIGHT;
	return aniId;
}
void SmallJason::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == SMALLJASON_STATE_DIE) return;

	switch (state)
	{
	case SMALLJASON_STATE_WALK_DOWN:
		maxVy = SMALLJASON_WALKING_SPEED;
		ay = SMALLJASON_ACCEL_WALK;
		ax = 0;
		vx = 0;
		ny = 1;
		nx = 0;
		break;
	case SMALLJASON_STATE_WALK_RIGHT:
		maxVx = SMALLJASON_WALKING_SPEED;
		ax = SMALLJASON_ACCEL_WALK;
		ay = 0;
		vy = 0;
		nx = 1;
		ny = 0;
		break;
	case SMALLJASON_STATE_WALK_LEFT:
		maxVx = -SMALLJASON_WALKING_SPEED;
		ax = -SMALLJASON_ACCEL_WALK;
		ay = 0;
		vy = 0;
		nx = -1;
		ny = 0;
		break;
	case SMALLJASON_STATE_IDLE:
		ax = 0.0f;
		ay = 0.0f;
		vx = 0;
		vy = 0;
		break;
	case SMALLJASON_STATE_DIE:
		vy = 0.0f;
		vx = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		break;
	}


	Gameobject::setstate(state);

	DebugOut(L"small Set stated %d\n", this->state);
}
void SmallJason::SetLevel(int l)
{
}
void SmallJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SMALLJASON_BIG_BBOX_WIDTH / 2;
	top = y - SMALLJASON_BIG_BBOX_HEIGHT / 2;
	right = left + SMALLJASON_BIG_BBOX_WIDTH;
	bottom = top + SMALLJASON_BIG_BBOX_HEIGHT;
}
void SmallJason::OnkeyUP(int keycode)
{
	//SmallJason* jason = (SmallJason*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	
}
void SmallJason::OnkeyDown(int keycode)
{
}
void SmallJason::Keystate(BYTE* key)
{
	LPGAME game = game->GetInstance();
	if (game->IsKeyDown(DIK_DOWN))
	{
		SetState(SMALLJASON_STATE_WALK_DOWN);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SetState(SMALLJASON_STATE_WALK_LEFT);
	}
	else if (game->IsKeyDown(DIK_D))
	{
		SetState(SMALLJASON_STATE_WALK_RIGHT);
	}
	else
	{
		SetState(SMALLJASON_STATE_IDLE);
	}
}

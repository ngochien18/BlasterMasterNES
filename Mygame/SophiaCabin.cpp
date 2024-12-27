#include "SophiaCabin.h"

SophiaCabin::SophiaCabin(Sophia* sophia)
{
	this->base = sophia;

}

SophiaCabin::~SophiaCabin() {}

void SophiaCabin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*SetState(this->state);
	vy = ay * dt;
	vx = ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx * nx;
	if (abs(vy) > abs(maxVy))	vy = maxVy * ny;*/

	nx = base->GetDirection();
	Gameobject::Update(dt, coObjects);
}

void SophiaCabin::render() {
	int aniID = SOPHIA_ANI_CABIN_STANDING_RIGHT;
	float transX = 0, transY = 0;

	if (base->GetState() == SOPHIA_STATE_DIE) {
		return;
	}
	else {
		if (nx > 0)
			aniID = SOPHIA_ANI_CABIN_STANDING_RIGHT;
		else
			aniID = SOPHIA_ANI_CABIN_STANDING_LEFT;

		transX = -4.0;
		transY = 8.0;
	}


	float CabinX, CabinY;
	base->GetPosition(CabinX, CabinY);

	CabinX += SOPHIA_BIG_BBOX_WIDTH / 2;
	CabinY -= SOPHIA_BIG_BBOX_HEIGHT / 2;

	Animations::GetInstance()->Get(aniID)->Render(CabinX + transX, CabinY + transY);
}


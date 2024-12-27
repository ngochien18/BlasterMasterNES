#include "SophiaGun.h"

SophiaGun::SophiaGun(Sophia* sophia)
{
	this->base = sophia;

}

SophiaGun::~SophiaGun() {}

void SophiaGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = base->GetDirection();
	Gameobject::Update(dt, coObjects);
}

void SophiaGun::render() {
	int aniID = SOPHIA_ANI_GUN_0_RIGHT;

	float transX = 10.0, transY = 8.0;

	if (base->GetState() == SOPHIA_STATE_DIE) {
		return;
	}
	else {
		if (nx > 0)
			aniID = SOPHIA_ANI_GUN_0_RIGHT;
		else
		{
			aniID = SOPHIA_ANI_GUN_0_LEFT;
			transX = -10;
		}
	}


	float GunX, GunY;
	base->GetPosition(GunX, GunY);

	GunX += SOPHIA_BIG_BBOX_WIDTH / 2;
	GunY -= SOPHIA_BIG_BBOX_HEIGHT / 2;

	Animations::GetInstance()->Get(aniID)->Render(GunX + transX, GunY + transY);
}

#include "SophiaGun.h"

//SophiaGun::SophiaGun(Sophia* sophia)
//{
//	this->parent = sophia;
//
//	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
//	LPANIMATION_SET ani_set = animation_sets->Get(SOPHIA_PART_ANI_SETS_ID);
//	SetAnimationSet(ani_set);*/
//}

SophiaGun::~SophiaGun() {}

void SophiaGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void SophiaGun::render() {
	int aniID = SOPHIA_ANI_GUN_0_RIGHT;

	float transX = 12.0, transY = -8.0;

	if (parent->GetState() == SOPHIA_STATE_HEAD_UP) {
		aniID = SOPHIA_ANI_GUN_90;
		transX = 0.0;
		transY = -18.0;
	}
	else {
		if (nx > 0)
			aniID = SOPHIA_ANI_GUN_0_RIGHT;
		else
			aniID = SOPHIA_ANI_GUN_0_LEFT;
	}


	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += SOPHIA_BIG_BBOX_WIDTH / 2;
	partY += SOPHIA_BIG_BBOX_HEIGHT / 2;

	int alpha = 255;
	/*if (parent->GetIsUntouchable()) alpha = 128;*/

	Animations::GetInstance()->Get(aniID)->Render(x, y);
}

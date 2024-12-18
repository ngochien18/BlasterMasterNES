#include "SophiaCabin.h"

//sophiacabin::sophiacabin(sophia* sophia)
//{
//	this->parent = sophia;
//
//	/*canimationsets* animation_sets = canimationsets::getinstance();
//	lpanimation_set ani_set = animation_sets->get(sophia_part_ani_sets_id);
//	setanimationset(ani_set);*/
//}

SophiaCabin::~SophiaCabin() {}

void SophiaCabin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void SophiaCabin::render() {
	int aniID = SOPHIA_ANI_CABIN_STANDING_RIGHT;
	float transX = 0, transY = 0;

	if (parent->GetState() == SOPHIA_STATE_HEAD_UP) {
		if (nx > 0) {
			aniID = SOPHIA_ANI_CABIN_HEAD_RIGHT;
			transX = -8.0;
		}

		else {
			aniID = SOPHIA_ANI_CABIN_HEAD_LEFT;
			transX = 0.0;
		}

		transY = -14.0;
	}
	else {
		if (nx > 0)
			aniID = SOPHIA_ANI_CABIN_STANDING_RIGHT;
		else
			aniID = SOPHIA_ANI_CABIN_STANDING_LEFT;

		transX = -4.0;
		transY = -8.0;
	}


	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += SOPHIA_BIG_BBOX_WIDTH / 2;
	partY += SOPHIA_BIG_BBOX_HEIGHT / 2;

	int alpha = 255;
	//if (parent->GetIsUntouchable()) alpha = 128;

	Animations::GetInstance()->Get(aniID)->Render(x, y);
}


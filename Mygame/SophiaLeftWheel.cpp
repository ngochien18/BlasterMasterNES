#include "SophiaLeftWheel.h"

//SophiaLeftWheel::SophiaLeftWheel(Sophia* sophia)
//{
//	this->parent = sophia;
//
//	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
//	LPANIMATION_SET ani_set = animation_sets->Get(SOPHIA_PART_ANI_SETS_ID);
//	SetAnimationSet(ani_set);*/
//}

SophiaLeftWheel::~SophiaLeftWheel() {}

void SophiaLeftWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void SophiaLeftWheel::render() {
	int aniID = SOPHIA_ANI_LEFT_WALK;

	float transX = -7.0, transY = 0;

	if (parent->GetState() == SOPHIA_STATE_IDLE) {
		aniID = SOPHIA_ANI_STANDING;
	}
	else if (parent->GetState() == SOPHIA_STATE_WALKING_RIGHT) {
		aniID = SOPHIA_ANI_RIGHT_WALK;
	}
	else if (parent->GetState() == SOPHIA_STATE_WALKING_LEFT) {
		aniID = SOPHIA_ANI_LEFT_WALK;
	}
	else if (parent->GetState() == SOPHIA_STATE_HEAD_UP) {
		aniID = SOPHIA_ANI_STANDING;
		transX = -5.0;
	}


	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += SOPHIA_BIG_BBOX_WIDTH / 2;
	partY += SOPHIA_BIG_BBOX_HEIGHT / 2;

	int alpha = 255;
	/*if (parent->GetIsUntouchable()) alpha = 128;

	this->animation_set->at(ani)->Render(partX + transX, partY, alpha);*/

	Animations::GetInstance()->Get(aniID)->Render(x, y);
}

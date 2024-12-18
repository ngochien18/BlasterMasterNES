#include "SophiaMiddle.h"

//SophiaMiddle::SophiaMiddle(Sophia* sophia)
//{
//	this->parent = sophia;
//
//	/*CAnimationSets* aniIDmation_sets = CAnimationSets::GetInstance();
//	LPANIMATION_SET aniID_set = aniIDmation_sets->Get(SOPHIA_PART_ANI_SETS_ID);
//	SetAnimationSet(aniID_set);*/
//}

SophiaMiddle::~SophiaMiddle() {}

void SophiaMiddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void SophiaMiddle::render() {
	int aniID = SOPHIA_ANI_MIDDLE;
	float transX = 0, transY = 0;

	if (parent->GetState() == SOPHIA_STATE_HEAD_UP) {
		transX = 0;
		transY = -3.0;
	}
	else {

		transX = 0;
		transY = 0;
	}

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += SOPHIA_BIG_BBOX_WIDTH / 2;
	partY += SOPHIA_BIG_BBOX_HEIGHT / 2;

	int alpha = 255;
	/*if (parent->GetIsUntouchable()) alpha = 128;

	this->aniIDmation_set->at(aniID)->Render(partX + transX, partY + transY, alpha);*/

	Animations::GetInstance()->Get(aniID)->Render(x, y);
}
